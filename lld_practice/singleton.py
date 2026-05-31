from threading import Lock, Thread


class SingletonMeta(type):
    _instance_dict = {}
    _lock = Lock()

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instance_dict:
            with cls._lock:
                if cls not in cls._instance_dict:
                    instance = super().__call__(*args, *kwargs)
                    cls._instance_dict[cls] = instance
        return cls._instance_dict[cls]


class DBclient(metaclass=SingletonMeta):
    def __init__(self, url: str):
        self.url = url
        print(f"Db Client Initialized succesffuly with url as {url}")


def test_singleton(url: str):
    db = DBclient(url)
    print(db.url, "\n")


if __name__ == "__main__":
    t1 = Thread(target=test_singleton, args=["url1"], name="first thread")
    t2 = Thread(target=test_singleton, args=["url2"], name="second thread")

    for thread in [t1, t2]:
        thread.start()
    for thread in [t1, t2]:
        thread.join()
