from threading import Thread, Lock
from bs4 import BeautifulSoup
from queue import Queue
import requests

url_frontier = Queue()
visited_urls = set()
visited_lock = Lock()
THREAD_COUNT = 5
END_ELEMENT = None
# SEED_URL="https://maps.app.goo.gl"
SEED_URL = "https://www.linkedin.com/"


def process_single_url(url: str) -> None:
    # do the processing  [fetch content from url and find all url]
    # We will use BeautifulSoup to fetch all links from that url
    # Since BeautifulSoup will handle the unicode in better way, So we will pass
    # The content for better output than response text, because BeautifulSoup will handle
    # Special Characters like Emojis and other charaters internally
    try:
        res = requests.get(url, timeout=5)
        soup = BeautifulSoup(res.content, "html.parser")
        urls = [
            str(anchor_element.get("href"))
            for anchor_element in soup.find_all("a")
            if anchor_element.get("href") is not None
        ]
        print(f"total sub urls found for {url} is {len(urls)}")

        #  Add all urls in the Queue
        for url in urls:
            #   Use Lock to prevent adding duplicate entries in the Queue
            with visited_lock:
                if url not in visited_urls:
                    visited_urls.add(url)
                    url_frontier.put(url)

    except:
        pass


def worker():
    while True:
        url = url_frontier.get()

        if url == END_ELEMENT:
            url_frontier.task_done()
            return  # Break from this while loop

        # process url
        process_single_url(url)
        # After task completion, mark task as completed
        url_frontier.task_done()


threads = [
    Thread(target=worker, name=f"{i+1} th Thread") for i in range(0, THREAD_COUNT)
]

# Add the seed url to the url_frontier
url_frontier.put(SEED_URL)
visited_urls.add(SEED_URL)

# Start threads
for thread in threads:
    thread.start()
    # Don't do thread.join() here, Because if we do so then the main thread will wait for current
    # say (ith) thread to complete. And in this way we will have only 1 thread executing at a timeout
    # And We will loose concurrency

# Wait for all the tasks from the url_frontier to finished
url_frontier.join()

# At This point, all threads will blocks becuase of get call and will wait for new element
# We will add the sentinel (Gruard) value to wake up the threads which are sleep when Queue emptied
# Since each thread will only consume only 1 occurance of SENTINEL (Gruards / END CONTENT)

for _ in range(THREAD_COUNT):
    # Each Sentinel will wake up each thread and due the check, each thread will return from the while loop
    url_frontier.put(END_ELEMENT)

# Now join the threads (Main Thread will wait for all the threads to complete)
for thread in threads:
    thread.join() # At a time only 1 thread will call and will block till that thread completes
