# Spring Web MVC — From Servlet to Response

[⬅ 02-spring-core.md](02-spring-core.md) · [🏠 Start here](00-start-here.md) · [04-spring-data.md ➡](04-spring-data.md)

> Part of the Java & Spring Boot learning set. Section labels in this file start with **W**. The legend, version landscape, quick revision sheet and glossary live in [00-start-here.md](00-start-here.md).

## Contents

- [W1. Servlets and the servlet container [Q42, Q43, Q44]](#w1-servlets-and-the-servlet-container-q42-q43-q44)
  - [W1.1 What is a servlet? [Q42]](#w11-what-is-a-servlet-q42)
  - [W1.2 What is a servlet container? [Q42]](#w12-what-is-a-servlet-container-q42)
  - [W1.3 The servlet lifecycle [Q43]](#w13-the-servlet-lifecycle-q43)
  - [W1.4 A complete servlet, and what the container does with it [Q43]](#w14-a-complete-servlet-and-what-the-container-does-with-it-q43)
  - [W1.5 One servlet, many threads — the concurrency model [Q44]](#w15-one-servlet-many-threads--the-concurrency-model-q44)
  - [W1.6 The default Tomcat knobs [+]](#w16-the-default-tomcat-knobs-)
- [W2. Front Controller and DispatcherServlet [Q41, Q45, Q46, Q48]](#w2-front-controller-and-dispatcherservlet-q41-q45-q46-q48)
  - [W2.1 What the Front Controller pattern is [Q45]](#w21-what-the-front-controller-pattern-is-q45)
  - [W2.2 Is the Front Controller the same as the DispatcherServlet? [Q45]](#w22-is-the-front-controller-the-same-as-the-dispatcherservlet-q45)
  - [W2.3 Front Controller vs `@Controller` — the two "controllers" [Q45]](#w23-front-controller-vs-controller--the-two-controllers-q45)
  - [W2.4 The equivalent component in FastAPI and Express [Q46]](#w24-the-equivalent-component-in-fastapi-and-express-q46)
  - [W2.5 So why does Java need a *named, visible* one? [Q41, Q48]](#w25-so-why-does-java-need-a-named-visible-one-q41-q48)
  - [W2.6 You never write it [Q47]](#w26-you-never-write-it-q47)
  - [W2.7 What a Front Controller buys you [+]](#w27-what-a-front-controller-buys-you-)
  - [W2.8 The three collaborators inside the DispatcherServlet: HandlerMapping, HandlerAdapter, HandlerExecutionChain](#w28-the-three-collaborators-inside-the-dispatcherservlet-handlermapping-handleradapter-handlerexecutionchain)
- [W3. MVC architecture (and hexagonal compared) [Q49–Q54]](#w3-mvc-architecture-and-hexagonal-compared-q49q54)
  - [W3.1 What MVC is [Q49]](#w31-what-mvc-is-q49)
  - [W3.2 The components of Spring MVC [Q51]](#w32-the-components-of-spring-mvc-q51)
  - [W3.3 End-to-end request/response — the classic (view-rendering) flow [Q50, Q52]](#w33-end-to-end-requestresponse--the-classic-view-rendering-flow-q50-q52)
  - [W3.4 The complete REST/JSON architecture diagram [Q53]](#w34-the-complete-restjson-architecture-diagram-q53)
  - [W3.5 The gRPC architecture diagram [Q54]](#w35-the-grpc-architecture-diagram-q54)
  - [W3.6 Your specific questions about MVC mapping [Q50]](#w36-your-specific-questions-about-mvc-mapping-q50)
  - [W3.7 Where does business logic go: controller or model?](#w37-where-does-business-logic-go-controller-or-model)
  - [W3.8 How Spring MVC compares to other Java architectures [Q49]](#w38-how-spring-mvc-compares-to-other-java-architectures-q49)
  - [W3.9 Hexagonal architecture (Ports and Adapters) [Q49]](#w39-hexagonal-architecture-ports-and-adapters-q49)
  - [W3.10 Is MVC followed outside Java? [Q50]](#w310-is-mvc-followed-outside-java-q50)
- [W4. REST Controller — the complete unabstracted request lifecycle [Q★]](#w4-rest-controller--the-complete-unabstracted-request-lifecycle-q)
  - [W4.1 The dependencies you need](#w41-the-dependencies-you-need)
  - [W4.2 The 30,000-foot view](#w42-the-30000-foot-view)
  - [W4.3 What's actually on the wire](#w43-whats-actually-on-the-wire)
  - [W4.4 Tomcat accepts the socket](#w44-tomcat-accepts-the-socket)
  - [W4.5 HTTP parsing into `HttpServletRequest`](#w45-http-parsing-into-httpservletrequest)
  - [W4.6 The filter chain](#w46-the-filter-chain)
  - [W4.7 `DispatcherServlet.doDispatch()` and routing](#w47-dispatcherservletdodispatch-and-routing)
  - [W4.8 JSON to Java object (where "JSON.parse" really lives)](#w48-json-to-java-object-where-jsonparse-really-lives)
  - [W4.9 Validation](#w49-validation)
  - [W4.10 Invoke, then Java object to JSON](#w410-invoke-then-java-object-to-json)
  - [W4.11 The exception path](#w411-the-exception-path)
  - [W4.12 The complete annotation reference](#w412-the-complete-annotation-reference)
  - [W4.13 Routing: does declaration order matter?](#w413-routing-does-declaration-order-matter)
  - [W4.14 The alternative: functional endpoints — and why they aren't popular](#w414-the-alternative-functional-endpoints--and-why-they-arent-popular)
  - [W4.15 Threading model: thread-per-request, async, WebFlux, virtual threads](#w415-threading-model-thread-per-request-async-webflux-virtual-threads)
  - [W4.16 Debugging cheatsheet: where to put a breakpoint](#w416-debugging-cheatsheet-where-to-put-a-breakpoint)
  - [W4.17 A complete, annotated worked example](#w417-a-complete-annotated-worked-example)
- [W5. Filters vs HandlerInterceptors](#w5-filters-vs-handlerinterceptors)
  - [W5.1 The two layers in one picture](#w51-the-two-layers-in-one-picture)
  - [W5.2 The exact order of events](#w52-the-exact-order-of-events)
  - [W5.3 Does an interceptor run for every endpoint?](#w53-does-an-interceptor-run-for-every-endpoint)
  - [W5.4 Filter, server interceptor or client interceptor? The decision guide](#w54-filter-server-interceptor-or-client-interceptor-the-decision-guide)
  - [W5.5 `postHandle` vs `afterCompletion`, and the timing example](#w55-posthandle-vs-aftercompletion-and-the-timing-example)
  - [W5.6 So where does CORS run: filter or interceptor?](#w56-so-where-does-cors-run-filter-or-interceptor)
  - [W5.7 GZIP compression: per endpoint or global, and where?](#w57-gzip-compression-per-endpoint-or-global-and-where)
- [W6. Reading input and data binding [Q55, Q56]](#w6-reading-input-and-data-binding-q55-q56)
  - [W6.1 `@RequestParam` vs `request.getParameter()` [Q55]](#w61-requestparam-vs-requestgetparameter-q55)
  - [W6.2 The complete "where does this value come from" table [Q55]](#w62-the-complete-where-does-this-value-come-from-table-q55)
  - [W6.3 Several path variables, and does parameter order matter?](#w63-several-path-variables-and-does-parameter-order-matter)
  - [W6.4 Data binding for HTML forms [Q55]](#w64-data-binding-for-html-forms-q55)
  - [W6.5 `Model`, `ModelMap`, `ModelAndView` — and the Express equivalent [Q55]](#w65-model-modelmap-modelandview--and-the-express-equivalent-q55)
  - [W6.6 `@RequestMapping` vs the shortcut annotations [Q55]](#w66-requestmapping-vs-the-shortcut-annotations-q55)
  - [W6.7 [+] Type conversion: how `"25"` becomes `25`](#w67--type-conversion-how-25-becomes-25)
  - [W6.8 Reading `Converter<String, OrderStatus>`: generics, registration, and where it applies](#w68-reading-converterstring-orderstatus-generics-registration-and-where-it-applies)
  - [W6.9 `@InitBinder` [Q55, Q56]](#w69-initbinder-q55-q56)
  - [W6.10 `@InitBinder` follow-up questions](#w610-initbinder-follow-up-questions)
  - [W6.11 [+] Mass assignment: the vulnerability `@InitBinder` actually defends against](#w611--mass-assignment-the-vulnerability-initbinder-actually-defends-against)
- [W7. Validation [Q55]](#w7-validation-q55)
  - [W7.1 The three layers — spec, implementation, integration](#w71-the-three-layers--spec-implementation-integration)
  - [W7.2 `javax.annotation.Nonnull` vs Bean Validation [Q55]](#w72-javaxannotationnonnull-vs-bean-validation-q55)
  - [W7.3 The annotation catalogue [Q55]](#w73-the-annotation-catalogue-q55)
  - [W7.4 `@Valid` vs `@Validated`](#w74-valid-vs-validated)
  - [W7.5 Where validation runs, and what gets thrown](#w75-where-validation-runs-and-what-gets-thrown)
  - [W7.6 `BindingResult` [Q55]](#w76-bindingresult-q55)
  - [W7.7 Custom validation annotations [Q55]](#w77-custom-validation-annotations-q55)
  - [W7.8 Custom error messages [Q55]](#w78-custom-error-messages-q55)
  - [W7.9 End-to-end worked example [Q55]](#w79-end-to-end-worked-example-q55)
  - [W7.10 Validation in a REST API — what changes](#w710-validation-in-a-rest-api--what-changes)
  - [W7.11 Comparison: Bean Validation vs Pydantic vs Zod [Q55]](#w711-comparison-bean-validation-vs-pydantic-vs-zod-q55)
- [W8. Writing responses: @ResponseBody, ResponseEntity, message converters, and global error handling](#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling)
  - [W8.1 `@Controller` vs `@RestController`: what "= `@Controller` + `@ResponseBody`" means](#w81-controller-vs-restcontroller-what--controller--responsebody-means)
  - [W8.2 `@RequestBody` vs `@ResponseBody`: input vs output](#w82-requestbody-vs-responsebody-input-vs-output)
  - [W8.3 `HttpMessageConverter` and Jackson: who actually writes the JSON](#w83-httpmessageconverter-and-jackson-who-actually-writes-the-json)
  - [W8.4 `produces` and `consumes`](#w84-produces-and-consumes)
  - [W8.5 `ResponseEntity` vs plain return + `@ResponseStatus`](#w85-responseentity-vs-plain-return--responsestatus)
  - [W8.6 Error handling in both styles](#w86-error-handling-in-both-styles)
  - [W8.7 `@ControllerAdvice` vs `@RestControllerAdvice`](#w87-controlleradvice-vs-restcontrolleradvice)
  - [W8.8 Global exception handling with `ProblemDetail` [+]](#w88-global-exception-handling-with-problemdetail-)
- [W9. CORS: @CrossOrigin, CorsFilter, and Spring Security](#w9-cors-crossorigin-corsfilter-and-spring-security)
  - [W9.1 CORS in 60 seconds](#w91-cors-in-60-seconds)
  - [W9.2 The four ways to configure CORS in Spring, and where each runs](#w92-the-four-ways-to-configure-cors-in-spring-and-where-each-runs)
  - [W9.3 How `@CrossOrigin` works behind the scenes](#w93-how-crossorigin-works-behind-the-scenes)
  - [W9.4 Global + local: combined, not "most specific wins"](#w94-global--local-combined-not-most-specific-wins)
  - [W9.5 Spring Security and CORS](#w95-spring-security-and-cors)
  - [W9.6 `allowCredentials`, `OPTIONS` `permitAll`, and other pitfalls](#w96-allowcredentials-options-permitall-and-other-pitfalls)
- [W10. Request-scoped context: RequestContextHolder and LocaleContextHolder](#w10-request-scoped-context-requestcontextholder-and-localecontextholder)
  - [W10.1 What they hold, and who fills them](#w101-what-they-hold-and-who-fills-them)
  - [W10.2 New threads, pools and virtual threads](#w102-new-threads-pools-and-virtual-threads)
- [W11. Thymeleaf and server-side rendering [Q15, Q16]](#w11-thymeleaf-and-server-side-rendering-q15-q16)
  - [W11.1 What Thymeleaf is, and the EJS comparison [Q15]](#w111-what-thymeleaf-is-and-the-ejs-comparison-q15)
  - [W11.2 Do you create the HTML file yourself? [Q16]](#w112-do-you-create-the-html-file-yourself-q16)
  - [W11.3 [+] The five expression types — the cheatsheet that matters](#w113--the-five-expression-types--the-cheatsheet-that-matters)
  - [W11.4 [+] Configuration and production gotchas](#w114--configuration-and-production-gotchas)
  - [W11.5 [+] When *not* to use Thymeleaf](#w115--when-not-to-use-thymeleaf)
- [W12. API documentation: OpenAPI and Swagger [Q32, Q33]](#w12-api-documentation-openapi-and-swagger-q32-q33)
  - [W12.1 Is this the same Swagger as FastAPI's? [Q32]](#w121-is-this-the-same-swagger-as-fastapis-q32)
  - [W12.2 The dependency [Q32]](#w122-the-dependency-q32)
  - [W12.3 Does it work with Spring Data REST? [Q32]](#w123-does-it-work-with-spring-data-rest-q32)
  - [W12.4 Customizing the paths [Q32]](#w124-customizing-the-paths-q32)
  - [W12.5 Why you'd want the JSON/YAML endpoint [Q32]](#w125-why-youd-want-the-jsonyaml-endpoint-q32)
  - [W12.6 Enriching the docs with `@Operation` and `@Schema` [Q33]](#w126-enriching-the-docs-with-operation-and-schema-q33)
  - [W12.7 Documenting gRPC [Q32]](#w127-documenting-grpc-q32)

---

## W1. Servlets and the servlet container [Q42, Q43, Q44]

> **Your questions:** *"what is servlet and servlet container?"* [Q42] · *"how the servlet life cycle works in detail, or look at a sample code implementation of an HttpServlet?"* [Q43] · *"when we are creating an application using spring boot and tomcat as a web server, so here only one servlet container will be there and that servlet container will have multiple servlets running inside that? …do we have separate servlet for each request or each servlet can handle multiple request at a time?"* [Q44]

You will never write a servlet. But **every single thing in Spring MVC sits on top of this API**, and you cannot read a Spring stack trace without knowing it.

### W1.1 What is a servlet? [Q42]

A **servlet** is a Java class conforming to the **Jakarta Servlet API** (formerly Java Servlet API). It extends a server's capabilities by processing incoming HTTP requests (GET, POST, …) and returning dynamic content — HTML, JSON, XML.

The historical point that explains its design: instead of spawning a heavy, independent **OS process per request** like 1990s CGI programs, a servlet runs as a **lightweight thread inside a shared process** — fast and memory-efficient. That single decision is why Java web apps are thread-per-request to this day.

Its lifecycle contract is three methods: `init()`, `service()`, `destroy()`.

### W1.2 What is a servlet container? [Q42]

A **servlet container** (a.k.a. **web container**) is the system software that runs servlets. It is the bridge between the raw network and your Java code:

- Listens for incoming **socket connections**.
- Parses raw network bytes into clean Java objects (`HttpServletRequest`) and wraps responses (`HttpServletResponse`).
- Controls the **entire lifecycle** of every servlet — loading classes, instantiating, initialising, destroying.
- Manages the **thread pool**, security, and session state.

Popular ones: **Apache Tomcat** (Spring Boot's default), **Eclipse Jetty**, **Undertow**.

| | Servlet | Servlet container |
|---|---|---|
| Definition | a class **you** write | system software providing the runtime |
| Role | business logic for one kind of request | sockets, threads, routing, security, lifecycle |
| Lifecycle control | *implements* `init()`, `service()`, `destroy()` | *invokes* `init()`, `service()`, `destroy()` |
| **Analogy** | the plug-in appliance (a toaster) | the wall socket supplying power and structure |

🐍🟨 **The equivalents:** Tomcat ≈ **Uvicorn/Gunicorn** ≈ **the Node `http` module**. The Servlet API ≈ **ASGI** ≈ Node's `(req, res)` callback contract.

### W1.3 The servlet lifecycle [Q43]

```
┌──────────────────────────┐
│ 1. Loading & Instantiation│  container loads the class, calls the no-arg constructor
└────────────┬──────────────┘   (at server start, or on the first request to it)
             ▼
┌──────────────────────────┐
│ 2. init()                 │  called EXACTLY ONCE. One-time setup:
└────────────┬──────────────┘   DB connections, reading config params
             ▼
┌──────────────────────────┐
│ 3. service()  ◄──────────┐│  called for EVERY request, on a NEW THREAD from the pool.
│    dispatches to         ││  Dispatches by HTTP method →
│    doGet/doPost/doPut/…  ││  doGet(), doPost(), doPut(), doDelete(), doHead(), doOptions()
└────────────┬─────────────┘│
             │   (repeats, concurrently, for the life of the app)
             ▼
┌──────────────────────────┐
│ 4. destroy()              │  called ONCE on shutdown/undeploy. Cleanup.
└──────────────────────────┘
```

### W1.4 A complete servlet, and what the container does with it [Q43]

```java
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

// Maps this servlet to the URL path "/greet"
@WebServlet("/greet")
public class HelloServlet extends HttpServlet {

    // 1. One-time initialization
    @Override
    public void init() throws ServletException {
        System.out.println("Servlet initialized successfully!");
    }

    // 2. Handling an HTTP GET
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String userName = request.getParameter("name");     // reads ?name=Alice
        if (userName == null || userName.trim().isEmpty()) {
            userName = "Guest";
        }

        response.setContentType("text/html");

        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Hello, " + userName + "!</h1>");
        out.println("<p>Welcome to our Servlet application.</p>");
        out.println("</body></html>");
    }

    // 3. One-time cleanup
    @Override
    public void destroy() {
        System.out.println("Servlet is being destroyed. Cleaning up resources...");
    }
}
```

**What the container does behind the scenes** [Q43]:

1. A user visits `http://localhost:8080/my-app/greet?name=John`.
2. The container intercepts the network request on port 8080.
3. It parses the HTTP data, instantiates `HelloServlet` (if not already) and calls `init()`.
4. It creates an `HttpServletRequest` holding `name=John`, and an empty `HttpServletResponse`.
5. It invokes `service()`, which sees the method is GET and triggers `doGet()`.
6. Your code runs, reads `"John"`, and prints HTML into the response object.
7. The container turns that populated response back into a raw HTTP packet and writes it to the socket.

⚠️ Note `jakarta.servlet`, not `javax.servlet`. The namespace changed in **Jakarta EE 9 / Spring Framework 6 / Spring Boot 3.0**. Any tutorial older than late 2022 uses `javax.*` and **will not compile** on Boot 3. This is the #1 source of confusion when following older material.

### W1.5 One servlet, many threads — the concurrency model [Q44]

> **Your questions:** *"do we have separate servlet for each request or each servlet can handle multiple request at a time?"* and *"does servlets inside servlet helps in handling concurrent request because java & spring boot doesn't have the event loop… and it spawns a dedicated thread for each new request?"*

**Direct answers:**
- **No, there is not a separate servlet per request.**
- **In a Spring Boot REST API there is essentially ONE servlet** — the `DispatcherServlet`.
- **That one servlet instance handles many requests simultaneously**, via a **thread pool**.

Your intuition about the missing event loop is exactly right, and the consequence is exactly as you guessed:

```
[Incoming Request 1] ──► [Tomcat Thread Pool: Thread-A] ──► [DispatcherServlet] ──► [Your Controller]
[Incoming Request 2] ──► [Tomcat Thread Pool: Thread-B] ──► [DispatcherServlet] ──► [Your Controller]
[Incoming Request 3] ──► [Tomcat Thread Pool: Thread-C] ──► [DispatcherServlet] ──► [Your Controller]
            ▲                        ▲                              ▲
      HTTP over TCP        ~200 threads by default        ONE shared instance
```

1. **Tomcat maintains a pool of worker threads** — by default up to **200**.
2. When a request arrives, Tomcat grabs an **idle thread** and assigns the request to it.
3. That thread executes `service()` on the **single, shared** `DispatcherServlet` instance.
4. If 50 users hit your API in the same millisecond, 50 different threads execute code inside **the same** `DispatcherServlet` object concurrently.

**Why one instance can serve thousands of concurrent requests:** Java methods are **re-entrant**. Each thread has its **own stack** and its **own local variables**. They do not interfere.

⚠️ **The crucial rule that follows — and it is the single most important thread-safety rule in Spring:**

> Because the servlet (and every Spring **singleton** bean — your `@Service`, `@Repository`, `@RestController`) is **shared across all request threads**, **they must be stateless.** If you store request-specific data in an **instance field**, concurrent threads will overwrite each other's data. You get data leaking between users — one customer seeing another's order.

```java
@RestController
public class OrderController {
    private String currentUserId;            // ❌❌❌ CATASTROPHIC. Shared across all requests.

    private final OrderService service;      // ✅ fine — immutable dependency, set once at startup

    @GetMapping("/orders")
    public List<Order> list(@RequestParam String userId) {
        String local = userId;               // ✅ fine — a LOCAL variable lives on the thread's stack
        return service.findFor(local);
    }
}
```

🐍🟨 This has no analogue in your background. In Express each request runs a fresh closure; in FastAPI a `Depends` typically resolves per request. **In Spring the object graph is built once at startup and shared forever.**

### W1.6 The default Tomcat knobs [+]

```properties
server.port=8080
server.tomcat.threads.max=200          # max concurrent in-flight requests
server.tomcat.threads.min-spare=10     # threads kept warm
server.tomcat.max-connections=8192     # accepted sockets (queued beyond thread count)
server.tomcat.accept-count=100         # OS backlog once max-connections is hit
server.tomcat.connection-timeout=20s
```

**The capacity arithmetic that matters:** with `threads.max=200` and an endpoint whose downstream call takes 500 ms, your theoretical ceiling is `200 / 0.5s = 400 req/s`. Beyond that, requests queue and latency climbs off a cliff. This is why Java shops care so much about downstream timeouts — and why virtual threads ([§J6.12](01-java.md#j612-virtual-threads-and-structured-concurrency-)) are such a big deal.

---

## W2. Front Controller and DispatcherServlet [Q41, Q45, Q46, Q48]

> **Your questions, merged:** *"what is front controller pattern and how it is different from controller in spring boot? is front controller same as dispatcher servlet?"* [Q45] · *"why springboot needed front controller and why fastapi and express doesn't?"* [Q41] · *"what's the similar component in python+fastapi and node+express?"* [Q46] · *"why do we need this dispatchservlet in spring boot and not in js(express) and python+fastapi?"* [Q48] · *"i think this dispatchservlet is available automatically without writing code for this?"* [Q47]

### W2.1 What the Front Controller pattern is [Q45]

A software design pattern where **a single centralized component handles all incoming HTTP requests** for an application.

**Why it exists.** In early Java web development every route needed its **own servlet** — `LoginServlet`, `ProfileServlet`, `CartServlet` — each declared in `web.xml`. This became unmaintainable, and worse, common concerns (security, logging, data formatting, routing, encoding) had to be **manually repeated inside every single servlet**.

The Front Controller solves this by acting as a gatekeeper/receptionist: it catches every request first, performs all the common plumbing, and *then* hands off to a specific worker.

### W2.2 Is the Front Controller the same as the DispatcherServlet? [Q45]

**Yes — with one clarification worth internalising:**

> **Front Controller** = the conceptual **design pattern**.
> **`DispatcherServlet`** = the actual **Java class** in Spring that implements it.

Same thing in the Spring ecosystem. Spring Boot registers exactly **one** `DispatcherServlet`, mapped to `/`, intercepting all traffic. You don't write security checks, internationalisation, or URL parsing because the `DispatcherServlet` orchestrates it by delegating to auxiliary components.

### W2.3 Front Controller vs `@Controller` — the two "controllers" [Q45]

They both say "controller" but operate at completely different levels.

| Feature | **Front Controller** (`DispatcherServlet`) | **Spring Controller** (`@Controller` / `@RestController`) |
|---|---|---|
| **Quantity** | **exactly one** per application | **many** — as many as your domain needs |
| **Role** | global **infrastructure manager** | local **worker / handler** |
| **Scope** | intercepts **every** HTTP request | only the paths it's mapped to (`@GetMapping("/users")`) |
| **Who writes it** | **Spring** | **you** |
| **Responsibilities** | URL parsing, request↔object conversion, global exception handling, routing, view rendering | actual business/domain logic |

**The restaurant analogy** [Q45]:
1. **The client (customer)** places an order.
2. **The Front Controller (`DispatcherServlet`)** is the **host/receptionist** — greets the customer, validates the request, checks the menu listings, routes the order to the right kitchen station.
3. **The `@Controller`** is the **chef** — doesn't greet customers or take payments; just accepts the order details, cooks (executes business logic), and hands the food back.
4. **The Front Controller** plates it (view resolution / JSON serialisation) and delivers it.

### W2.4 The equivalent component in FastAPI and Express [Q46]

**They all have a front controller.** The difference is only how visible it is.

**Express — the `express()` app instance is the Front Controller:**
```javascript
const express = require('express');
const app = express();            // ◄── THE FRONT CONTROLLER

app.use(express.json());          // global plumbing — done by the front controller

app.get('/users', (req, res) => { // local handler — the "chef"
    res.json({ message: "Fetching users" });
});
```

**FastAPI — the `FastAPI()` app instance (plus the ASGI server) is the Front Controller:**
```python
from fastapi import FastAPI

app = FastAPI()                   # ◄── THE FRONT CONTROLLER

@app.get("/users")                # local handler — the "chef"
def get_users():
    return {"message": "Fetching users"}
```

#### The alignment table [Q46, Q41]

| Role | **Spring Boot (Java)** | **Express (Node)** | **FastAPI (Python)** |
|---|---|---|---|
| Lower engine / socket accept | **Tomcat / Jetty** (servlet container) | Node's built-in `http` module (libuv) | **Uvicorn / Hypercorn** (ASGI server, uvloop) |
| Protocol contract | **Servlet API** (`jakarta.servlet`) | `(req, res)` callback | **ASGI** callable `(scope, receive, send)` |
| **Front Controller** | **`DispatcherServlet`** | the `app` from `express()` | the `FastAPI()` / Starlette app |
| Router | `RequestMappingHandlerMapping` | `express.Router` | Starlette `Router` |
| Global plumbing | `Filter` + `HandlerInterceptor` | `app.use(fn)` | ASGI middleware / global `Depends` |
| Handler | `@RestController` method | route callback | path-operation function |
| Configuration style | **declarative / annotation-driven** | imperative / middleware-driven | imperative / decorator-driven |
| Routing mechanism | centralized servlet maps requests to **beans** | **sequential** middleware stack | internal `APIRouter` matching paths to async fns |
| **Visibility** | **highly visible** — named class, appears in logs & config | abstracted behind the router | abstracted behind the app instance |

### W2.5 So why does Java need a *named, visible* one? [Q41, Q48]

This is the real answer to your question, and it's historical rather than technical.

**Java's constraint: the Servlet API came first.**
Java web applications don't talk to the internet directly. They run **inside a servlet container**. That container is a low-level engine that understands **exactly one contract** — `HttpServletRequest` / `HttpServletResponse`. It knows nothing about `@RestController`, `@GetMapping`, or JSON.

So Spring needs an **interpreter**: one servlet registered inside Tomcat that receives the raw `HttpServletRequest`, finds your annotated controller by reflection, converts the HTTP data into your Java objects, and calls your method. That interpreter is the `DispatcherServlet`.

**Before Spring**, you satisfied the container contract yourself — one servlet per screen, or a hand-rolled dispatcher. Spring's contribution was: **register exactly ONE servlet at `/` and do all routing in Java, with annotations.**

**Node and Python had no such pre-existing contract.**
- **Node.js is a network runtime.** `http.createServer(handler)` — the handler **is** the front controller. No external container. And because JavaScript treats functions as first-class values, Express doesn't need a servlet class to map URLs to classes — it maps URLs straight to callbacks.
- **FastAPI** sits on **ASGI** with Uvicorn handling sockets and event loops. Python's decorators and runtime reflection let FastAPI inspect function signatures and bind parameters directly, via Pydantic. No rigid servlet infrastructure to adapt to.

| | Spring Boot (Java) | Node (Express) | Python (FastAPI) |
|---|---|---|---|
| Lower engine | Tomcat/Jetty (servlet container) | Node built-in `http` | Uvicorn (ASGI) |
| **The middleman** | **`DispatcherServlet`** — translates Servlet API → Spring features | **none** — Express handles the Node HTTP stream natively | **none** — FastAPI handles ASGI events natively |
| How routing works | reflective scanning of **class-based annotations** | sequential execution of an **array of middleware** | event loop calling **decorated functions** |

> **In one sentence:** *All three have a front controller. Only Java gives it a name and a class, because only Java had to fit inside a pre-existing container contract that predates the framework.*

### W2.6 You never write it [Q47]

> **Your question:** *"i think this dispatchservlet is available automatically without writing code for this in the spring boot application?"* — **100 % correct.**

`DispatcherServletAutoConfiguration` creates and registers it whenever `spring-boot-starter-web` is on the classpath ([§C1.3](02-spring-core.md#c13-how-auto-configuration-actually-works-q47)). Default mapping: `/`.

**The legacy contrast** [Q47] — this is what Spring Boot removed. Before Boot, you wrote this by hand in `web.xml`:
```xml
<!-- You used to have to write all this just to turn on the Front Controller! -->
<servlet>
    <servlet-name>dispatcher</servlet-name>
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
    <load-on-startup>1</load-on-startup>
</servlet>
<servlet-mapping>
    <servlet-name>dispatcher</servlet-name>
    <url-pattern>/</url-pattern>
</servlet-mapping>
```
…or the Java-config version, `WebApplicationInitializer`. You'll still see both in older codebases and tutorials.

### W2.7 What a Front Controller buys you [+]

Concretely, this is what centralising the entry point gives Spring the *ability* to do — every one of these is impossible if each endpoint is its own servlet:

- **One place for routing** — `@GetMapping` on any bean, anywhere.
- **Uniform JSON handling** — one `ObjectMapper` config applied to every endpoint.
- **Global exception handling** — `@ControllerAdvice` catches from *all* controllers ([§W4.11](#w411-the-exception-path)).
- **Cross-cutting interceptors** — auth, tracing, metrics, MDC.
- **Content negotiation** — the same handler serving JSON or XML by `Accept` header.
- **Consistent argument resolution** — `@PathVariable`, `@RequestParam`, `@RequestBody` work identically everywhere.
- **Observability** — one choke point to time and count every request ([§P5.4](06-spring-production.md#p54-actuator-health-metrics-)).

### W2.8 The three collaborators inside the DispatcherServlet: HandlerMapping, HandlerAdapter, HandlerExecutionChain

> **Your questions, merged:** *"what is HandlerAdapter and how is it related with RequestMappingHandlerAdapter?"* · *"is RequestMappingHandlerMapping the @RequestMapping annotation?"* · *"what is HandlerExecutionChain?"*

The `DispatcherServlet` delegates each step to a **strategy interface**, so it never needs to know what a "controller" looks like:

| Interface | Job | The implementation you use 99% of the time |
|---|---|---|
| `HandlerMapping` | "**which** handler serves this request?" Returns a `HandlerExecutionChain` | `RequestMappingHandlerMapping` |
| `HandlerAdapter` | "**how** do I call that handler?" (resolve arguments, invoke, handle the return value) | `RequestMappingHandlerAdapter` |
| `HandlerExceptionResolver` | "turn this exception into a response" | `ExceptionHandlerExceptionResolver` ([§W4.11](#w411-the-exception-path)) |
| `ViewResolver` | "turn a view name into a `View`" | Thymeleaf's resolver ([§W11](#w11-thymeleaf-and-server-side-rendering-q15-q16)) |

**`@RequestMapping` vs `RequestMappingHandlerMapping`.** 📌 **Correction:** they aren't the same thing. `@RequestMapping` (and `@GetMapping`, …) is just **metadata**, an annotation. `RequestMappingHandlerMapping` is the **class** that reads that metadata at startup from every `@Controller` bean and builds the route table, then looks routes up per request ([§W4.7](#w47-dispatcherservletdodispatch-and-routing)).

**`HandlerAdapter` vs `RequestMappingHandlerAdapter`.** `HandlerAdapter` is the interface; `RequestMappingHandlerAdapter` is the implementation for `@RequestMapping` methods (a `HandlerMethod`). It's the one that runs the argument resolvers, `@InitBinder`, validation, `Method.invoke`, and the return-value handlers ([§W4.8](#w48-json-to-java-object-where-jsonparse-really-lives)–[§W4.10](#w410-invoke-then-java-object-to-json)). Other adapters exist because other handler types exist:

| Handler type | Found by | Called by |
|---|---|---|
| `@RequestMapping` method (`HandlerMethod`) | `RequestMappingHandlerMapping` | `RequestMappingHandlerAdapter` |
| functional `RouterFunction` ([§W4.14](#w414-the-alternative-functional-endpoints--and-why-they-arent-popular)) | `RouterFunctionMapping` | `HandlerFunctionAdapter` |
| `HttpRequestHandler`, e.g. `ResourceHttpRequestHandler` for static files | `SimpleUrlHandlerMapping` | `HttpRequestHandlerAdapter` |
| legacy `Controller` interface | `BeanNameUrlHandlerMapping` | `SimpleControllerHandlerAdapter` |

`DispatcherServlet.getHandlerAdapter(handler)` asks each adapter `supports(handler)` and uses the first that says yes. That is the Adapter pattern: one uniform `handle(...)` call over different handler shapes.

A small correction to the source answer: `handle(...)` returns a `ModelAndView` **or `null`**. For `@ResponseBody`/`ResponseEntity` the body is already written inside the adapter, so it returns `null` and no view is rendered.

**`HandlerExecutionChain`** is what a `HandlerMapping` returns: *the handler plus the interceptors that apply to this request*. Its real fields (from the Framework source) are just:
```java
public class HandlerExecutionChain {
    private final Object handler;                                  // e.g. a HandlerMethod
    private final List<HandlerInterceptor> interceptorList = new ArrayList<>();
    private int interceptorIndex = -1;                             // last interceptor whose preHandle returned true
}
```
```java
// How doDispatch drives it (simplified)
HandlerExecutionChain chain = getHandler(request);           // mapping + matching interceptors (+ CORS, §W9.3)
if (!chain.applyPreHandle(request, response)) return;        // each preHandle in order; on false →
                                                             //   afterCompletion for the ones already passed
ModelAndView mv = adapter.handle(request, response, chain.getHandler());
chain.applyPostHandle(request, response, mv);                // reverse order; skipped on exception
// …render view if any…
chain.triggerAfterCompletion(request, response, ex);         // reverse order, up to interceptorIndex
```
`interceptorIndex` is how Spring knows which interceptors need `afterCompletion`: only those whose `preHandle` returned `true`. The full interceptor story, including what each hook can and cannot do, is in [§W5](#w5-filters-vs-handlerinterceptors).

🐍🟨 FastAPI/Express have only "router finds the function, then calls it". The `HandlerAdapter` layer exists because Spring supports several *kinds* of handlers behind one front controller.

---

## W3. MVC architecture (and hexagonal compared) [Q49–Q54]

> **Your questions, merged:** *"what is mvc architecture in spring boot? explain in detail about each component and why it's needed and how is this better/different from other architecture in java. and also compare this with hexagonal architecture from python"* [Q49] · *"explain me how a request/response looks like from end to end in mvc? and is this mvc pattern followed in other language or framework other than java?"* [Q50] · *"what are the components of spring mvc?"* [Q51] · *(your own flow diagram)* [Q52] · *"give me a complete diagram of spring mvc architecture for http/rest"* [Q53] · *"diagram if we are using grpc"* [Q54]

### W3.1 What MVC is [Q49]

**MVC (Model-View-Controller)** divides an application into three interconnected components, separating the user interface, the business logic, and the data layer. In Spring Boot it's powered by **Spring MVC**, which uses the centralised front-controller servlet (`DispatcherServlet`) to manage the request-response lifecycle.

#### 1. The Model [Q49]

- **What it is:** the data layer **and** the business rules. In Spring this includes your **entity classes** (`@Entity`), **DTOs**, and **service components**.
- **Why it's needed:** without a Model your application has no state, persistence, or logic. It isolates database operations and calculations away from the presentation layer.

#### 2. The View [Q49]

- **What it is:** the presentation layer. For traditional monoliths: template files (Thymeleaf, JSP, FreeMarker). **For modern REST APIs, the "View" is simply the JSON or XML payload** serialized by Spring's `HttpMessageConverter`.
- **Why it's needed:** users and client apps cannot interact with raw Java objects. The View translates Model data into a readable format — HTML for humans, JSON for mobile/frontend.

#### 3. The Controller [Q49]

- **What it is:** the traffic cop and entry point. Accepts HTTP requests, processes input parameters, calls service methods (Model), and decides which View or data response to return. Defined with `@Controller` or `@RestController`.
- **Why it's needed:** it's the intermediary. It prevents the View from directly touching the database or business logic, and ensures inputs are validated before they reach the core.

### W3.2 The components of Spring MVC [Q51]

Grouped by responsibility, and all managed by the Spring IoC container.

**1. The core orchestrator (Front Controller)**

| Component | What it does |
|---|---|
| **`DispatcherServlet`** | The heart of Spring MVC. Every HTTP request passes through it first. **It doesn't process the request itself** — it coordinates all the other components. |

**2. Routing and execution**

| Component | What it does |
|---|---|
| **`HandlerMapping`** | The **map maker**. Looks at the URL, HTTP method, and headers and finds the controller method configured to handle it (e.g. `@GetMapping("/profile")`). |
| **`HandlerAdapter`** | The **executioner**. Different kinds of controller exist; the adapter hides that from the `DispatcherServlet`. It knows how to invoke your specific method, resolve its arguments, and process its return value. |

**3. Your code**

| Component | What it does |
|---|---|
| **`@Controller` / `@RestController`** | Entry point for business logic. Receives data from the adapter, validates, invokes services, returns data or a view name. |
| **`Model` / `ModelAndView`** | The **data carrier**. `Model` is essentially a map passing attributes from Controller to View. `ModelAndView` holds both the data **and** the view name. |

**4. Presentation and serialization**

| Component | What it does |
|---|---|
| **`ViewResolver`** | The **pathfinder** for UI templates. Turns `"home"` into a physical file by applying a prefix (`/templates/`) and suffix (`.html`). |
| **`View`** | The final renderer. Merges model data into the template and produces the HTML. |
| **`HttpMessageConverter`** | The **API data translator**. For `@RestController`, the `ViewResolver` is bypassed entirely — `MappingJackson2HttpMessageConverter` serializes Java return objects into JSON (Boot 4: `JacksonJsonHttpMessageConverter`, see [§W8.3](#w83-httpmessageconverter-and-jackson-who-actually-writes-the-json)). |

**5. Cross-cutting utilities**

| Component | What it does |
|---|---|
| **`HandlerInterceptor`** | Pre- and post-processing. Run custom code before a controller is hit or after a view is rendered — logging, metrics, token checks. |
| **`HandlerExceptionResolver`** | The **global safety net**. Catches any exception thrown during the lifecycle and maps it to an error page or HTTP status (e.g. `UserNotFoundException` → 404). |
| `LocaleResolver` | i18n — determines the request's locale |
| `MultipartResolver` | handles `multipart/form-data` file uploads |

### W3.3 End-to-end request/response — the classic (view-rendering) flow [Q50, Q52]

Your diagram from Q52, preserved:

```
[ Client Browser ] ──(1. HTTP Request)──> [ DispatcherServlet ]
                                                 │      ▲
              ┌──────────────────────────────────┘      │
              ▼                                         │
     [ HandlerMapping ] <──(2. Find Controller)─────────┘
              │
              ▼
       [ Controller ] ────(3. Process Logic)───> [ Service / DB Layer ]
              │
              └───────────(4. Return Model & View Name)─┐
                                                        ▼
[ Client Browser ] <──(7. HTML Response)── [ DispatcherServlet ]
                                                 │      ▲
              ┌──────────────────────────────────┘      │
              ▼                                         │
      [ ViewResolver ] ───(5. Resolve Physical View)────┘
              │
              ▼
           [ View ] <─────(6. Render Data with Model)
```

**The seven steps** [Q50, Q52]:

1. **The request arrives.** A client sends `GET /users/5`. The **`DispatcherServlet`** intercepts it as the single entry point.
2. **Routing lookup.** The `DispatcherServlet` queries **`HandlerMapping`**, which scans your routing annotations (`@GetMapping("/users/{id}")`) and identifies the exact Controller class and method. It returns that metadata.
3. **Execution delivery.** The `DispatcherServlet` passes the request to the **`HandlerAdapter`**, which actually invokes the controller method and handles tasks like converting incoming JSON into Java objects (via Jackson).
4. **Controller execution.** The Controller method triggers. It extracts parameters, validates incoming data, and calls the appropriate **Service** layer component.
5. **Business & data processing.** The Service executes business rules and talks to the **Repository** to fetch or save Model data. The data flows back up to the Controller.
6. **Determining the output:**
   - **REST API (`@RestController`):** the Controller returns the raw Java object. The `HandlerAdapter` intercepts it and uses an **`HttpMessageConverter`** to serialize it into JSON or XML. **The UI rendering phase is skipped completely.**
   - **Monolith UI (`@Controller`):** the Controller returns a **`ModelAndView`** (model data + a view name string like `"profile"`). The `DispatcherServlet` sends the name to a **`ViewResolver`** (Thymeleaf) to fetch the HTML page and merge it with the data.
7. **The response is sent.** The `DispatcherServlet` wraps the final output (JSON payload or rendered HTML) into an HTTP Response and sends it back to the client.

### W3.4 The complete REST/JSON architecture diagram [Q53]

In a REST architecture the traditional `ViewResolver` and templates are **completely bypassed**. Java objects returned by your code are serialized straight into a text stream by an `HttpMessageConverter`.

```
                 [ Client (Browser / Postman / Mobile App) ]
                     │                                 ▲
       1. HTTP POST  │                                 │ 8. HTTP Response
       (JSON String) │                                 │ (JSON String)
                     ▼                                 │
         ┌─────────────────────────────────────────────────────────┐
         │                    DispatcherServlet                    │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
        2. Find      │                                 │ 7. Return Serialized
        Route        │                                 │    JSON Stream
                     ▼                                 │
         ┌───────────────────────┐                     │
         │    HandlerMapping     │                     │
         └───────────┬───────────┘                     │
                     │                                 │
        3. Return    │                                 │
        Execution    │                                 │
        Chain        ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │                    HandlerAdapter                       │
         │             (RequestMappingHandlerAdapter)              │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
                     │ Uses                            │ Uses
                     ▼                                 ▼
         ┌───────────────────────┐         ┌───────────────────────┐
         │  HttpMessageConverter │         │  HttpMessageConverter │
         │   (Jackson / JSON)    │         │   (Jackson / JSON)    │
         └───────────┬───────────┘         └───────────▲───────────┘
                     │                                 │
        4. Deserializes JSON                           │ 6. Serializes Java
           into Java Object                            │    Object to JSON
                     ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │             Controller Layer (@RestController)          │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
                     │ 5. Invokes                      │ Returns Data
                     │    Business Logic               │ (Java DTO/Entity)
                     ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │                 Service Layer (@Service)                │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
                     │ Queries /                       │ Returns Data
                     │ Saves Data                      │ (Java Entity)
                     ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │            Repository Layer (@Repository)               │
         └───────────────────────────┬─────────────────────────────┘
                                     │
                                     ▼
                               [ Database ]
```

**The step-by-step for REST** [Q53]:

1. **Inbound.** The client transmits a raw, stringified JSON payload (`{"name": "Alice"}`). `DispatcherServlet` intercepts.
2. **Route matching.** `HandlerMapping` finds which controller method maps to the URL + HTTP method.
3. **Delegation.** `DispatcherServlet` passes the request context to `RequestMappingHandlerAdapter`, which orchestrates data binding and execution.
4. **JSON deserialization.** The adapter sees the parameter is annotated `@RequestBody` and invokes `MappingJackson2HttpMessageConverter`, which calls Jackson's `ObjectMapper` to parse the JSON into a concrete Java object.
5. **Business logic.** The adapter invokes your `@RestController` method with the Java object. It forwards down to the Service Layer, which hits the Repository Layer.
6. **Return, bypassing the View.** The Controller returns a plain Java object (DTO/Entity) instead of a view template. Because it's a `@RestController`, Spring knows not to look for an HTML page.
7. **JSON serialization.** The adapter routes the returned object back through the `HttpMessageConverter`; Jackson serializes it to a JSON string.
8. **Outbound.** The JSON is written into the HTTP response body with `Content-Type: application/json` and returned to the client.

> 📌 A precision note on step 3→4, refining what you wrote in Q50: you said *"HandlerAdapter from DispatcherServlet convert the incoming stringify json to java object using jackson."* Almost — the adapter **delegates**. The precise chain is:
> `RequestMappingHandlerAdapter` → **`RequestResponseBodyMethodProcessor`** (the `HandlerMethodArgumentResolver` that handles `@RequestBody`) → **`MappingJackson2HttpMessageConverter`** → **Jackson `ObjectMapper`**. Knowing that chain by name is what lets you set a useful breakpoint ([§W4.16](#w416-debugging-cheatsheet-where-to-put-a-breakpoint)).
>
> *(Boot 4 / Framework 7: `JacksonJsonHttpMessageConverter` → Jackson 3 `JsonMapper`. Same chain, new names.)*

### W3.5 The gRPC architecture diagram [Q54]

When you swap HTTP REST/JSON for gRPC, **the entire Spring MVC framework is bypassed** — no `DispatcherServlet`, no `HandlerMapping`, no `HandlerAdapter`, no `HttpMessageConverter`. gRPC uses an HTTP/2 server (typically **Netty**) with persistent, multiplexed binary streams.

```
                 [ Client (gRPC Stub Client / Mobile App) ]
                     │                                 ▲
       1. RPC Call   │                                 │ 8. Binary Stream
       (Protobuf     │                                 │ (Protobuf Response)
       Binary)       ▼                                 │
         ┌─────────────────────────────────────────────────────────┐
         │              HTTP/2 Server (e.g., Netty)                │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
        2. Routes    │                                 │ 7. Pipes Binary
        Stream       │                                 │    Data Back
                     ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │             Generated gRPC Server Stub                  │
         │          (e.g., UserServiceGrpc.UserImplBase)           │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
                     │ Uses                            │ Uses
                     ▼                                 ▼
         ┌───────────────────────┐         ┌───────────────────────┐
         │   Protobuf Engine     │         │    Protobuf Engine    │
         │   (Binary Decoder)    │         │    Binary Encoder     │
         └───────────┬───────────┘         └───────────▲───────────┘
                     │                                 │
        3. Deserializes Binary                         │ 6. Serializes Java
           into Java Protobuf                          │    Protobuf Object
           Request Object                              │    to Binary
                     ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │          gRPC Service Impl Layer (@GrpcService)         │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
                     │ 4. Invokes                      │ Returns Data
                     │    Business Logic               │ (Java DTO/Entity)
                     ▼                                 │
      =================================================================
      ▼  THE UNIFIED CORE MODEL (identical to your MVC app)          ▼
         ┌─────────────────────────────────────────────┴───────────┐
         │                 Service Layer (@Service)                │
         └───────────┬─────────────────────────────────▲───────────┘
                     │                                 │
                     ▼                                 │
         ┌─────────────────────────────────────────────┴───────────┐
         │            Repository Layer (@Repository)               │
         └───────────────────────────┬─────────────────────────────┘
                                     ▼
                               [ Database ]
```

**Step by step** [Q54]:

1. **Inbound.** The client executes a Remote Procedure Call, sending a compressed, binary-serialized **Protocol Buffers** payload over a **persistent HTTP/2** connection.
2. **Server routing.** The request hits the **Netty** HTTP/2 server running inside Spring Boot, which identifies the RPC service path.
3. **Binary deserialization.** It bypasses all Spring MVC web logic and lands in the **generated gRPC server stub** (compiled from your `.proto`). The Protobuf engine decodes the binary stream into a strongly-typed Java Protobuf request object.
4. **Endpoint invocation.** The stub calls your implementation class (`@GrpcService`, or `@Component`, depending on the library — e.g. `grpc-spring-boot-starter`).
5. **Entering the unified core.** Your gRPC impl class plays exactly the role your REST Controller did — unpacks the request, coordinates data, calls your standard `@Service` layer. **Everything below this line is identical.** Domain rules, validations, and database interactions do not change.
6. **Binary serialization.** Data returns up; the impl builds a Java Protobuf response object; the engine serializes it into binary.
7–8. **Outbound.** Netty pushes the binary payload down the open, multiplexed HTTP/2 stream to the client stub.

**Summary comparison** [Q50]:

| | Path |
|---|---|
| **Spring MVC (JSON)** | Text (JSON) → HTTP/1.1 or 2 → Tomcat/Jetty → `DispatcherServlet` → Jackson converter → Controller → Service |
| **gRPC** | Binary (Protobuf) → strict HTTP/2 → Netty → generated gRPC stub → Service |

💡 **The architectural lesson, and it's the important one:** your `@Service` and `@Repository` layers are **transport-agnostic**. Swapping REST for gRPC replaces only the top adapter. That observation is *exactly* the hexagonal architecture insight in [§W3.9](#w39-hexagonal-architecture-ports-and-adapters-q49) — Spring's layering gets you most of the way there for free.

### W3.6 Your specific questions about MVC mapping [Q50]

> *"is jackson serialization/deserialization comes under view of mvc pattern of spring?"*

**Conceptually yes; architecturally no — and the distinction matters.**

- **Conceptually:** in a REST API you return raw data, and the client expects JSON. Jackson (via `HttpMessageConverter`) plays the **View role**: it takes Model data and transforms it into the final presentation format.
- **Architecturally, `@ResponseBody` *bypasses* view resolution entirely.** When `RequestResponseBodyMethodProcessor` writes the response it calls `mavContainer.setRequestHandled(true)`, which tells `DispatcherServlet` the response is already written — so **no `ViewResolver` and no `View` object are ever consulted**. An `HttpMessageConverter` is *not* a `View`; they're different interfaces at different points in the pipeline.
- 📌 There *is* a real `View` that produces JSON — `MappingJackson2JsonView` — but it's only used in the non-`@ResponseBody` content-negotiation flow, which is rare today.

> *"and business logic and db layer (using repository) must lie in model layer of mvc pattern?"*

**Yes.** In classic MVC theory, everything that is neither input routing (Controller) nor presentation rendering (View) **is the Model**. So your **Service layer** (business logic) and **Repository/DAO layer** (database access) are both sub-components inside the Model.

> *"is model layer is also called as service layer?"*

**No.** The Service layer is just *part* of the Model. Calling the whole Model "the service layer" is too narrow. **Model is an umbrella term** covering:
- **Core entities** (the data itself)
- **Repositories** (database access)
- **Services** (business logic)

> *"spring security does it's validation in model layer?"*

**No — it primarily happens *before* the Controller.** Spring Security operates as a chain of **Servlet Filters**. A request passes through the security filter chain **before** the `DispatcherServlet` ever hands it to your Controller or Model.

*(Caveat: method-level security like `@PreAuthorize` on a `@Service` method does execute inside the Model layer, via an AOP proxy. But the bulk of authentication and URL protection happens outside MVC entirely.)* Full detail in [§S1.2](05-spring-security.md#s12-the-architecture-the-servlet-filter-chain-q34).

### W3.7 Where does business logic go: controller or model?

> **Your question:** *"should business logic be written in controller or model?"*

**In the Model layer, concretely in `@Service` classes. Keep the controller thin.** The controller's job is HTTP translation only:

| Controller does ✅ | Controller does not ❌ |
|---|---|
| map the URL, read path/query/body, trigger validation (`@Valid`) | compute prices, apply discounts, check stock |
| call **one** service method | call repositories directly and orchestrate several of them |
| map the result to a response DTO / status | open transactions (`@Transactional` belongs on the service) |
| | catch exceptions to build error JSON (that's `@ControllerAdvice`, [§W8.6](#w86-error-handling-in-both-styles)) |

```java
@RestController
@RequestMapping("/api/orders")
@RequiredArgsConstructor
class OrderController {                                     // thin: HTTP in, HTTP out
    private final OrderService service;

    @PostMapping @ResponseStatus(HttpStatus.CREATED)
    OrderDto place(@Valid @RequestBody PlaceOrderRequest req) {
        return service.place(req);
    }
}

@Service
@RequiredArgsConstructor
class OrderService {                                        // the business rules live here
    private final OrderRepository orders;
    private final InventoryClient inventory;

    @Transactional
    public OrderDto place(PlaceOrderRequest req) {
        if (!inventory.inStock(req.sku(), req.qty())) throw new OutOfStockException(req.sku());
        Order o = orders.save(Order.create(req.customerId(), req.sku(), req.qty()));
        return OrderDto.from(o);
    }
}
```
**Why:** the same rule is then reusable from a gRPC endpoint, a Kafka consumer or a scheduled job ([§W3.5](#w35-the-grpc-architecture-diagram-q54)), testable without HTTP, and transactional through the service proxy ([§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)). Rules that concern one entity's own state (e.g. `order.cancel()` refusing if already shipped) can live **on the entity itself** (a "rich domain model"). The service then orchestrates across entities and external systems.

🐍🟨 Same as FastAPI's "keep path operations thin, put logic in a service module" and Express's routes → controllers → services layering.

### W3.8 How Spring MVC compares to other Java architectures [Q49]

Java web development has evolved a lot. Here's how Spring Boot MVC stacks up against what came before:

| Metric | **Spring Boot MVC** (Action-Based) | **Traditional Servlet/JSP** (Early Java) | **JavaServer Faces (JSF)** (Component-Based) |
|---|---|---|---|
| **Separation of concerns** | **High.** Absolute boundary between logic, data, presentation. | **Low.** Often "spaghetti code" with Java logic embedded inside HTML files (scriptlets). | **Medium.** Focuses on UI component state, binding logic tightly to views. |
| **Developer productivity** | **Extremely high.** Auto-configuration, embedded server, simple annotations. | **Low.** Manual `web.xml`, manual parsing, heavy boilerplate. | **Medium.** Complex lifecycle phases make debugging tedious. |
| **Testing** | **Excellent.** Controllers, services, models unit-tested in isolation with `MockMvc`. | **Difficult.** Required running a full heavy servlet container. | **Complex.** Requires mocking UI component trees and page lifecycles. |

[+] Two more you'll hear named: **Struts 1/2** (the action-based framework Spring MVC displaced) and **EJB 2** (the notoriously heavyweight enterprise component model whose pain directly motivated Spring's creation in 2003 — Rod Johnson's book was literally titled *J2EE Development **without** EJB*).

### W3.9 Hexagonal architecture (Ports and Adapters) [Q49]

While Spring Boot MVC is the default blueprint for Java web apps, Python applications (FastAPI/Flask + SQLAlchemy) frequently lean into **Hexagonal Architecture**, also called **Ports and Adapters**.

```
  Spring Boot MVC (Layered Top-to-Bottom)       Hexagonal Architecture (Inside-Out)

         [ Client / Browser ]                                  [ Adapters ]
                 │                                        ┌───────────────────┐
                 ▼                                        │  HTTP / FastAPI   │
          ┌──────────────┐                                └─────────┬─────────┘
          │  Controller  │                                          │ (Drives)
          └──────┬───────┘                                          ▼
                 │                                        ┌───────────────────┐
                 ▼                                        │   Inbound Port    │
          ┌──────────────┐                                └─────────┬─────────┘
          │   Service    │                                          │
          └──────┬───────┘                                ┌─────────▼─────────┐
                 │                                        │    Core Domain    │
                 ▼                                        │  (Pure Business)  │
          ┌──────────────┐                                └─────────▲─────────┘
          │  Repository  │                                          │
          └──────┬───────┘                                ┌─────────┴─────────┐
                 │                                        │   Outbound Port   │
                 ▼                                        └─────────▲─────────┘
            [ Database ]                                            │ (Driven)
                                                          ┌─────────┴─────────┐
                                                          │ ORM / PostgreSQL  │
                                                          └───────────────────┘
                                                               [ Adapters ]
```

#### The three core differences [Q49]

**1. Direction of dependency.**
In Spring Boot MVC dependencies flow **linearly downwards**: Controller → Service → Repository. The business logic **depends directly on the database access layer**.
In Hexagonal, dependencies flow **inwards**. The core domain sits in the centre and **depends on nothing outside itself**; external services (databases, UI) implement "Ports" *defined by the core*.

**2. Database coupling.**
Switching from SQL to MongoDB in Spring Boot MVC likely means modifying your Entity classes and Repository layer, because the architecture assumes database models are foundational. In Hexagonal, the core business model stays **completely untouched** — you swap an external database **Adapter**.

**3. Framework intrusion.**
Spring Boot MVC relies heavily on framework annotations (`@Autowired`, `@Service`, `@Entity`) embedded deep in every layer. Python hexagonal implementations deliberately keep the core domain **free of framework dependencies**, so the domain logic stays pure, framework-agnostic Python.

#### [+] The honest assessment, and how to do hexagonal *in* Spring

**Why hexagonal is more popular in Python than in Java:** FastAPI gives you *no* architecture, so teams impose one. Spring hands you MVC + layering on day one, so the itch never develops. It's a vacuum effect, not a language property.

**You can absolutely do hexagonal in Spring** — the trick is to own the repository *interface* in your domain:

```
com.example.orders
├── domain/                       ← ZERO Spring imports, zero JPA imports
│   ├── Order.java                    a plain record/class
│   ├── OrderService.java             pure business logic
│   └── port/
│       ├── OrderRepository.java      ◄── INTERFACE, owned by the DOMAIN (outbound port)
│       └── PaymentGateway.java       ◄── INTERFACE, owned by the DOMAIN (outbound port)
│
├── adapter/in/
│   └── OrderController.java      ← @RestController — a DRIVING adapter
│
└── adapter/out/
    ├── JpaOrderRepository.java   ← implements domain.port.OrderRepository — DRIVEN adapter
    └── StripePaymentGateway.java ← implements domain.port.PaymentGateway
```

The single arrow that changes everything:

```
NAIVE SPRING LAYERING                  HEXAGONAL IN SPRING
  OrderService                            OrderService
       │ depends on                            │ depends on
       ▼                                       ▼
  JpaRepository<Order, Long>            OrderRepository   ◄── YOUR interface, in the domain
  (a Spring Data type)                        ▲
  ⇒ domain is coupled to JPA                  │ implements
                                        JpaOrderRepository ◄── infrastructure depends on domain
                                        ⇒ the arrow is INVERTED
```

**Spring's DI is what makes this cheap** — your domain declares `OrderRepository`, and the container injects the JPA adapter at startup. You get the inversion without writing any wiring code.

**When is it worth it?**

| Situation | Recommendation |
|---|---|
| CRUD service, one datastore, one entry point | **Plain layering.** Hexagonal is ceremony here. |
| Rich domain, long-lived, multiple entry points (REST + Kafka + gRPC + cron) | **Hexagonal pays for itself.** |
| You need to unit-test business rules with zero Spring context | **Hexagonal** — the domain has no framework deps, so tests are plain JUnit and run in milliseconds |
| You genuinely expect to swap datastores | **Hexagonal** (though be honest: this is rarer than people claim) |

Related names for the same family of ideas: **Onion Architecture**, **Clean Architecture** (Uncle Bob), **DDD's layered architecture**. They differ in vocabulary far more than in substance. The invariant is the **Dependency Rule**: *source code dependencies point only inwards, toward higher-level policy.*

### W3.10 Is MVC followed outside Java? [Q50]

**Yes, absolutely.** MVC is one of the most widely adopted architectural patterns in software engineering and underpins web frameworks in almost every major language.

| Language | Framework | How MVC is applied |
|---|---|---|
| **Python** | **Django** | Uses a variation called **MVT (Model-View-Template)**. Django's "View" acts like the traditional Java **Controller** (handles logic); the "Template" acts like the Java **View** (UI presentation). ⚠️ The naming is genuinely confusing — Django's *View* is a *Controller*. |
| **Ruby** | **Ruby on Rails** | The quintessential MVC framework that popularised the pattern globally. "Convention over Configuration" automatically maps Controllers to Models and Views without manual routing. |
| **C# (.NET)** | **ASP.NET Core MVC** | Architecturally almost identical to Spring Boot. Routing controllers, strongly-typed Models, Razor as the View engine. |
| **PHP** | **Laravel** | Standard MVC; a web routing file routes requests into Controller classes that interface with Eloquent (Model) and Blade (View). |
| **JS/TS** | **NestJS** | Deeply inspired by Angular and Spring Boot. Brings enterprise MVC to Node — `@Controller()`, Services, TypeScript classes as Models. |
| **JS/TS** | **Express** | Not enforced, but the conventional structure is `routes/` + `controllers/` + `models/` — MVC by convention. |
| **Python** | **FastAPI** | Also not enforced. Teams typically impose either MVC-style layering or hexagonal. |

> 💡 The pattern you actually use in Spring Boot every day is better described as **layered architecture** (Controller → Service → Repository) than as textbook MVC — because in a REST API there is no View at all. When a Java developer says "MVC" in 2026 they usually mean "Spring MVC, the library", not the 1979 Smalltalk pattern.

---

## W4. REST Controller — the complete unabstracted request lifecycle [Q★]

> **Your question (from your Google AI Mode link — no answer text was recoverable, so this section is written from scratch):**
> *"how does rest controller works in the springboot and what are the different annotations…? remove the abstraction layer and tell me the low level like call will be made and how socket / network call will be made (how parsing like converting to string i.e stringify before sending to the network and converting to the json before we have the data)… also earlier you had told that using something we can get rid of rest controller then why that approach is not so popular…? how routing will happen, does ordering matter (it matter in python with fast api)? what are the dependency that we need to add in the spring project"*

**Every abstraction removed, with real class names so you can set breakpoints.**

### W4.1 The dependencies you need

```xml
<!-- THE one you need. Brings Spring MVC + Jackson + embedded Tomcat. -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```

That single line transitively pulls in:
```
spring-boot-starter            → core, logging (logback), spring-boot-autoconfigure
spring-boot-starter-json       → jackson-databind, jackson-datatype-jdk8,
                                 jackson-datatype-jsr310 (java.time!),
                                 jackson-module-parameter-names
spring-boot-starter-tomcat     → tomcat-embed-core, tomcat-embed-el, tomcat-embed-websocket
spring-web                     → RestTemplate, HTTP abstractions, HttpMessageConverter
spring-webmvc                  → DispatcherServlet, @Controller, HandlerMapping, …
spring-core / spring-beans / spring-context / spring-aop / spring-expression
```

**The ones you will add next:**

| Dependency | Why |
|---|---|
| `spring-boot-starter-validation` | ⚠️ **`@Valid` / `@NotBlank` do nothing without this.** Split out in Boot 2.3. |
| `spring-boot-starter-test` | JUnit 5, Mockito, AssertJ, `MockMvc`. Included by Spring Initializr. |
| `spring-boot-devtools` | auto-restart on recompile — the `nodemon` equivalent |
| `spring-boot-starter-actuator` | `/actuator/health`, metrics, `/actuator/mappings` |
| `springdoc-openapi-starter-webmvc-ui` | Swagger UI ([§W12](#w12-api-documentation-openapi-and-swagger-q32-q33)) |
| `org.projectlombok:lombok` | `@RequiredArgsConstructor`, `@Slf4j`, `@Getter` |
| `spring-boot-starter-data-jpa` | Hibernate + Spring Data repositories |
| `spring-boot-starter-security` | [§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext) |

**Swap Tomcat for Undertow or Jetty** (same programming model, different server):
```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <exclusions><exclusion>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-tomcat</artifactId>
    </exclusion></exclusions>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-undertow</artifactId>
</dependency>
```

### W4.2 The 30,000-foot view

```
CLIENT                                                            YOUR CODE
  │                                                                   ▲
  │ ① DNS → TCP handshake → TLS handshake                             │
  │ ② raw bytes: "POST /api/orders HTTP/1.1\r\n…\r\n\r\n{...}"        │
  ▼                                                                   │
┌──────────────────────────────────────────────────────────────────┐  │
│ ③ TOMCAT   Acceptor → Poller(Selector) → worker thread           │  │
│            Http11Processor parses bytes → Request/Response       │  │
│            wrapped as HttpServletRequest / HttpServletResponse   │  │
└────────────────────────────┬─────────────────────────────────────┘  │
                             ▼                                        │
┌──────────────────────────────────────────────────────────────────┐  │
│ ④ FILTER CHAIN  CharacterEncodingFilter → FormContentFilter →    │  │
│                 RequestContextFilter → [Spring Security] →       │  │
│                 metrics filter (Boot 2: WebMvcMetricsFilter;     │  │
│                 Boot 3+: ServerHttpObservationFilter)            │  │
└────────────────────────────┬─────────────────────────────────────┘  │
                             ▼                                        │
┌──────────────────────────────────────────────────────────────────┐  │
│ ⑤ DispatcherServlet.doDispatch()                                 │  │
│      ⑥ HandlerMapping      → which method?                       │  │
│      ⑦ HandlerAdapter      → resolve arguments                   │  │
│      ⑧ HttpMessageConverter→ JSON bytes → Java object ("parse")  │  │
│      ⑨ Validator           → @Valid                              │  │
│      ⑩ Method.invoke()     ─────────────────────────────────────────┤ YOUR
│      ⑪ ReturnValueHandler  → content negotiation                 │  │ CONTROLLER
│      ⑫ HttpMessageConverter→ Java object → JSON bytes ("stringify")│ │
└────────────────────────────┬─────────────────────────────────────┘  │
                             ▼                                        │
  ⑬ OutputBuffer → Http11OutputBuffer → NioChannel.write() → socket   │
  ⑭ keep-alive: connection stays open for the next request            │
```

### W4.3 What's actually on the wire

There is **no "JSON object" on the network.** There is only a sequence of bytes. Both sides agree on the meaning via `Content-Type`.

```
POST /api/v1/orders HTTP/1.1\r\n
Host: api.example.com\r\n
Content-Type: application/json\r\n
Content-Length: 51\r\n
Accept: application/json\r\n
Connection: keep-alive\r\n
\r\n
{"customerId":"c-42","items":[{"sku":"A","qty":2}]}
```

- `\r\n` (CRLF) terminates every line; a **blank line** separates headers from body.
- `Content-Length` tells the receiver how many body bytes to read (alternative: `Transfer-Encoding: chunked`).
- For `application/json`, **UTF-8 is the default and only sane encoding** (RFC 8259).
- HTTP/2 replaces this text framing with binary **HPACK**-compressed frames, but the semantic model is identical.

### W4.4 Tomcat accepts the socket

```
                  port 8080
                     │
        ┌────────────▼────────────┐
        │  Acceptor thread        │   ServerSocketChannel.accept()  — ONE thread, blocking
        └────────────┬────────────┘
                     ▼
        ┌─────────────────────────┐
        │  Poller (NIO Selector)  │   registers the socket, waits for OP_READ
        └────────────┬────────────┘   — a FEW threads handle THOUSANDS of sockets
                     ▼  socket is readable
        ┌─────────────────────────┐
        │  Worker thread pool     │   "http-nio-8080-exec-1" … "-exec-200"
        │  (max 200 by default)   │   ← THIS is the thread your controller runs on
        └────────────┬────────────┘
                     ▼
              Http11Processor.service()
```

Key classes: `org.apache.tomcat.util.net.NioEndpoint` (`Acceptor`, `Poller`), `org.apache.coyote.http11.Http11Processor`.

⚠️ **The important nuance:** Tomcat's *socket handling* is non-blocking (NIO), but **request processing is blocking** — one worker thread is dedicated to a request from the moment it's dispatched until the response is written, **including every blocking DB and HTTP call inside**. That's the capacity ceiling in [§W1.6](#w16-the-default-tomcat-knobs-).

With `spring.threads.virtual.enabled=true` on Boot 3.2+/Java 21+, that worker is a **virtual** thread and the ceiling largely evaporates.

### W4.5 HTTP parsing into `HttpServletRequest`

`Http11Processor` and `Http11InputBuffer` parse the byte stream:
1. **Request line** — `POST /api/v1/orders HTTP/1.1`
2. **Headers** — into a `MimeHeaders` structure. ⚠️ Header names/values are decoded as **ISO-8859-1** by default per the old HTTP spec, which is why non-ASCII header values misbehave unless you set `URIEncoding`/`useBodyEncodingForURI`.
3. **Body** — *not read yet.* It stays as an unread `InputStream` over the socket. **This matters** — see [§W4.8](#w48-json-to-java-object-where-jsonparse-really-lives).

The result is `org.apache.catalina.connector.Request`, wrapped in a `RequestFacade` implementing **`jakarta.servlet.http.HttpServletRequest`**. Then `CoyoteAdapter.service()` hands it into the servlet container's valve pipeline: `StandardEngineValve` → `StandardHostValve` → `StandardContextValve` → `StandardWrapperValve` → the filter chain.

### W4.6 The filter chain

Servlet `Filter`s run **before and after** the servlet — this is your `app.use()` / ASGI middleware.

| Filter (typical order) | What it does |
|---|---|
| `OrderedCharacterEncodingFilter` | forces UTF-8 request encoding |
| `WebMvcMetricsFilter` | *(actuator)* starts the request timer. ⚠️ Boot 2.x only; Boot 3+ replaced it with Micrometer Observation's `ServerHttpObservationFilter` |
| `OrderedFormContentFilter` | ⚠️ parses `x-www-form-urlencoded` bodies for **PUT/PATCH/DELETE** — servlet containers only do it for POST ([§W6.1](#w61-requestparam-vs-requestgetparameter-q55)) |
| `OrderedRequestContextFilter` | binds the request to a `ThreadLocal` so `RequestContextHolder` works anywhere |
| **`FilterChainProxy`** | *(Spring Security)* — the whole security chain, ~15 filters ([§S1.2](05-spring-security.md#s12-the-architecture-the-servlet-filter-chain-q34)) |

```java
@Component
public class CorrelationIdFilter extends OncePerRequestFilter {
    @Override
    protected void doFilterInternal(HttpServletRequest req, HttpServletResponse res, FilterChain chain)
            throws ServletException, IOException {
        String id = Optional.ofNullable(req.getHeader("X-Correlation-Id"))
                            .orElseGet(() -> UUID.randomUUID().toString());
        MDC.put("correlationId", id);          // ← now every log line carries it
        res.setHeader("X-Correlation-Id", id);
        try {
            chain.doFilter(req, res);           // ← everything downstream; omit this to SHORT-CIRCUIT
        } finally {
            MDC.clear();                        // ← MUST clear: the thread is reused!
        }
    }
}
```

**`Filter` vs `HandlerInterceptor`** — you'll be asked this:

| | `Filter` (servlet) | `HandlerInterceptor` (Spring) |
|---|---|---|
| Level | servlet container — **outside** Spring MVC | inside `DispatcherServlet` |
| Sees | every request, incl. static resources & errors | only requests that matched a handler (⚠️ static files served by Spring MVC's `ResourceHttpRequestHandler` *are* handlers, so interceptors run for them too; see [§W5.3](#w53-does-an-interceptor-run-for-every-endpoint)) |
| Knows which controller will run | ❌ | ✅ receives the `HandlerMethod` |
| Can modify the request/response object | ✅ (wrapping) | ❌ can't wrap/replace them; can still set headers/status in `preHandle` |
| Hooks | `doFilter` (before + after) | `preHandle`, `postHandle`, `afterCompletion` |
| Use for | security, encoding, CORS (with Spring Security), correlation IDs | per-handler timing/auditing, reading annotations on the target method, populating the `Model` |

*(Response compression in Boot is done by the embedded server, not by a filter, and route auth belongs in Spring Security rather than an interceptor. The full comparison, decision guide and corrections are in [§W5](#w5-filters-vs-handlerinterceptors).)*

### W4.7 `DispatcherServlet.doDispatch()` and routing

```java
// org.springframework.web.servlet.DispatcherServlet — simplified from the real source
protected void doDispatch(HttpServletRequest request, HttpServletResponse response) {
    processedRequest = checkMultipart(request);              // MultipartResolver

    HandlerExecutionChain mappedHandler = getHandler(processedRequest);   // ⑥ WHICH method?
    if (mappedHandler == null) { noHandlerFound(...); return; }           // → 404

    HandlerAdapter ha = getHandlerAdapter(mappedHandler.getHandler());    // ⑦

    if (!mappedHandler.applyPreHandle(processedRequest, response)) return; // interceptors

    mv = ha.handle(processedRequest, response, mappedHandler.getHandler()); // ⑧⑨⑩⑪⑫

    mappedHandler.applyPostHandle(processedRequest, response, mv);
    processDispatchResult(processedRequest, response, mappedHandler, mv, dispatchException);
}
```

`getHandler()` iterates the registered `HandlerMapping`s **in order**:

| Order | HandlerMapping | Handles |
|---|---|---|
| **0** | **`RequestMappingHandlerMapping`** | your `@GetMapping`/`@PostMapping` methods |
| 1 | `RouterFunctionMapping` | functional endpoints |
| 2 | `BeanNameUrlHandlerMapping` | legacy bean-name URLs |
| LOWEST−1 | `SimpleUrlHandlerMapping` | static resources (`/static/**`, `/webjars/**`) |
| LOWEST | `WelcomePageHandlerMapping` | `index.html` |

At **startup**, `RequestMappingHandlerMapping.afterPropertiesSet()` scans every `@Controller` bean, reads every `@RequestMapping` (and its composed variants), and builds a **`MappingRegistry`**: `RequestMappingInfo` → `HandlerMethod`.

A `RequestMappingInfo` is **not just a path** — it's a conjunction of conditions:

| Condition | From | Mismatch → |
|---|---|---|
| path pattern | `@GetMapping("/orders/{id}")` | 404 |
| HTTP method | `@PostMapping` | **405** Method Not Allowed |
| `consumes` | `consumes = "application/json"` | **415** Unsupported Media Type |
| `produces` | `produces = "application/json"` | **406** Not Acceptable |
| `params` | `params = "version=2"` | 404 |
| `headers` | `headers = "X-API-Key"` | 404 |

💡 **This table explains a real confusion:** when you get a **415** or **406** instead of a 404, it means the path *did* match but a media-type condition didn't.

### W4.8 JSON to Java object (where "JSON.parse" really lives)

`RequestMappingHandlerAdapter` calls `InvocableHandlerMethod.getMethodArgumentValues()`, which walks a chain of **`HandlerMethodArgumentResolver`**s — one per parameter:

| Resolver | Handles |
|---|---|
| `PathVariableMethodArgumentResolver` | `@PathVariable` |
| `RequestParamMethodArgumentResolver` | `@RequestParam`, `MultipartFile` |
| **`RequestResponseBodyMethodProcessor`** | **`@RequestBody`** |
| `RequestHeaderMethodArgumentResolver` | `@RequestHeader` |
| `ServletCookieValueMethodArgumentResolver` | `@CookieValue` |
| `ModelAttributeMethodProcessor` | `@ModelAttribute` (form binding) |
| `ServletRequestMethodArgumentResolver` | raw `HttpServletRequest`, `Principal`, `Locale`, `HttpMethod` |
| `PrincipalMethodArgumentResolver` | `Authentication` |
| `PageableHandlerMethodArgumentResolver` | `Pageable` (Spring Data) |

For `@RequestBody`, `RequestResponseBodyMethodProcessor.readWithMessageConverters()`:
1. Reads the request's `Content-Type` (e.g. `application/json`).
2. Walks the registered `HttpMessageConverter`s and picks the first whose `canRead(type, mediaType)` returns true — for JSON, **`MappingJackson2HttpMessageConverter`** (Boot 2.7/3; on Boot 4 it is `JacksonJsonHttpMessageConverter`).
3. Calls `objectMapper.readValue(inputStream, javaType)`.

> ⚠️ **Version note (Jackson):** Boot 2.7 and Boot 3 use Jackson 2 (`MappingJackson2HttpMessageConverter`, `ObjectMapper`, `com.fasterxml.jackson`). **Boot 4 / Framework 7 default to Jackson 3**: `JacksonJsonHttpMessageConverter`, a `JsonMapper` bean, package `tools.jackson`. Jackson 2 support is deprecated there. The class names in this section are the Jackson 2 ones; the flow is identical. Details: [§W8.3](#w83-httpmessageconverter-and-jackson-who-actually-writes-the-json).

> ### ⭐ Directly answering your question about "stringify before sending / parse before we have the data"
>
> **Spring does NOT build an intermediate `String`.**
>
> Your mental model from JS/Python is `JSON.parse(await req.text())` — first materialise the whole body as a string, then parse it. **Spring skips the string entirely.**
>
> - **Inbound:** `ObjectMapper.readValue(InputStream, Class)` creates a **`JsonParser`** that pulls **bytes** straight off the servlet `InputStream` — which is reading from the **socket** — and emits tokens (`START_OBJECT`, `FIELD_NAME`, `VALUE_STRING`…) incrementally, populating your Java object field by field. A 10 MB request body never exists as a 10 MB `String`.
> - **Outbound:** `ObjectMapper.writeValue(OutputStream, object)` uses a **`JsonGenerator`** that writes **UTF-8 bytes** directly to the response stream.
>
> So the real pipeline is:
> ```
> socket bytes → Http11InputBuffer → ServletInputStream → JsonParser → Java object
> Java object  → JsonGenerator → ServletOutputStream → OutputBuffer → socket bytes
> ```
> **`String` never appears.** This is why Java handles large payloads with a flat memory profile.
>
> ⚠️ One practical consequence: because the body is a **one-shot stream**, you can read it **once**. A filter that reads the body to log it will leave `@RequestBody` with an empty stream. The fix is `ContentCachingRequestWrapper`.

**Jackson's mapping rules** — worth knowing since they cause most DTO bugs:

```java
public record OrderRequest(
        @JsonProperty("customer_id") String customerId,   // JSON snake_case → Java camelCase
        List<ItemDto> items,
        @JsonFormat(shape = STRING, pattern = "yyyy-MM-dd") LocalDate deliverBy,
        @JsonIgnore String internalNote                   // never serialised or deserialised
) {}
```
```properties
spring.jackson.property-naming-strategy=SNAKE_CASE     # global snake_case
spring.jackson.default-property-inclusion=non_null     # omit nulls from output
spring.jackson.deserialization.fail-on-unknown-properties=false   # default in Boot: false
spring.jackson.serialization.write-dates-as-timestamps=false      # ISO-8601 for java.time
```
⚠️ Jackson needs either a no-arg constructor + setters, **or** the `jackson-module-parameter-names` module (included by `spring-boot-starter-json`) plus `-parameters` at compile time. Boot sets `-parameters` for you, which is why **records work as DTOs out of the box**.

### W4.9 Validation

If the parameter is annotated `@Valid` or `@Validated`, `RequestResponseBodyMethodProcessor` invokes `LocalValidatorFactoryBean` (Hibernate Validator) **immediately after deserialization**. On failure it throws **`MethodArgumentNotValidException`** → mapped to **400**. Full detail in [§W7](#w7-validation-q55).

### W4.10 Invoke, then Java object to JSON

**The actual invocation** is plain Java reflection:
```java
// InvocableHandlerMethod#doInvoke — this is the real line
ReflectionUtils.makeAccessible(getBridgedMethod());
return getBridgedMethod().invoke(getBean(), args);
//     ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^^^^^^^   ^^^^
//     your method               your        resolved
//                               singleton   arguments
//                               controller
//                               bean
```
That's it. **No magic** — a `java.lang.reflect.Method.invoke` on the singleton bean the container built at startup.

**Return value handling.** `HandlerMethodReturnValueHandlerComposite` picks a handler:

| Return type | Handler | Result |
|---|---|---|
| any object, `@ResponseBody` present | `RequestResponseBodyMethodProcessor` | serialised to the body |
| `ResponseEntity<T>` | `HttpEntityMethodProcessor` | body **+ status + headers** |
| `String` (no `@ResponseBody`) | `ViewNameMethodReturnValueHandler` | treated as a **view name** ([§W11](#w11-thymeleaf-and-server-side-rendering-q15-q16)) |
| `ModelAndView` | `ModelAndViewMethodReturnValueHandler` | view + model |
| `CompletableFuture<T>` / `Callable<T>` / `DeferredResult<T>` | async handlers | frees the Tomcat thread |
| `void` | — | response assumed already written |

**Content negotiation** happens here: `ContentNegotiationManager` → `HeaderContentNegotiationStrategy` reads the `Accept` header, producing a ranked list of acceptable `MediaType`s. It's matched against each converter's `getSupportedMediaTypes()` and the method's `produces`. No overlap → **406**.

Then `MappingJackson2HttpMessageConverter.writeInternal()` → `objectMapper.writeValue(outputStream, obj)` (Boot 4: `JacksonJsonHttpMessageConverter` → `JsonMapper`).

⚠️ Because the body is written and committed here, inside the `HandlerAdapter`, an interceptor's `postHandle` runs **after** the response is already sent and can no longer change headers ([§W5.2](#w52-the-exact-order-of-events)).

⚠️ For `@RestController`, `mavContainer.setRequestHandled(true)` is set, so `processDispatchResult` **skips view resolution entirely** — no `ViewResolver` is consulted. This is the mechanical basis of the “Jackson is the View” discussion in [§W3.6](#w36-your-specific-questions-about-mvc-mapping-q50).

### W4.11 The exception path

Any exception thrown anywhere in `doDispatch` is caught and passed to `HandlerExceptionResolverComposite`, which tries each resolver in order:

| Order | Resolver | Handles |
|---|---|---|
| 0 | **`ExceptionHandlerExceptionResolver`** | your `@ExceptionHandler` / `@ControllerAdvice` methods |
| 1 | `ResponseStatusExceptionResolver` | `@ResponseStatus` on an exception class; `ResponseStatusException` |
| 2 | `DefaultHandlerExceptionResolver` | built-in Spring MVC exceptions → standard status codes |

`DefaultHandlerExceptionResolver` is why you get sensible codes for free:

| Exception | Status |
|---|---|
| `NoHandlerFoundException` | 404 |
| `HttpRequestMethodNotSupportedException` | 405 |
| `HttpMediaTypeNotSupportedException` | 415 |
| `HttpMediaTypeNotAcceptableException` | 406 |
| `MissingServletRequestParameterException` | 400 |
| `MethodArgumentNotValidException` | 400 |
| `MethodArgumentTypeMismatchException` | 400 |
| `HttpMessageNotReadableException` (malformed JSON) | 400 |

If nothing resolves it, the servlet container forwards to `/error`, handled by Boot's `BasicErrorController`. Modern practice is RFC 9457 **`ProblemDetail`** — [§W8.8](#w88-global-exception-handling-with-problemdetail-).

### W4.12 The complete annotation reference

#### Class-level

| Annotation | What it does |
|---|---|
| **`@RestController`** | = **`@Controller` + `@ResponseBody`**. Every method's return value is serialised to the body. |
| **`@Controller`** | A `@Component` stereotype, discovered by component scan. Return values are **view names** unless `@ResponseBody`. |
| **`@RequestMapping("/api/v1/orders")`** | Base path prefix for all methods in the class. |
| `@CrossOrigin(origins = "...")` | CORS headers for this controller. See [§W9](#w9-cors-crossorigin-corsfilter-and-spring-security). |
| `@Validated` | Boot 2.7 / Framework ≤6.0: required to validate `@RequestParam`/`@PathVariable` constraints. ⚠️ Framework 6.1+ validates them **built-in** without it; see [§W7.4](#w74-valid-vs-validated). |
| `@RestControllerAdvice` | = `@ControllerAdvice` + `@ResponseBody` — global exception handling ([§W8.7](#w87-controlleradvice-vs-restcontrolleradvice)). |

#### Method-level: mapping

| Annotation | Equivalent to |
|---|---|
| `@GetMapping("/x")` | `@RequestMapping(path="/x", method=GET)` |
| `@PostMapping` / `@PutMapping` / `@PatchMapping` / `@DeleteMapping` | same pattern |
| `@RequestMapping(path=…, method=…, consumes=…, produces=…, params=…, headers=…)` | the general form |
| `@ResponseStatus(HttpStatus.CREATED)` | sets the status when the method returns normally |
| `@ResponseBody` | on a method in a plain `@Controller` |

#### Parameter-level

```java
@PostMapping(path = "/{tenantId}/orders", consumes = APPLICATION_JSON_VALUE,
                                          produces = APPLICATION_JSON_VALUE)
@ResponseStatus(HttpStatus.CREATED)
public OrderDto create(
        @PathVariable String tenantId,                          // /{tenantId}
        @RequestParam(defaultValue = "false") boolean dryRun,   // ?dryRun=true
        @RequestHeader("X-Request-Id") String requestId,        // header
        @CookieValue(value="sid", required=false) String sid,   // cookie
        @Valid @RequestBody CreateOrderRequest body,            // JSON body + validation
        Authentication auth,                                    // Spring Security principal
        HttpServletRequest raw) {                               // escape hatch (avoid)
    ...
}
```

| Annotation | Source | Notes |
|---|---|---|
| `@PathVariable` | URI template segment | Name inferred from the parameter name — **requires `-parameters`**, which Boot sets. Otherwise `@PathVariable("id")`. |
| `@RequestParam` | query string **or** form body | `required` (default true), `defaultValue`. See [§W6.1](#w61-requestparam-vs-requestgetparameter-q55). |
| `@RequestBody` | request body, deserialised | one per method |
| `@RequestHeader` | a header | |
| `@CookieValue` | a cookie | |
| `@RequestPart` | one part of `multipart/form-data` | for file + JSON uploads |
| `@ModelAttribute` | binds form fields onto an object | [§W6.4](#w64-data-binding-for-html-forms-q55) |
| `@Valid` / `@Validated` | triggers Bean Validation | [§W7](#w7-validation-q55) |
| `@MatrixVariable` | `;k=v` URI matrix params | rare |

#### `ResponseEntity<T>` — the programmatic alternative

```java
@GetMapping("/{id}")
public ResponseEntity<OrderDto> get(@PathVariable String id) {
    return service.find(id)
        .map(dto -> ResponseEntity.ok()
                .eTag(dto.version())
                .cacheControl(CacheControl.maxAge(60, SECONDS))
                .body(dto))
        .orElseGet(() -> ResponseEntity.notFound().build());
}

@PostMapping
public ResponseEntity<OrderDto> create(@Valid @RequestBody CreateOrderRequest req) {
    OrderDto created = service.create(req);
    return ResponseEntity.created(URI.create("/api/orders/" + created.id())).body(created);
}
```
Use `ResponseEntity` when the **status or headers vary at runtime**; use a plain return type + `@ResponseStatus` when they're fixed. The full comparison and error handling: [§W8.5](#w85-responseentity-vs-plain-return--responsestatus).

### W4.13 Routing: does declaration order matter?

> **Your question:** *"how routing will happen, does ordering matter (it matter in python with fast api)?"*

**In Spring: NO. In FastAPI and Express: YES.** This is a genuine, load-bearing difference, and it will surprise you in both directions.

#### The demonstration

```java
// Spring — BOTH work, in EITHER declaration order
@GetMapping("/users/{id}") public User byId(@PathVariable String id) { ... }
@GetMapping("/users/me")   public User me() { ... }
```
`GET /users/me` → calls **`me()`**. ✅ Order is irrelevant.

```python
# FastAPI — the FIRST match wins
@app.get("/users/{id}")
def by_id(id: str): ...
@app.get("/users/me")
def me(): ...
```
`GET /users/me` → calls **`by_id(id="me")`**. ❌ You **must** declare `/users/me` first.

```javascript
// Express — same as FastAPI. First registered route wins.
app.get('/users/:id', byId);
app.get('/users/me',  me);     // unreachable
```

#### Why the difference — the algorithm

| | Spring MVC | FastAPI / Starlette, Express |
|---|---|---|
| When routes are registered | **all at startup**, into a `MappingRegistry` | appended to an ordered **list** |
| At request time | collect **ALL** matching mappings, then **sort by specificity** | iterate the list, take the **first** match |
| Winner | **most specific** | **first declared** |
| Two equally-specific matches | 💥 **`IllegalStateException: Ambiguous handler methods mapped for '/users/me'`** — at request time | silently shadowed, no warning |

Spring's sort uses **`PathPattern.SPECIFICITY_COMPARATOR`** (the default since Spring 6; the older `AntPathMatcher` is deprecated). Scoring, **lower = more specific = wins**:

| Element | Score |
|---|---|
| URI variable `{id}` | 1 |
| single wildcard `*` | 1 |
| double wildcard `**` | 2 |

Tie-breakers: longer patterns beat shorter ones; more URI variables beat wildcards. The catch-all `/**` is always sorted **last** and excluded from scoring. So `/users/me` (0 points, all literal) beats `/users/{id}` (1 point).

```
GET /users/me
      │
      ▼
  ALL matching RequestMappingInfos collected:
      /users/me      → score 0   (all literal)
      /users/{id}    → score 1   (one URI variable)
      /users/**      → sorted last
      │
      ▼  sort by PathPattern.SPECIFICITY_COMPARATOR
  BEST MATCH: /users/me   ✅ regardless of declaration order
```

**The trade-off, stated honestly:**
- ✅ Spring is **safer** — no accidental shadowing, and true ambiguity is a loud error instead of silent misrouting.
- ⚠️ Spring can **surprise you** — "most specific" isn't always the one you had in mind, and you can't force a route to win by declaring it first.
- ⚠️ It's marginally slower (though direct-path lookups on non-pattern URLs hit an O(1) map first).

⚠️ **One more Spring 6 / Boot 3 change:** **trailing-slash matching was removed.** `/users` no longer matches `/users/`. Under Boot 2 it did. This breaks clients on upgrade and is a known migration gotcha.

### W4.14 The alternative: functional endpoints — and why they aren't popular

> **Your question:** *"earlier you had told that using something we can get rid of rest controller then why that approach is not so popular and why rest controller is popular choice in industry"*

You **can** build a REST API in Spring with **zero annotated controllers**, using **`RouterFunction`** (WebMVC.fn, available since Spring 5.2 for servlet stacks; the original home is WebFlux).

```java
@Configuration
public class OrderRoutes {
    @Bean
    public RouterFunction<ServerResponse> orderRoutes(OrderHandler handler) {
        return RouterFunctions.route()
            .GET("/api/orders/{id}", accept(APPLICATION_JSON), handler::getOne)
            .POST("/api/orders",     accept(APPLICATION_JSON), handler::create)
            .DELETE("/api/orders/{id}",                        handler::delete)
            .build();
    }
}

@Component
public class OrderHandler {
    private final OrderService service;
    public OrderHandler(OrderService service) { this.service = service; }

    public ServerResponse getOne(ServerRequest request) {
        String id = request.pathVariable("id");                 // manual extraction
        return service.find(id)
                .map(dto -> ServerResponse.ok().body(dto))
                .orElseGet(() -> ServerResponse.notFound().build());
    }

    public ServerResponse create(ServerRequest request) throws ServletException, IOException {
        CreateOrderRequest body = request.body(CreateOrderRequest.class);   // manual deserialization
        // ⚠️ and you must call the Validator YOURSELF — no @Valid here
        OrderDto created = service.create(body);
        return ServerResponse.created(URI.create("/api/orders/" + created.id())).body(created);
    }
}
```

#### Why the industry overwhelmingly uses `@RestController`

| # | Reason |
|---|---|
| **1. History and gravity** | Annotated controllers arrived in **Spring 2.5 (2007)**. `RouterFunction` for servlet stacks arrived in **5.2 (2019)**. Twelve years of tutorials, Stack Overflow answers, books, and existing codebases. |
| **2. The whole ecosystem assumes annotations** | **springdoc-openapi** scans `@GetMapping`/`@Operation` to generate Swagger. `@Valid` works automatically. `@ControllerAdvice` catches exceptions globally. `HandlerMethodArgumentResolver` gives you `@PathVariable`, `Authentication`, `Pageable` free. **Functional endpoints get none of this automatically** — you extract, deserialise, and validate by hand. |
| **3. Discoverability** | In an annotated controller, "give me the ID from the path" is `@PathVariable String id`. Functionally, it's `request.pathVariable("id")` returning a `String` you must convert yourself. |
| **4. Tooling** | IDEs have "show all endpoints" views driven by annotations. `GET /actuator/mappings` is richer. Ctrl-clicking a URL in IntelliJ works. |
| **5. ⚠️ You lose the ordering safety** | **`RouterFunction`s compose in order and the FIRST match wins** — exactly like FastAPI/Express. So the safety property from [§W4.13](#w413-routing-does-declaration-order-matter) is gone; `/users/{id}` declared before `/users/me` will shadow it silently. Directly relevant to your ordering question. |
| **6. Team familiarity** | You can hire a hundred Spring developers who know annotations. Far fewer have written WebMVC.fn. |

#### Where functional endpoints genuinely win

- **WebFlux / reactive** — that's their native home and where you'll actually meet them.
- **Kotlin** — the `coRouter { }` DSL is genuinely elegant.
- **GraalVM native images** — no reflection, so faster startup and smaller binaries.
- **Programmatically generated routes** — building routes from config or a database at runtime.
- **Testability** — a handler is a pure `ServerRequest → ServerResponse` function; no `MockMvc` needed.

> **The honest summary:** functional endpoints are a *fine* technology that lost on ecosystem network effects, not on merit. For a REST API in 2026, `@RestController` is the correct default and nobody will question it.

### W4.15 Threading model: thread-per-request, async, WebFlux, virtual threads

| Model | How | Concurrency ceiling | Style |
|---|---|---|---|
| **Classic MVC** (default) | Tomcat worker thread held for the whole request | ≈ `threads.max` (200) | plain blocking code ✅ |
| **Servlet async** | return `Callable<T>` / `DeferredResult<T>` / `CompletableFuture<T>` | high | callback-ish |
| **WebFlux** | `Mono<T>` / `Flux<T>` on Netty event loops | very high, few threads | fully reactive ⚠️ steep |
| **Virtual threads** (Boot 3.2+, Java 21+) | `spring.threads.virtual.enabled=true` | **very high** | **plain blocking code** ✅✅ |

```java
// Servlet async — the Tomcat thread is RELEASED while the future is pending
@GetMapping("/slow")
public CompletableFuture<Report> slow() {
    return CompletableFuture.supplyAsync(this::buildReport, reportExecutor);
}
```

🟨🐍 **Calibrating against your instincts:** Node is **one** thread — blocking it is catastrophic. FastAPI runs `async def` on the event loop and plain `def` in an **anyio threadpool** (default ~40 threads). **Classic Spring MVC is closest to "FastAPI where every endpoint is a plain `def`, but with 200 threads."** Blocking is normal and correct.

**Virtual threads are the direction of travel.** One property gives you event-loop-class scalability while keeping ordinary blocking code, readable stack traces, and working debuggers. For new Boot 3.2+ services on Java 21+, turn it on and skip WebFlux unless you have a specific streaming requirement.

### W4.16 Debugging cheatsheet: where to put a breakpoint

**This table is the practical payoff of this entire section.** When something inexplicable happens, attach a debugger here. *(The Jackson rows are for Boot 2.7/3. On Boot 4 / Framework 7, break in `JacksonJsonHttpMessageConverter` / its parent `AbstractJacksonHttpMessageConverter` instead.)*

| To see… | Breakpoint at |
|---|---|
| Raw HTTP bytes being parsed | `org.apache.coyote.http11.Http11InputBuffer#parseRequestLine` |
| Which filters run, in what order | `org.springframework.web.filter.OncePerRequestFilter#doFilter` |
| Entry into Spring MVC | **`org.springframework.web.servlet.DispatcherServlet#doDispatch`** |
| **Why the wrong endpoint matched** | **`RequestMappingHandlerMapping#lookupHandlerMethod`** |
| All registered routes | `RequestMappingHandlerMapping#getHandlerMethods()` (or `GET /actuator/mappings`) |
| How each argument is resolved | `InvocableHandlerMethod#getMethodArgumentValues` |
| **JSON → object** | **`AbstractJackson2HttpMessageConverter#readInternal`** |
| Validation firing | `MethodValidationAdapter` / `LocalValidatorFactoryBean#validate` |
| **Your method actually invoked** | **`InvocableHandlerMethod#doInvoke`** |
| Which converter was chosen for the response | `AbstractMessageConverterMethodProcessor#writeWithMessageConverters` |
| **Object → JSON** | **`AbstractJackson2HttpMessageConverter#writeInternal`** |
| Exception → status mapping | `ExceptionHandlerExceptionResolver#doResolveHandlerMethodException` |
| Bytes leaving for the socket | `org.apache.coyote.http11.Http11OutputBuffer#commit` |

**Turn on the narration instead of stepping:**
```properties
logging.level.org.springframework.web=TRACE      # the whole dispatch, converter selection
logging.level.org.springframework.web.servlet.mvc.method.annotation=TRACE
spring.mvc.log-request-details=true              # ⚠️ logs params & headers — NEVER in prod
logging.level.org.apache.coyote.http11=DEBUG     # raw HTTP parsing
logging.level.org.springframework.security=DEBUG # the security filter chain
```

### W4.17 A complete, annotated worked example

```java
// ── DTOs ────────────────────────────────────────────────────────────────
public record CreateOrderRequest(
        @NotBlank(message = "customerId is required") String customerId,
        @NotEmpty @Valid List<ItemDto> items) {}          // @Valid cascades into the list

public record ItemDto(@NotBlank String sku, @Min(1) @Max(999) int qty) {}

public record OrderDto(String id, String customerId, BigDecimal total, Instant createdAt) {}

// ── Controller ──────────────────────────────────────────────────────────
@RestController                                   // = @Controller + @ResponseBody
@RequestMapping("/api/v1/orders")                 // base path for the whole class
@RequiredArgsConstructor                          // Lombok → constructor injection
@Slf4j
public class OrderController {

    private final OrderService service;           // final → injected once at startup

    @GetMapping("/{id}")                          // GET /api/v1/orders/abc-123
    public OrderDto getOne(@PathVariable String id) {
        return service.find(id)
                      .orElseThrow(() -> new OrderNotFoundException(id));   // → 404 via @ExceptionHandler
    }

    @GetMapping                                   // GET /api/v1/orders?status=NEW&page=0&size=20
    public Page<OrderDto> list(
            @RequestParam(required = false) OrderStatus status,   // String → enum, automatic
            @PageableDefault(size = 20) Pageable pageable) {      // Spring Data resolver
        return service.search(status, pageable);
    }

    @PostMapping(consumes = APPLICATION_JSON_VALUE,   // 415 if Content-Type is wrong
                 produces = APPLICATION_JSON_VALUE)   // 406 if Accept is incompatible
    @ResponseStatus(HttpStatus.CREATED)               // 201 on success
    public OrderDto create(@Valid @RequestBody CreateOrderRequest req,   // deserialise + validate
                           @RequestHeader(value = "X-Idempotency-Key", required = false) String key) {
        log.info("creating order for customer {}", req.customerId());
        return service.create(req, key);
    }

    @DeleteMapping("/{id}")
    @ResponseStatus(HttpStatus.NO_CONTENT)        // 204, empty body
    public void delete(@PathVariable String id) {
        service.delete(id);
    }

    // ── Local exception handling (the global version: @RestControllerAdvice, chapter W8) ──
    @ExceptionHandler(OrderNotFoundException.class)
    @ResponseStatus(HttpStatus.NOT_FOUND)
    public ProblemDetail notFound(OrderNotFoundException e) {
        ProblemDetail pd = ProblemDetail.forStatusAndDetail(HttpStatus.NOT_FOUND, e.getMessage());
        pd.setTitle("Order not found");
        pd.setProperty("orderId", e.orderId());
        return pd;
    }
}
```

**Trace `POST /api/v1/orders` through the machine:**

| Stage | What happens | Class |
|---|---|---|
| 1 | TCP bytes arrive on :8080 | `NioEndpoint$Acceptor` |
| 2 | Socket readable → worker `http-nio-8080-exec-7` picks it up | `NioEndpoint$Poller` |
| 3 | Parse request line + headers; body left unread | `Http11InputBuffer` |
| 4 | Wrap as `HttpServletRequest` | `RequestFacade` |
| 5 | Filter chain: encoding → metrics → security → request context | `FilterChainProxy` |
| 6 | `doDispatch()` entered | `DispatcherServlet` |
| 7 | `POST` + `/api/v1/orders` + `consumes=json` → `OrderController#create` | `RequestMappingHandlerMapping` |
| 8 | Resolve `req` → `@RequestBody`; `key` → `@RequestHeader` | `InvocableHandlerMethod` |
| 9 | **Stream socket bytes → `CreateOrderRequest`** (no String!) | `MappingJackson2HttpMessageConverter` → `ObjectMapper.readValue` (Boot 4: `JacksonJsonHttpMessageConverter` → `JsonMapper`) |
| 10 | `@Valid` → `@NotBlank`, `@NotEmpty`, cascade into `ItemDto` | `LocalValidatorFactoryBean` |
| 11 | `method.invoke(orderController, [req, key])` | `InvocableHandlerMethod#doInvoke` |
| 12 | Your code → `OrderService` → `OrderRepository` → JDBC → DB | your beans |
| 13 | `OrderDto` returned; `@ResponseStatus(CREATED)` → 201 | `RequestResponseBodyMethodProcessor` |
| 14 | `Accept: application/json` matched against converters | `ContentNegotiationManager` |
| 15 | **`OrderDto` → UTF-8 JSON bytes** straight to the output stream | `ObjectMapper.writeValue` |
| 16 | Status line + headers + body written; `Content-Length` set (or chunked if > 8 KB buffer) | `Http11OutputBuffer` |
| 17 | Bytes on the socket; connection kept alive | `NioChannel#write` |
| 18 | Worker thread returns to the pool | `NioEndpoint` |

**If validation had failed at step 10:** `MethodArgumentNotValidException` → caught in `doDispatch` → `ExceptionHandlerExceptionResolver` looks for a matching `@ExceptionHandler` → falls through to `DefaultHandlerExceptionResolver` → **400**. Steps 11–12 never run. *(Boot's default `/error` JSON omits the field errors unless `server.error.include-binding-errors` is set. A `@RestControllerAdvice` gives you a proper field-error body: [§W8.8](#w88-global-exception-handling-with-problemdetail-).)*

---


## W5. Filters vs HandlerInterceptors

> **Your questions, merged:** *"difference between filterchain and interceptor in spring boot"* · *"so interceptor is also applicable for all application endpoints except the others like static endpoints (i.e. all endpoints which we write for normal db interaction will be interacting with the interceptor)?"* · *"so when to make changes in interceptor and when in filter chain (i.e. when to create a new filter in the filterchain and when to create a new interceptor [client interceptor and server interceptor])?"* · *"why not postHandle here and why afterCompletion?"* · *"CORS handling done in Filter chain or inside the handlerInterceptor? what's the role of both in spring (filter chain and handlerInterceptor)?"*

[§W4.6](#w46-the-filter-chain) showed *where* the filter chain sits in the request journey. This chapter is the full comparison: what each layer can see, when each runs, and which one to pick.

### W5.1 The two layers in one picture

A **`Filter`** belongs to the **Servlet API** (`jakarta.servlet.Filter`; `javax.servlet.Filter` on Boot 2.7). It wraps the `DispatcherServlet` from the outside.
A **`HandlerInterceptor`** belongs to **Spring MVC** (`org.springframework.web.servlet.HandlerInterceptor`). It runs *inside* the `DispatcherServlet`, after the `HandlerMapping` has decided which handler will serve the request.

```
            Tomcat
              │
   ┌──────────▼───────────────────────────────────────────────┐
   │ FILTER CHAIN  (Servlet API — sees EVERY request)         │
   │   CharacterEncodingFilter → … → Spring Security          │
   │   → your OncePerRequestFilter …                          │
   │   ┌──────────────────────────────────────────────────┐   │
   │   │ DispatcherServlet                                │   │
   │   │   HandlerMapping → HandlerExecutionChain         │   │
   │   │   ┌───────────────────────────────────────────┐  │   │
   │   │   │ INTERCEPTORS (Spring MVC — only requests  │  │   │
   │   │   │ that matched a handler)                   │  │   │
   │   │   │   preHandle → handler → postHandle        │  │   │
   │   │   │   → (view) → afterCompletion              │  │   │
   │   │   └───────────────────────────────────────────┘  │   │
   │   └──────────────────────────────────────────────────┘   │
   └──────────────────────────────────────────────────────────┘
```

| | **`Filter`** | **`HandlerInterceptor`** |
|---|---|---|
| API | Servlet spec (`jakarta.servlet`) | Spring MVC |
| Runs | **before and after** the `DispatcherServlet` | inside it, around the **handler** |
| Sees | every request, including ones Spring MVC would 404 and error dispatches | only requests for which a `HandlerMapping` found a handler. That includes static files Spring MVC serves; see [§W5.3](#w53-does-an-interceptor-run-for-every-endpoint) |
| Knows the target handler | ❌ | ✅ the `handler` argument, usually a `HandlerMethod` you can read annotations from |
| Can replace request/response objects | ✅ wrap them (`ContentCachingRequestWrapper`, …) | ❌ can't replace them, but can set headers/status in `preHandle` |
| Hooks | `doFilter(req, res, chain)`: code before **and** after `chain.doFilter()` | `preHandle` / `postHandle` / `afterCompletion` |
| Short-circuit | don't call `chain.doFilter()` | return `false` from `preHandle` |
| Exceptions handled by `@ControllerAdvice` | ❌ thrown outside the `DispatcherServlet` → container error page / Boot's `/error` | ✅ processed by the `HandlerExceptionResolver`s, so `@ExceptionHandler` works |
| Registration in Boot | any `Filter` **bean** (e.g. a `@Component`) is auto-registered for `/*`; use `FilterRegistrationBean` for URL patterns/order | must be added in `WebMvcConfigurer.addInterceptors(...)`. Being a `@Component` alone does nothing |
| Spring beans injectable | ✅ in Boot (a filter bean is a normal bean) | ✅ |

**Correction to the source answer:** *"a filter cannot easily inject Spring beans"* is only true for a filter that the **servlet container** instantiates (declared in `web.xml` or with `@WebFilter`). In Spring Boot a filter is normally a Spring bean. Boot docs: *"Any `Servlet`, `Filter`, or servlet `*Listener` instance that is a Spring bean is registered with the embedded container."* So constructor injection works like anywhere else. The split between container and Spring context matters for **Spring Security**, which is why it uses `DelegatingFilterProxy` ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)).

🐍🟨 Both FastAPI and Express collapse these two layers into one: ASGI middleware / `app.use()` is the filter. Their closest thing to an interceptor is a **FastAPI dependency on a router** (`APIRouter(dependencies=[Depends(...)])`) or **Express route-level middleware** (`router.get('/x', auth, handler)`), i.e. code that runs only once the route is known.

### W5.2 The exact order of events

This is the timeline from the source answer, corrected at two points (steps 6 and 8):

```
 1. Client sends the HTTP request
 2. Filter chain: each filter's code BEFORE chain.doFilter()
 3. DispatcherServlet.doDispatch()
 4.    HandlerMapping → HandlerExecutionChain (handler + matching interceptors)
 5.    interceptor.preHandle()  — in registration order; false ⇒ stop here
 6.    HandlerAdapter invokes your controller method
         └─ for @ResponseBody / ResponseEntity: the return value is serialised
            to JSON and the response is WRITTEN AND COMMITTED right here
 7.    interceptor.postHandle() — reverse order; SKIPPED if step 6 threw
 8.    View rendering (only for @Controller + view name, e.g. Thymeleaf)
 9.    interceptor.afterCompletion() — reverse order; runs on success AND on
       exception, but only for interceptors whose preHandle returned true
10. Filter chain: each filter's code AFTER chain.doFilter() (unwinding)
11. Tomcat flushes the remaining bytes to the client
```

Verified against the Spring Framework reference: *"For `@ResponseBody` and `ResponseEntity` controller methods, the response is written and committed within the `HandlerAdapter`, before `postHandle` is called. That means it is too late to change the response, such as to add an extra header."* The docs suggest `ResponseBodyAdvice` instead ([§W8.3](#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling)).

Two more facts from `HandlerExecutionChain`'s source that are easy to get wrong:
- If interceptor #3's `preHandle` returns `false`, Spring immediately calls `afterCompletion` on interceptors #1 and #2, whose `preHandle` already returned `true`, so they can clean up. #3's own `afterCompletion` is **not** called.
- `postHandle` and `afterCompletion` run in **reverse** registration order. It's the same onion as Express middleware unwinding.

### W5.3 Does an interceptor run for every endpoint?

> **Your question:** *"so interceptor is also applicable for all application endpoints except the others like static endpoints?"*

**Yes for every controller endpoint you write**, provided the interceptor's path patterns match.

📌 **Correction:** the "except static endpoints" part is wrong (the source answer said the same). Interceptors also run for static files served by Spring MVC.

Static files in Boot are served by Spring MVC's own `ResourceHttpRequestHandler`, found through a `SimpleUrlHandlerMapping`. In the Framework source, `WebMvcConfigurationSupport` passes the interceptors you register to **every** handler mapping it creates, including the resource-handler mapping (`mapping.setInterceptors(getInterceptors(...))` in `initHandlerMapping`). So a `/**` interceptor **also runs for `/css/app.css`**. That has been true in 5.3 (Boot 2.7) and is still true in 7.x.

What an interceptor genuinely never sees:
- requests that **no** handler mapping matched (they become a 404 before any interceptor runs);
- anything a **filter** rejected or answered earlier (e.g. Spring Security returning 401).

**Scoping is your job**: use path patterns, and exclude static paths explicitly if you don't want them.
```java
@Configuration
public class WebConfig implements WebMvcConfigurer {           // ⚠️ no @EnableWebMvc in Boot

    private final AuditInterceptor auditInterceptor;            // constructor injection is fine
    public WebConfig(AuditInterceptor auditInterceptor) { this.auditInterceptor = auditInterceptor; }

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(auditInterceptor)
                .addPathPatterns("/api/**")                     // only API endpoints
                .excludePathPatterns("/api/auth/**",            // not login/register
                                     "/css/**", "/js/**", "/error");
        // .order(1) — lower runs earlier; default is registration order
    }
}
```

⚠️ The Spring docs add a warning worth taking seriously: *"Interceptors are not ideally suited as a security layer due to the potential for a mismatch with annotated controller path matching. Generally, we recommend using Spring Security, or alternatively a similar approach integrated with the Servlet filter chain."* Use interceptors for metrics, auditing and context, not as your only authentication gate.

### W5.4 Filter, server interceptor or client interceptor? The decision guide

> **Your question:** *"so when to make changes in interceptor and when in filter chain (i.e. when to create new filter in filterchain and when to create new interceptor [client interceptor and server interceptor])?"*

The deciding question: **who owns the request at that moment, and what do you need to know?**

**Write a `Filter` when** the concern is about raw HTTP and must happen for everything, before Spring MVC:
- reject early: IP block-lists, rate limits, request-size limits;
- change the raw streams: wrap the request to read the body twice (`ContentCachingRequestWrapper`), force character encoding;
- set universal response headers (security headers, correlation ID), or MDC/tracing context for the whole request, including errors;
- authentication: Spring Security *is* a filter chain ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)).

**Write a `HandlerInterceptor` (server side) when** you need to know which controller method is about to run:
- read a custom annotation on the target method (`((HandlerMethod) handler).getMethodAnnotation(Audited.class)`);
- per-handler metrics or audit logs tagged with the controller/method name;
- add common attributes to the `ModelAndView` for server-rendered pages (`postHandle`);
- you want exceptions to flow into your `@ControllerAdvice`.

**Write a client interceptor when** you are changing **outgoing** calls your service makes to other services. It is a different direction entirely:

```
INBOUND  (server side)
[External client] ─► [Filter chain] ─► [HandlerInterceptor] ─► [Your @RestController]
                                                                      │
                                                                      │ your code calls another service
OUTBOUND (client side)                                                ▼
[Other service]  ◄── network ◄── [Client interceptor] ◄── [RestClient / RestTemplate / gRPC stub]
```

| Client | Interceptor type |
|---|---|
| `RestTemplate`, `RestClient` | `ClientHttpRequestInterceptor` |
| `WebClient` | `ExchangeFilterFunction` |
| gRPC stub | `io.grpc.ClientInterceptor` ([§P1](06-spring-production.md#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21)) |

Typical client-interceptor jobs: add an OAuth token or `X-API-Key` to every outgoing call, propagate a correlation ID, log outbound URIs and latency, and refresh the token then retry once on a 401.
```java
public class ApiKeyInterceptor implements ClientHttpRequestInterceptor {
    @Override
    public ClientHttpResponse intercept(HttpRequest req, byte[] body,
                                        ClientHttpRequestExecution execution) throws IOException {
        req.getHeaders().add("X-API-Key", "…");          // outgoing header
        return execution.execute(req, body);              // like chain.doFilter()
    }
}
RestClient client = RestClient.builder().requestInterceptor(new ApiKeyInterceptor()).build();
```
(The word "interceptor" means a different thing in gRPC, where both `ServerInterceptor` and `ClientInterceptor` exist. A gRPC gateway typically uses both. See [§P1](06-spring-production.md#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21).)

**The selection matrix (corrected):**

| Objective | Put it in |
|---|---|
| Block malicious traffic, rate-limit | **Filter** |
| CORS | **Spring Security's `.cors()`** if you use Security, otherwise MVC config or a `CorsFilter` ([§W9](#w9-cors-crossorigin-corsfilter-and-spring-security)) |
| Parse/verify a JWT | **Filter**, inside the Spring Security chain ([§S3](05-spring-security.md#s3-stateless-authentication-jwt-and-refresh-tokens)) |
| Read a custom annotation on the controller method | **HandlerInterceptor** (or AOP, [§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-)) |
| Time a controller endpoint | **HandlerInterceptor** (`preHandle` + `afterCompletion`), or just Actuator/Micrometer, which already does it ([§P5](06-spring-production.md#p5-production-grade-concerns-)) |
| Time the *whole* request including filters | **Filter** |
| Add a tracking header to downstream calls | **Client interceptor** |
| Modify a JSON response body/headers after the controller | **`ResponseBodyAdvice`**, not `postHandle` |

### W5.5 `postHandle` vs `afterCompletion`, and the timing example

> **Your question:** *"why not postHandle here and why afterCompletion?"*

The conclusion is right (use `afterCompletion` to stop the timer), but **one of the two reasons in the source answer was wrong**.

| Claim in the source answer | Reality |
|---|---|
| "`postHandle` fires before Spring serialises the data to JSON, so it misses serialisation time" | ❌ **Wrong.** For `@ResponseBody`/`ResponseEntity` the JSON was already written and committed inside the `HandlerAdapter`, **before** `postHandle` ([§W5.2](#w52-the-exact-order-of-events)). For a REST API, `postHandle` and `afterCompletion` see almost the same elapsed time. The extra window only exists for **view rendering** (Thymeleaf), which happens between them. |
| "`postHandle` is skipped if an exception occurs" | ✅ **Right, and this is the real reason.** A timer stopped in `postHandle` would never record failed requests. |
| "`afterCompletion` is guaranteed to run" | ⚠️ **Almost.** It runs on success and on exception, but only if *this* interceptor's `preHandle` returned `true`. |

So the real rule: **`afterCompletion` is the `finally` block of an interceptor.** Use it for timers, clearing `ThreadLocal`/MDC, and releasing resources. Use `postHandle` only to touch the `ModelAndView` of a view-rendering controller.

```java
@Component
public class ExecutionTimeInterceptor implements HandlerInterceptor {
    private static final String START = ExecutionTimeInterceptor.class.getName() + ".start";
    private static final Logger log = LoggerFactory.getLogger(ExecutionTimeInterceptor.class);

    @Override
    public boolean preHandle(HttpServletRequest req, HttpServletResponse res, Object handler) {
        req.setAttribute(START, System.nanoTime());   // ✅ per-request storage, not a field
        return true;
    }

    @Override
    public void afterCompletion(HttpServletRequest req, HttpServletResponse res,
                                Object handler, Exception ex) {
        Object start = req.getAttribute(START);
        if (start == null) return;                     // defensive: preHandle didn't run
        long ms = (System.nanoTime() - (Long) start) / 1_000_000;
        log.info("{} {} -> {} in {} ms{}", req.getMethod(), req.getRequestURI(),
                 res.getStatus(), ms, ex != null ? " (exception: " + ex + ")" : "");
    }
}
```
Notes on this example:
- ✅ **Why a request attribute and not a field:** the interceptor is a singleton shared by all request threads ([§W1.5](#w15-one-servlet-many-threads--the-concurrency-model-q44)). A field would be overwritten by concurrent requests. The request object is private to this request.
- `System.nanoTime()` measures elapsed time. `currentTimeMillis()` is wall-clock time and can jump when NTP adjusts the clock.
- ⚠️ `ex` is often `null` even when the client got a 500. If an `@ExceptionHandler` already turned the exception into a response, the `DispatcherServlet` treats the exception as handled. Log `res.getStatus()` instead of relying on `ex`.
- In production you rarely need this: Boot's Actuator already records `http.server.requests` timers per endpoint ([§P5](06-spring-production.md#p5-production-grade-concerns-)).

The same `preHandle` → `afterCompletion` pairing is how you safely set and clear a `ThreadLocal` such as a tenant ID ([§J6](01-java.md#j6-concurrency-and-multithreading-q2q9)). A filter with `try { chain.doFilter } finally { clear }` is even safer, because it also covers requests that never reach a handler.

### W5.6 So where does CORS run: filter or interceptor?

> **Your question:** *"CORS handling done in Filter chain or inside the handleInterceptor?"*

**Either, depending on how you configure it.** The source answers contradicted each other on this, and both "only the filter" and "only the interceptor" are wrong:

| You configure CORS with… | It runs in… |
|---|---|
| `@CrossOrigin`, or `WebMvcConfigurer.addCorsMappings()` | **Spring MVC**, inside the `DispatcherServlet`. The `HandlerMapping` adds an internal `CorsInterceptor` (or answers the preflight itself) |
| a `CorsFilter` bean | the **filter chain** |
| Spring Security `.cors(...)` | Security's `CorsFilter`, early in the **security filter chain** |

If Spring Security is present, CORS must be handled **before** security, i.e. in a filter. Full mechanics in [§W9](#w9-cors-crossorigin-corsfilter-and-spring-security).

### W5.7 GZIP compression: per endpoint or global, and where?

> **Your question:** *"gzip is added per endpoint or for all endpoint in a system (asking in generic way like python+fastapi, spring boot) where should it be placed?"*

**Globally, never per endpoint**, and ideally at the outermost layer.

| Tier | Where | Why |
|---|---|---|
| 🥇 Infrastructure | reverse proxy / load balancer / CDN (Nginx, Envoy, CloudFront, Cloudflare) | compression costs CPU; do it once, at the edge, for every service behind it |
| 🥈 Application server | the embedded web server, switched on by configuration | fine when nothing in front compresses |

Both tiers compress conditionally, never blindly:
- **by content type**: text formats (JSON, HTML, CSS, JS) shrink a lot, while JPEG/PNG/video are already compressed and only waste CPU;
- **by size**: tiny bodies like `{"status":"ok"}` can get *bigger* after adding the gzip header.

**Spring Boot** (verified, Boot reference "Enable HTTP Response Compression"):
```properties
server.compression.enabled=true
server.compression.min-response-size=2048          # default 2048 bytes (2 KB)
server.compression.mime-types=application/json,text/html   # REPLACES the default list
# server.compression.additional-mime-types=...     # ADDS to the default list (newer Boot)
```
- Default mime types: `text/html, text/xml, text/plain, text/css, text/javascript, application/javascript, application/json, application/xml`.
- Supported servers: Tomcat, Jetty, Reactor Netty.
- **Note:** this is **not** a servlet filter. Boot hands the settings to the embedded server's connector (Tomcat's own compression support), so it runs inside Tomcat's HTTP processing, below the filter chain.

**FastAPI** uses ASGI middleware, which is FastAPI's equivalent of a filter:
```python
from fastapi.middleware.gzip import GZipMiddleware
app.add_middleware(GZipMiddleware, minimum_size=500)   # bytes; 500 is the default
```
🟨 **Express:** `app.use(compression())` from the `compression` package.

⚠️ Don't enable it in two places (e.g. Nginx *and* Tomcat) without checking: it wastes CPU, and you can get confusing `Content-Encoding` behaviour. Also, never compress responses that mix secrets with attacker-controlled input over TLS (the BREACH attack class).

## W6. Reading input and data binding [Q55, Q56]

### W6.1 `@RequestParam` vs `request.getParameter()` [Q55]

> **Your question:** *"i know two methods a) `request.getParameter` and b) using `@RequestParam`… is this only for reading form data or body or queryparam or pathparam or something else (or it depends on the type of the request method i.e if request method is get it will read from the query param or if the request method is post then it will read from request body)?"*

**Your hypothesis — "it depends on the HTTP method" — is not quite right.** It depends on **`Content-Type`**, not on the verb.

Both `HttpServletRequest.getParameter(String)` and `@RequestParam` read from exactly **two** places, and the Servlet specification defines them:

1. **Query string** in the URL — `/api/search?name=Alex&page=2` — for **any** HTTP method, including POST.
2. **Form data in the body** — but *only* when `Content-Type` is `application/x-www-form-urlencoded` or `multipart/form-data`.

```
GET /api/search?name=Alex          →  @RequestParam String name  ✅  (query string)
POST /api/search?name=Alex         →  @RequestParam String name  ✅  (still the query string!)
POST  Content-Type: x-www-form-urlencoded
      body: name=Alex              →  @RequestParam String name  ✅  (form body)
POST  Content-Type: application/json
      body: {"name":"Alex"}        →  @RequestParam String name  ❌  400
```

**Can they read a JSON body?** **No.** A JSON body is opaque to the servlet container — it never parses it. `@RequestParam(required = true)` on a JSON request throws **`MissingServletRequestParameterException`** → 400. To read JSON you must use **`@RequestBody`**, which triggers Jackson ([§W4.8](#w48-json-to-java-object-where-jsonparse-really-lives)).

**Can they read path variables?** **No.** `/users/{id}` → `/users/5` needs **`@PathVariable`**. The `5` is part of the URL *path*, not the query string.

⚠️ **One Spring-specific extension to the servlet rule.** The Servlet spec only requires the container to parse a form body for **POST**. Spring Boot registers `OrderedFormContentFilter`, which also parses `x-www-form-urlencoded` bodies for **PUT, PATCH and DELETE** — so `@RequestParam` works there too in a Boot app, where it would not in a bare servlet. ([§W4.6](#w46-the-filter-chain))

#### Can you drop `HttpServletRequest` entirely?

> **Your question:** *"in this way we don't have to pass ServletRequest as the parameter and we can safely only use the @RequestParam as the function parameter of the api controller?"*

**Yes — and you should.** Taking the raw `HttpServletRequest` is a pre-Spring-2.5 habit. It gives you untyped `String`s, manual null handling, no defaults, no validation, and it makes the method almost impossible to unit-test without a mock servlet request.

```java
// ❌ Archaic: boilerplate, untyped, hard to test
@GetMapping("/greet")
public String greetOld(HttpServletRequest request) {
    String name = request.getParameter("name");
    return "Hello " + (name != null ? name : "Guest");
}

// ✅ Modern: type-safe, declarative, trivially unit-testable
@GetMapping("/greet")
public String greetModern(@RequestParam(defaultValue = "Guest") String name) {
    return "Hello " + name;
}
```

The modern version is also **self-documenting**: springdoc reads it and produces the OpenAPI parameter entry for free ([§W12](#w12-api-documentation-openapi-and-swagger-q32-q33)). The `HttpServletRequest` version produces nothing.

**The few legitimate reasons to still inject `HttpServletRequest`:** reading the raw client IP behind a proxy, `request.getRequestURI()` for audit logging, iterating headers you don't know in advance, or accessing the raw `InputStream`. Even then, prefer `@RequestHeader`, `Principal`, `Locale`, `HttpMethod`, or `UriComponentsBuilder.fromCurrentRequest()` where they fit.

🐍🟨 **Your equivalents:**

| | Spring | FastAPI | Express |
|---|---|---|---|
| Query param | `@RequestParam String q` | `def f(q: str)` | `req.query.q` |
| Path param | `@PathVariable Long id` | `def f(id: int)` (from `/{id}`) | `req.params.id` |
| JSON body | `@RequestBody Dto dto` | `def f(dto: Model)` | `req.body` (with `express.json()`) |
| Form field | `@RequestParam String name` | `name: str = Form(...)` | `req.body` (with `express.urlencoded()`) |
| Header | `@RequestHeader("X-Id") String id` | `x_id: str = Header(...)` | `req.get('X-Id')` |
| Cookie | `@CookieValue("sid") String sid` | `sid: str = Cookie(...)` | `req.cookies.sid` |
| Raw request | `HttpServletRequest request` | `request: Request` | `req` |

💡 Note how **FastAPI infers the source from the type**, while **Spring makes you name it with an annotation**. Spring's way is more verbose but unambiguous — you never have to remember FastAPI's precedence rules for where a bare `str` parameter comes from.

### W6.2 The complete "where does this value come from" table [Q55]

| Annotation | Reads from | `required` default | Missing → |
|---|---|---|---|
| `@RequestParam` | query string **or** form body | `true` | 400 `MissingServletRequestParameterException` |
| `@PathVariable` | URI template segment | `true` | 500 (the mapping shouldn't have matched) |
| `@RequestBody` | request body via `HttpMessageConverter` | `true` | 400 `HttpMessageNotReadableException` |
| `@RequestHeader` | a request header | `true` | 400 `MissingRequestHeaderException` |
| `@CookieValue` | a cookie | `true` | 400 `MissingRequestCookieException` |
| `@RequestPart` | one named part of a `multipart/form-data` body (converted by a message converter — so a JSON part works) | `true` | 400 `MissingServletRequestPartException` |
| `@ModelAttribute` | query string + form body, bound onto an object | n/a | silently leaves fields null |
| `@MatrixVariable` | `;k=v` segments in the path | `true` | 400 |
| *(no annotation, simple type)* | treated as `@RequestParam` | — | — |
| *(no annotation, complex type)* | treated as `@ModelAttribute` | — | — |

⚠️ **That last pair is a real trap.** An un-annotated `String`/`int`/`Long`/enum parameter is implicitly `@RequestParam`; an un-annotated POJO is implicitly `@ModelAttribute`. So this compiles and runs but silently reads nothing from a JSON body:

```java
@PostMapping("/users")
public User create(User user) { ... }        // ❌ @ModelAttribute — JSON body IGNORED, all fields null
@PostMapping("/users")
public User create(@RequestBody User user) { ... }   // ✅
```

**Making a parameter optional — three ways:**
```java
@RequestParam(required = false) String q                 // null when absent
@RequestParam(defaultValue = "10") int size              // implies required=false
@RequestParam Optional<String> q                         // Optional.empty() when absent
```
⚠️ Never use a primitive with `required = false` — `int` can't be null, so an absent parameter throws. Use `Integer`, `Optional<Integer>`, or a `defaultValue`.

**Multi-valued and structured parameters:**
```java
@RequestParam List<String> tags        // ?tags=a&tags=b   OR   ?tags=a,b
@RequestParam String[] tags            // same
@RequestParam Map<String,String> all   // every query parameter, unbound
@RequestParam MultiValueMap<String,String> all   // preserves repeated keys
@RequestParam MultipartFile avatar     // a file upload part
@RequestParam List<MultipartFile> files
```

### W6.3 Several path variables, and does parameter order matter?

> **Your question:** *"how to take multiple path variables? does the order of parameters in the method have to match the order in the URL?"* e.g. `@GetMapping("/users/{userId}/orders/{orderId}") public OrderDto get(@PathVariable Long orderId, @PathVariable Long userId)`

**Binding is by name, never by position.** That signature is correct even though the parameters are in the opposite order to the URL: `{userId}` binds to the parameter named `userId`, and `{orderId}` to `orderId`.

```java
@GetMapping("/users/{userId}/orders/{orderId}")
public OrderDto get(@PathVariable Long orderId,                 // ✅ any order
                    @PathVariable("userId") Long ownerId) {     // ✅ explicit name when it differs
    return service.find(ownerId, orderId);
}

@GetMapping("/users/{userId}/orders/{orderId}")
public OrderDto get(@PathVariable Map<String, String> vars) { … }   // all of them, as Strings
```
- Leaving out the name (`@PathVariable Long orderId`) relies on the **parameter name being present in the `.class` file**, which requires compiling with **`-parameters`**. Boot's Maven and Gradle plugins set it. ⚠️ **Framework 6.1 removed the fallback** that read names from debug info (`LocalVariableTableParameterNameDiscoverer`; Framework 6.1 release notes). So a project built without Boot's plugin (some Bazel setups!) fails at runtime with *"Name for argument of type … not specified, and parameter name information not available via reflection"*. Fix: add `-parameters` to javac, or always write the name explicitly. Kotlin: `-java-parameters`.
- The same rule applies to `@RequestParam`, `@RequestHeader` and `@CookieValue`.
- Types are converted per variable (`Long`, `UUID`, enums; [§W6.7](#w67--type-conversion-how-25-becomes-25)). A non-numeric `orderId` → `MethodArgumentTypeMismatchException` → **400**.
- Regex constraints: `{orderId:\\d+}` makes the mapping not match non-digits (→ 404, or another mapping).

🐍 FastAPI also binds by name: `def get(order_id: int, user_id: int)` for `/users/{user_id}/orders/{order_id}`. 🟨 Express: `req.params.userId`.

### W6.4 Data binding for HTML forms [Q55]

> **Your question:** *"explain how several data binding works in spring boot for several type of html tags like checkbox, form, radio, drop-down list, input text etc?"*

When an HTML `<form>` is submitted, Spring uses **`WebDataBinder`** to match each HTML control's **`name` attribute** to a property of a target Java object — historically called a **Command Object** or **Form Backing Bean** — declared with **`@ModelAttribute`**.

```
<input name="username" value="alex">          HTTP body: username=alex&age=30&hobbies=code&hobbies=chess
          │
          ▼
   WebDataBinder
          │  for each request parameter:
          │    1. find the matching property on the target  (username → setUsername)
          │    2. CONVERT the String to the property's type (via ConversionService / PropertyEditor)
          │    3. set it
          │  record any failure as a FieldError in the BindingResult
          ▼
   UserForm { username="alex", age=30, hobbies=["code","chess"] }
```

| HTML control | Binds to | Notes |
|---|---|---|
| `<input type="text" name="username">` | `String username` | via `setUsername(String)` |
| `<input type="number" name="age">` | `int` / `Integer age` | ⚠️ non-numeric text → `typeMismatch` error, **not** an exception |
| `<input type="checkbox" name="hobbies" value="code">` ×N (same name) | `List<String>` / `String[] hobbies` | repeated names collapse into a collection |
| `<input type="checkbox" name="active">` (single) | `boolean active` | ⚠️ see the unchecked-box trap below |
| `<input type="radio" name="gender">` | `String` or an **enum** `Gender` | only the selected one is submitted |
| `<select name="country">` | `String country` | the chosen `<option>`'s `value` |
| `<select name="roles" multiple>` | `List<String>` / `Set<Role>` | |
| `<input type="date" name="dob">` | `LocalDate dob` | needs `@DateTimeFormat(iso = DATE)` or a `Converter` |
| `<input type="file" name="avatar">` | `MultipartFile avatar` | form must be `enctype="multipart/form-data"` |
| `<input name="address.city">` | `form.getAddress().setCity(...)` | **nested paths** work with dots |
| `<input name="items[0].sku">` | `form.getItems().get(0).setSku(...)` | **indexed paths** work with brackets |

#### [+] The unchecked-checkbox trap — the #1 form-binding bug

**An unchecked HTML checkbox submits nothing at all.** So if `active` was `true` and the user unchecks it, the browser sends no `active` parameter, the binder has nothing to set, and the field **stays `true`**. The user's change is silently lost.

Spring solves this with a **field marker**: `WebDataBinder.DEFAULT_FIELD_MARKER_PREFIX = "_"`. You submit a hidden field named `_active` alongside the checkbox. The binder reasons: *"`_active` is present, so the checkbox was on the form; `active` is absent, so it was unchecked → reset it to the empty value (`false`)."*

```html
<!-- Raw HTML: you must add the hidden marker yourself -->
<input type="checkbox" name="active" value="true" />
<input type="hidden"   name="_active" />

<!-- Thymeleaf th:field: the hidden marker is generated FOR you -->
<input type="checkbox" th:field="*{active}" />
```

There is a sibling prefix `!` (`DEFAULT_FIELD_DEFAULT_PREFIX`): a parameter `!active=true` supplies the value to use when `active` is absent. Rarely needed, but it explains the odd-looking `_` and `!` parameters you'll see in legacy Spring form posts.

💡 **This whole class of bug does not exist in a JSON API** — JSON has an explicit `false`. It's purely an HTML-forms problem.

### W6.5 `Model`, `ModelMap`, `ModelAndView` — and the Express equivalent [Q55]

> **Your question:** *"what is `Model` from `org.springframework.ui.Model`? is this used to share information between spring application and web pages or it has some other usecases? was any similar thing exist in express to share information between the express app and the ejs or any view template engine?"*

**Your understanding is exactly right.** `org.springframework.ui.Model` is a **typed map** that carries data from the controller to the view template. Nothing more.

```java
@GetMapping("/profile")
public String profile(Model model) {                 // Spring injects it
    model.addAttribute("user", userService.current());   // key → value
    model.addAttribute("orders", orderService.recent());
    return "profile";                                 // → templates/profile.html
}
```
```html
<h1 th:text="${user.name}">…</h1>
<li th:each="o : ${orders}" th:text="${o.id}">…</li>
```

| Type | What it is |
|---|---|
| `Model` | the interface — `addAttribute(k, v)`, `addAllAttributes(map)`, `containsAttribute(k)` |
| `ModelMap` | an implementation that is also a `LinkedHashMap<String,Object>` |
| `ModelAndView` | model **+** view name in a single returned object — the older style |
| `@ModelAttribute` **on a method** | runs before **every** handler in the controller and adds its return value to the model — good for dropdown options, the logged-in user, etc. |
| `RedirectAttributes` | survives a redirect; `addFlashAttribute` stores once in the session and auto-removes after the next request |

```java
@ModelAttribute("countries")            // runs before every handler in this controller
public List<String> countries() { return List.of("IN", "US", "DE"); }
```

🟨 **The Express equivalent is exact.** `res.render(view, locals)` — the second argument *is* the Model:
```javascript
res.render('profile', { user: currentUser, orders: recentOrders });   // ← the Model
app.locals.appName = 'MyApp';   // ← application-wide, like @ModelAttribute on @ControllerAdvice
res.locals.user = req.user;     // ← per-request, like @ModelAttribute on a method
```
🐍 In **Flask** it's `render_template('profile.html', user=..., orders=...)`; in **Django** it's the `context` dict; in **FastAPI + Jinja2** it's `templates.TemplateResponse("profile.html", {"request": request, "user": user})`.

⚠️ **`Model` is irrelevant in a `@RestController`.** There is no view. Anything you add to the model is simply ignored. If you inject `Model` into a REST handler, that's a sign the method was copy-pasted from an MVC tutorial.

### W6.6 `@RequestMapping` vs the shortcut annotations [Q55]

> **Your question:** *"`@RequestMapping` can handle all type of http request method [get, post, put, delete, patch, option, head] then why do we use this because in real world we don't want a single controller to handle all kind of work? [so we should use `@RequestMapping(path="/user", method=RequestMethod.GET)` or short form is `@GetMapping`]"*

**Your conclusion is correct, and it is exactly what the industry does.**

The history: before **Spring 4.3 (2016)**, `@RequestMapping` was the *only* mapping annotation, so every method carried the verbose form. Spring 4.3 introduced the **composed annotations** — `@GetMapping`, `@PostMapping`, `@PutMapping`, `@DeleteMapping`, `@PatchMapping` — each of which is itself meta-annotated with `@RequestMapping`:

```java
@Target(METHOD) @Retention(RUNTIME) @Documented
@RequestMapping(method = RequestMethod.GET)      // ← literally this
public @interface GetMapping { ... }
```

⚠️ **There is no `@OptionsMapping` or `@HeadMapping`** — and you don't need them. Spring MVC answers `OPTIONS` automatically (listing the allowed methods) and answers `HEAD` by running the `GET` handler and discarding the body. For those you'd use the long form.

**The modern pattern uses both, at different levels:**
```java
@RestController
@RequestMapping("/api/v1/users")        // ← class level: the shared base path
public class UserController {

    @GetMapping                          // GET  /api/v1/users
    public List<UserDto> all() { ... }

    @GetMapping("/{id}")                 // GET  /api/v1/users/5
    public UserDto one(@PathVariable Long id) { ... }

    @PostMapping                         // POST /api/v1/users
    public UserDto create(@RequestBody CreateUserRequest r) { ... }
}
```

**When the long form is still the right call:** one handler that genuinely serves several verbs, or when you need `params` / `headers` conditions.
```java
@RequestMapping(path = "/legacy", method = {RequestMethod.GET, RequestMethod.HEAD})
@RequestMapping(path = "/users", params = "version=2")       // routes by a query param
@RequestMapping(path = "/users", headers = "X-API-Version=2") // routes by a header
```

### W6.7 [+] Type conversion: how `"25"` becomes `25`

Every value arriving over HTTP is a **`String`**. Something has to turn it into an `int`, a `LocalDate`, an enum, a `UUID`. Spring has **two generations** of machinery for this, and knowing which is which resolves a lot of confusion in older tutorials:

| | `PropertyEditor` (old, JavaBeans) | `Converter` / `Formatter` (modern, Spring 3+) |
|---|---|---|
| Interface | `java.beans.PropertyEditor` | `Converter<S,T>`, `Formatter<T>` |
| Thread-safe | ❌ **stateful** — one instance per request | ✅ stateless singletons |
| Registered | per-controller via **`@InitBinder`** | once, globally, as a `@Bean` |
| Examples | `StringTrimmerEditor`, `CustomDateEditor` | `StringToLocalDateConverter` |
| Verdict | legacy; still works | ✅ **prefer this** |

**Built in already:** all primitives and wrappers, `BigDecimal`, `UUID`, `Locale`, `Charset`, `enum` (by name, case-sensitive), `java.time` types (with a format annotation), arrays and collections of any of these.

```java
// The declarative way — handles 95% of real cases, no code at all
public class EventForm {
    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE)      // 2026-09-14
    private LocalDate day;
    @DateTimeFormat(pattern = "dd-MM-yyyy HH:mm")       // 14-09-2026 18:30
    private LocalDateTime startsAt;
    @NumberFormat(style = NumberFormat.Style.CURRENCY)
    private BigDecimal price;
}
```
```java
// A custom global Converter — just declare it as a bean, Boot registers it
@Component
public class StringToOrderStatusConverter implements Converter<String, OrderStatus> {
    @Override
    public OrderStatus convert(String source) {
        return OrderStatus.valueOf(source.trim().toUpperCase());   // case-insensitive enum
    }
}
```

⚠️ **Conversion failures do not throw out of the binder.** For `@ModelAttribute` binding, a bad value becomes a **`typeMismatch` `FieldError`** in the `BindingResult`, leaving the field at its default. That's why `typeMismatch.userForm.age` is a resolvable message code ([§W7.8](#w78-custom-error-messages-q55)). For a `@RequestParam`/`@PathVariable`, it throws `MethodArgumentTypeMismatchException` → 400.

### W6.8 Reading `Converter<String, OrderStatus>`: generics, registration, and where it applies

> **Your question:** *"what does `implements Converter<String, OrderStatus>` mean? how does spring know when to call it, and do we need to register it?"*

**The syntax.** `Converter<S, T>` is a generic interface with one method, `T convert(S source)`. Writing `Converter<String, OrderStatus>` fills in the type parameters: *source* `String`, *target* `OrderStatus`. So the compiler forces your method to be `OrderStatus convert(String source)`. 🐍 It's like `Callable[[str], OrderStatus]`; 🟨 like `(s: string) => OrderStatus` in TypeScript.

**How Spring knows when to use it.** Generic types are normally erased at runtime, but **not** in a class's `implements` clause. When the converter is registered, Spring reads `String → OrderStatus` from that declaration (via `GenericTypeResolver`) and stores it in the `ConversionService` under that pair. Later, when a `@RequestParam OrderStatus status` (or `@PathVariable`, form field) needs a `String` turned into an `OrderStatus`, it looks the pair up.

**Registration (version-proof facts):**
- **Spring Boot:** a `Converter`, `GenericConverter` or `Formatter` **bean** (e.g. `@Component`) is added to MVC's conversion service automatically (`WebMvcAutoConfiguration` → `ApplicationConversionService.addBeans`). That's why the example in [§W6.7](#w67--type-conversion-how-25-becomes-25) needs nothing else.
- **Plain Spring MVC / an `@EnableWebMvc` app:** register it yourself in `WebMvcConfigurer.addFormatters(FormatterRegistry registry) { registry.addConverter(new StringToOrderStatusConverter()); }`.

**Do you even need it?** Enums **already** convert by name (`StringToEnumConverterFactory`), but **case-sensitively**: `?status=NEW` works, while `?status=new` gives a 400. The custom converter in §W6.7 exists only to make it case-insensitive and to trim.

⚠️ Gotchas:
- A **lambda** loses the type information: `registry.addConverter(s -> OrderStatus.valueOf(s))` fails with *"Unable to determine source type <S> and target type <T>"*. Use a class, or `registry.addConverter(String.class, OrderStatus.class, s -> …)`.
- Converters are **not used for JSON bodies**. A `@RequestBody` field of type `OrderStatus` is deserialised by Jackson (use `@JsonCreator` or a Jackson setting for case-insensitivity). See [§W8.3](#w83-httpmessageconverter-and-jackson-who-actually-writes-the-json).
- Converters must be stateless (they're shared singletons). `IllegalArgumentException` thrown inside becomes a 400 type-mismatch.

### W6.9 `@InitBinder` [Q55, Q56]

> **Your question:** *"what is `@InitBinder` and what it does and how does it work? [i think we had some pydantic validation like `method_validator`, `stringConstraint` etc for these]"*

`@InitBinder` is a **method-level annotation that lets you configure the `WebDataBinder`** before it binds anything — a hook to clean, format, restrict, or validate raw input on its way into your Java object.

#### How it works behind the scenes — *(your diagram, preserved)*

```
[ Incoming HTTP Request ] 
          │
          ▼
┌────────────────────────────────┐
│       DispatcherServlet        │
└──────────────┬─────────────────┘
               │
               ▼
┌────────────────────────────────┐
│      WebDataBinder Created     │  <- A fresh binder is instantiated for this request
└──────────────┬─────────────────┘
               │
               ▼
┌────────────────────────────────┐
│     @InitBinder Method Runs    │  <- Your custom logic intercepts the binder here
└──────────────┬─────────────────┘
               │
               ▼
┌────────────────────────────────┐
│    Data Binding & Validation   │  <- Spring parses text, maps fields, and runs validations
└──────────────┬─────────────────┘
               │
               ▼
┌────────────────────────────────┐
│   Target Controller Executed   │  <- The controller receives clean, structured Java objects
└────────────────────────────────┘
```

1. **Instantiation** — for every incoming request destined for a controller, Spring creates a **fresh** `WebDataBinder`. More precisely, it creates one **per argument being bound** (each `@ModelAttribute`, `@RequestParam`, `@PathVariable`, … gets its own), and the `@InitBinder` methods run for each. (Fresh per binding is what makes stateful `PropertyEditor`s safe here.)
2. **Interception** — before parameters are mapped onto your Java object, Spring scans the controller for `@InitBinder` methods and runs them.
3. **Configuration** — your method receives the live `WebDataBinder` and hooks editors, validators or field restrictions onto it.
4. **Execution** — the binder then evaluates the request under those rules and hands the clean object to your controller method.

#### The four core use cases

**1. Scrub and clean input** — trim whitespace globally:
```java
@Controller
public class AccountController {
    @InitBinder
    public void initBinder(WebDataBinder binder) {
        // 'true' → empty strings ("") are converted to null
        StringTrimmerEditor editor = new StringTrimmerEditor(true);
        binder.registerCustomEditor(String.class, editor);   // applies to ALL String properties
    }

    @PostMapping("/submit")
    public String handleForm(@ModelAttribute User user) {
        // user.getUsername() arrives already trimmed
        return "success";
    }
}
```

**2. Format complex types** — a custom date pattern:
```java
@InitBinder
public void initBinder(WebDataBinder binder) {
    SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
    df.setLenient(false);                                     // reject "2026-13-45"
    binder.registerCustomEditor(Date.class, new CustomDateEditor(df, true));
}
```
⚠️ For new code prefer `@DateTimeFormat` on the field, or a `Converter` bean ([§W6.7](#w67--type-conversion-how-25-becomes-25)) — `SimpleDateFormat` is **not thread-safe**, and `java.util.Date` is superseded by `java.time`.

**3. Whitelist / blacklist fields** — prevent mass assignment. See [§W6.11](#w611--mass-assignment-the-vulnerability-initbinder-actually-defends-against).
```java
@InitBinder
public void initBinder(WebDataBinder binder) {
    // The binder will ONLY bind these two. Extra payload keys are quietly dropped.
    binder.setAllowedFields("username", "email");
}
```

**4. Register a programmatic `Validator`:**
```java
@InitBinder("userForm")                        // ← scope to ONE model attribute by name
public void initBinder(WebDataBinder binder) {
    binder.addValidators(new UserFormValidator());   // a Spring org.springframework.validation.Validator
}
```

#### Scope: controller-specific vs. global

| Placement | Applies to |
|---|---|
| inside a `@Controller` / `@RestController` | **only** requests hitting that controller |
| inside a `@ControllerAdvice` | **every** controller in the application |
| `@InitBinder("userForm")` | only the model attribute with that name |

```java
@ControllerAdvice
public class GlobalBindingConfig {
    @InitBinder
    public void globalBinder(WebDataBinder binder) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        dateFormat.setLenient(false);
        binder.registerCustomEditor(Date.class, new CustomDateEditor(dateFormat, true));
    }
}
```

🐍 **Your Pydantic instinct is right, with one important difference.** `@InitBinder` is conceptually `@field_validator(mode="before")` — it runs on **raw input before parsing/validation**. But the scopes differ:

| | Pydantic | Spring |
|---|---|---|
| Attached to | the **model** | the **controller** |
| Travels with the type | ✅ everywhere that model is used | ❌ only in that controller (or advice) |
| Pre-parse hook | `@field_validator(mode="before")` | `@InitBinder` + `PropertyEditor` |
| Post-parse rule | `@field_validator` / `@model_validator` | `@AssertTrue` / a custom `ConstraintValidator` ([§W7.7](#w77-custom-validation-annotations-q55)) |
| Global type coercion | a custom type / `Annotated[...]` | a **`Converter` bean** ← the real Spring analogue |

💡 So: **for "always coerce this type this way", use a `Converter` bean, not `@InitBinder`.** `@InitBinder` is for controller-scoped concerns — most importantly field restriction.

⚠️ **For `@RequestBody`, `@InitBinder` only half-applies.** JSON deserialization is Jackson's job, so trimming, whitelisting (`setAllowedFields`) and custom editors registered here **don't affect the JSON body**. They affect `@RequestParam`, `@PathVariable` and `@ModelAttribute` only. For JSON, configure Jackson instead (a `Jackson2ObjectMapperBuilderCustomizer` bean on Boot 2.7/3, `JsonMapperBuilderCustomizer` on Boot 4, or `@JsonDeserialize` on the field).
📌 **Corrected:** an earlier version of this note said `@InitBinder` doesn't *run* for `@RequestBody`. It does. `RequestResponseBodyMethodProcessor` creates a `WebDataBinder` for the deserialized object (to validate it), and your `@InitBinder` methods configure that binder. So **validators added with `binder.addValidators(...)` do apply to `@Valid @RequestBody`** (verified in the Framework source).

### W6.10 `@InitBinder` follow-up questions

> **Your questions, merged:** *"what does 'bound' mean here?"* · *"does it apply to method arguments or to fields of the object?"* · *"is a registered editor for all Strings or for one field?"* · *"is the editor shared between requests?"* · *"does it work for @RequestBody?"* · plus the two example scenarios (trimming a form, and a `couponCode` request parameter).

**"Bound" = copied from the request into Java.** *Binding* is the step where a request value (a query parameter, form field or path segment, all strings) is converted and **assigned** to a method argument or to a property of an object. "Bound fields" are the properties that received a value.

**Method arguments or fields?** Both, depending on the argument:
- `@ModelAttribute UserForm form`: the binder sets **properties of the object** (`form.setEmail(...)`). `setAllowedFields`, nested paths and per-field editors are all about these properties.
- `@RequestParam String q`, `@PathVariable`, `@RequestHeader`: the binder converts **one value for that argument**. There is no object and no field list, so `setAllowedFields` doesn't apply.

**All Strings or one field?**
```java
binder.registerCustomEditor(String.class, new StringTrimmerEditor(true));               // every String
binder.registerCustomEditor(String.class, "couponCode", new StringTrimmerEditor(true)); // only property path "couponCode"
```
The second form matches a **property path** of a `@ModelAttribute` object.

**Is it shared between requests?** No. A new `WebDataBinder` is created **per argument being bound, per request**, and your `@InitBinder` method runs again for each one. That's why `new SimpleDateFormat(...)`/`new StringTrimmerEditor(...)` *inside* the method is safe. ⚠️ Don't store an editor instance in a field and reuse it: `PropertyEditor`s are stateful and not thread-safe.

**Does it work for `@RequestBody`?** Partly; see the corrected warning in [§W6.9](#w69-initbinder-q55-q56). Validators added with `binder.addValidators(...)` **do** run for `@Valid @RequestBody`. Editors, trimming and `setAllowedFields` do **not**, because Jackson has already built the object.

#### Scenario A — trimming a registration form (works as written)
```java
@InitBinder("userForm")
void trim(WebDataBinder b) { b.registerCustomEditor(String.class, new StringTrimmerEditor(true)); }

@PostMapping("/register")
String register(@Valid @ModelAttribute("userForm") UserForm form, BindingResult br) { … }
// "  alice  " → "alice";  "   " → null → @NotBlank reports it
```

#### Scenario B — a `couponCode` request parameter (the version-sensitive one)
```java
@GetMapping("/checkout")
String checkout(@RequestParam(required = false) String couponCode) { … }
```
**Correction to the source answer (verified in the Framework source):** whether a **path-specific** editor `registerCustomEditor(String.class, "couponCode", editor)` applies to this `@RequestParam` depends on the version:

| Version | Path-specific editor applied to `@RequestParam couponCode`? | Why |
|---|---|---|
| Framework 5.3 (Boot 2.7), 6.0 | ❌ silently ignored | `TypeConverterSupport.convertIfNecessary(value, type, methodParam)` converts with **no property name**, so only type-wide editors match |
| Framework 6.1+ (Boot 3.2+, Boot 4) | ✅ applied (only if compiled with `-parameters`) | 6.1 started passing `methodParam.getParameterName()` as the property name |

**Version-proof way:** scope the `@InitBinder` to the parameter name and register a **type-wide** editor. For `@RequestParam`, the binder's object name is the parameter name, so `@InitBinder("couponCode")` matches only that argument:
```java
@InitBinder("couponCode")
void couponCode(WebDataBinder b) {
    b.registerCustomEditor(String.class, new StringTrimmerEditor(true));   // trim + "" → null
}
```

**When not to use `@InitBinder`:**
- for type coercion everywhere → a `Converter` bean ([§W6.8](#w68-reading-converterstring-orderstatus-generics-registration-and-where-it-applies));
- for JSON → Jackson config;
- for validation rules that belong to the type → Bean Validation annotations ([§W7](#w7-validation-q55)).

### W6.11 [+] Mass assignment: the vulnerability `@InitBinder` actually defends against

Appending `&role=ADMIN` to a form post is not a hypothetical attack — it is the **mass assignment** vulnerability class, and it produced **CVE-2022-22965 ("Spring4Shell", CVSS 9.8)** in March 2022.

**The mechanism.** `WebDataBinder` walks **nested property paths**. Given `@ModelAttribute User user`, a parameter named `address.city` reaches `user.getAddress().setCity(...)`. On JDK 9+, `user.getClass()` returns a `Class`, which exposes `getModule()`, which chains onward — so a crafted parameter like `class.module.classLoader.resources.context.parent.pipeline.first.directory` could reach into Tomcat's access-log valve and **write an arbitrary file to disk**, i.e. drop a web shell. Unauthenticated RCE.

**Three layers of defence, in order of preference:**

```java
// 1. ✅ BEST: bind to a purpose-built DTO that has no dangerous properties at all.
//    A record is immutable and has no setters — nothing to mass-assign.
public record UpdateProfileRequest(String displayName, String email) {}
//    Note there is simply no `role` field. The attack has nothing to aim at.

// 2. ✅ Explicit whitelist, per controller
@InitBinder
public void initBinder(WebDataBinder binder) {
    binder.setAllowedFields("displayName", "email");
}

// 3. ✅ Global blacklist — the official Spring4Shell mitigation for un-upgradable apps
@ControllerAdvice
@Order(Ordered.LOWEST_PRECEDENCE)
public class BinderControllerAdvice {
    @InitBinder
    public void setAllowedFields(WebDataBinder dataBinder) {
        dataBinder.setDisallowedFields("class.*", "Class.*", "*.class.*", "*.Class.*");
    }
}
```

⚠️ **Never bind a JPA `@Entity` directly with `@ModelAttribute` or `@RequestBody`.** Your entity has every column as a settable property — `id`, `role`, `credits`, `passwordHash`, `createdAt`. A client can set all of them. Bind to a DTO and map explicitly. This is the same point as [§P5.2](06-spring-production.md#p52-dtos-vs-entities--never-expose-your-entities-) and it is the single highest-value habit in this section.

💡 **Spring Framework 6.1** added `DataBinder.setDeclarativeBinding(true)`, which binds only paths you explicitly allow. And **constructor binding** (records) is inherently safe: values go through the canonical constructor, so only declared components can be set.

🐍🟨 The same bug class is `Object.assign(user, req.body)` in Express and `User(**request.json)` in Python. The defence is identical: an explicit schema, never the raw payload.

---

## W7. Validation [Q55]

> **Your question:** *"how does spring handles form validation [are these similar to zod in express or pydantic in python + fastapi?] what is the standard beanvalidation api? does it also valid for thymeleaf or only applicable to spring boot?"*

### W7.1 The three layers — spec, implementation, integration

Most confusion here comes from conflating three different things:

```
┌──────────────────────────────────────────────────────────────────────┐
│ 1. THE SPECIFICATION      Jakarta Bean Validation  (jakarta.validation.*) │
│    Defines @NotNull, @Size, ConstraintValidator, the Validator API.  │
│    Version history:  JSR 303 (1.0, 2009) → JSR 349 (1.1, 2013)       │
│                    → JSR 380 (2.0, 2017, javax.validation)           │
│                    → Jakarta Bean Validation 3.0 (2020, JAKARTA.*)   │
│                    → Jakarta Validation 3.1 (2024)                   │
├──────────────────────────────────────────────────────────────────────┤
│ 2. THE IMPLEMENTATION     Hibernate Validator  (the reference impl)  │
│    The engine that actually runs the checks. Alternative: Apache BVal.│
│    Adds extras beyond the spec: @URL, @Length, @Range, @CreditCardNumber │
├──────────────────────────────────────────────────────────────────────┤
│ 3. THE SPRING INTEGRATION LocalValidatorFactoryBean, SpringValidatorAdapter │
│    Bridges 1+2 into Spring's own `org.springframework.validation.Validator`, │
│    wires the MessageSource in, and triggers it from @Valid in MVC.   │
└──────────────────────────────────────────────────────────────────────┘
```

> 📌 **Three names, three different things — keep them apart.** **JSR 380 is Bean Validation 2.0**, which used the `javax.validation` package. **Jakarta Bean Validation 3.0+** is the `jakarta.validation` rename that Spring 6 / Boot 3 require. **Hibernate Validator is the reference *implementation*** — a separate artifact, maintained by Red Hat, that you can swap for Apache BVal; it is not another name for the spec. Getting this straight matters practically: if you copy a tutorial that imports `javax.validation.constraints.NotNull` into a Boot 3 project, **the annotation is silently ignored** — it compiles, it just never validates.
> Sources: [beanvalidation.org/2.0-jsr380](https://beanvalidation.org/2.0-jsr380/), [Hibernate Validator docs](https://docs.jboss.org/hibernate/validator/6.0/reference/en-US/pdf/hibernate_validator_reference.pdf)

⚠️ **The dependency is not in `spring-boot-starter-web`.** Since Boot 2.3 it is separate, and forgetting it is the single most common reason `@Valid` "doesn't work" — there is **no error**, validation simply never runs:
```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-validation</artifactId>
</dependency>
```

**Is it Spring-specific, or Thymeleaf-specific?** **Neither.** Bean Validation operates on plain Java objects. The same annotated class validates identically in a REST controller, behind a Thymeleaf form, in a `@Service`, in a batch job, or in a plain `main()` with no Spring at all:
```java
Validator v = Validation.buildDefaultValidatorFactory().getValidator();   // pure Jakarta, no Spring
Set<ConstraintViolation<UserForm>> violations = v.validate(form);
```
It is also what **Hibernate ORM** runs on `pre-insert`/`pre-update`, and what generates `NOT NULL`/`VARCHAR(n)` in a generated DDL schema.

### W7.2 `javax.annotation.Nonnull` vs Bean Validation [Q55]

> **Your question:** *"are `import javax.annotation.Nonnull; import javax.annotation.Nullable;` different from the validation bean apis?"*

**Completely different tools with different targets.** They only look similar.

| | `javax.annotation.Nonnull` / `Nullable` (JSR-305) | `jakarta.validation.constraints.NotNull` |
|---|---|---|
| Purpose | **static analysis** — help the IDE/compiler warn you | **runtime** data validation |
| When it acts | while you type / at build time | when an HTTP request arrives |
| Stops a bad request | ❌ never | ✅ 400 Bad Request |
| Runtime cost | zero — often not even retained | reflection + validator engine |
| Provided by | `com.google.code.findbugs:jsr305` | `spring-boot-starter-validation` |
| Status | ⚠️ JSR-305 was **never ratified** and is dormant | active standard |

⚠️ **The most common resulting bug:** someone writes `@Nonnull String email` on a controller parameter, sees the annotation name, assumes it validates, and ships an endpoint that happily accepts `null`.

**Nullability annotations in the Spring world (2026):** there are four families, and Spring is consolidating on the last one.

| Family | Package | Notes |
|---|---|---|
| JSR-305 | `javax.annotation.Nonnull` | dormant, unratified — avoid in new code |
| Spring's own | `org.springframework.lang.NonNull`, `@Nullable` | used throughout Spring's own source |
| JetBrains | `org.jetbrains.annotations.NotNull` | best IntelliJ integration |
| **JSpecify** | `org.jspecify.annotations.Nullable` | ✅ **the emerging standard**; adopted across Spring Framework 7 |

💡 **Rule of thumb:** nullability annotations document a **contract between developers**. Bean Validation enforces a **contract with the outside world**. You want both, for different reasons — and only one of them is a security control.

### W7.3 The annotation catalogue [Q55]

**Jakarta Bean Validation — the standard constraints:**

| Annotation | Checks | Applies to |
|---|---|---|
| `@NotNull` | not null. ⚠️ **`""` passes** | any object |
| `@NotEmpty` | not null **and** size/length > 0. ⚠️ **`"   "` passes** | `String`, `Collection`, `Map`, array |
| `@NotBlank` | not null, and contains ≥ 1 non-whitespace char | `String` only |
| `@Size(min=, max=)` | length or collection size within bounds | `String`, `Collection`, `Map`, array |
| `@Min(v)` / `@Max(v)` | numeric bound (inclusive) | integral numbers |
| `@DecimalMin` / `@DecimalMax` | bound as a `String`, so exact for `BigDecimal` | `BigDecimal`, etc. |
| `@Positive` / `@PositiveOrZero` | > 0 / ≥ 0 | numbers |
| `@Negative` / `@NegativeOrZero` | < 0 / ≤ 0 | numbers |
| `@Digits(integer=, fraction=)` | digit counts either side of the point | numbers |
| `@Email` | well-formed email | `String` |
| `@Pattern(regexp=)` | regex match | `String` |
| `@Past` / `@PastOrPresent` | date in the past | `java.time.*`, `Date` |
| `@Future` / `@FutureOrPresent` | date in the future | `java.time.*`, `Date` |
| `@AssertTrue` / `@AssertFalse` | ✅ **cross-field rules** — put it on a `boolean` getter | `boolean` |
| `@Valid` | **cascade** into a nested object or collection elements | objects, collections |

**Hibernate Validator extras** (available because it's the implementation you have):

| Annotation | Checks |
|---|---|
| `@Length(min=, max=)` | like `@Size` but `String`-only |
| `@Range(min=, max=)` | `@Min` + `@Max` in one |
| `@URL` | well-formed URL |
| `@CreditCardNumber` | Luhn check |
| `@UniqueElements` | no duplicates in a collection |
| `@ISBN`, `@EAN` | identifier formats |

⚠️ **`@NotNull` vs `@NotEmpty` vs `@NotBlank` is the most-asked interview question in this area:**

| value | `@NotNull` | `@NotEmpty` | `@NotBlank` |
|---|---|---|---|
| `null` | ❌ | ❌ | ❌ |
| `""` | ✅ pass | ❌ | ❌ |
| `"   "` | ✅ pass | ✅ pass | ❌ |
| `"a"` | ✅ | ✅ | ✅ |

💡 **For a user-supplied `String`, you almost always want `@NotBlank`.**

#### Validating a number range [Q55]

> **Your question:** *"how to validate a number range?"*

```java
@Min(value = 18, message = "Age must be at least 18")
@Max(value = 99, message = "Age cannot exceed 99")
private int age;

// equivalent, Hibernate-specific, one annotation:
@Range(min = 18, max = 99, message = "Age must be between 18 and 99")
private int age;

// for money — @Min takes a long, so use the String-based ones for BigDecimal:
@DecimalMin(value = "0.01", inclusive = true)
@DecimalMax(value = "10000.00")
@Digits(integer = 5, fraction = 2)
private BigDecimal amount;
```

#### Cascading into nested objects and collections

```java
public record CreateOrderRequest(
        @NotBlank String customerId,
        @NotEmpty @Valid List<ItemDto> items,      // ← @Valid CASCADES into each element
        @Valid Address shippingAddress) {}          // ← and into the nested object

public record ItemDto(@NotBlank String sku, @Min(1) @Max(999) int qty) {}
```
⚠️ **Without the inner `@Valid`, the nested constraints are never evaluated.** `@NotEmpty` alone would check that the list is non-empty and stop there.

#### Cross-field validation with `@AssertTrue`

The cheapest way to express "field A must relate to field B" — no custom annotation needed:
```java
public class DateRangeForm {
    @NotNull private LocalDate from;
    @NotNull private LocalDate to;

    @AssertTrue(message = "'to' must be on or after 'from'")
    public boolean isRangeValid() {                    // ← the property name becomes "rangeValid"
        return from == null || to == null || !to.isBefore(from);
    }
}
```
⚠️ The method **must** follow the JavaBeans `isXxx()`/`getXxx()` naming convention, and must tolerate nulls (the `@NotNull`s report those separately). The resulting error attaches to the synthetic field `rangeValid`, not to `from` or `to` — use a custom class-level constraint ([§W7.7](#w77-custom-validation-annotations-q55)) if you need the error on a specific field.

### W7.4 `@Valid` vs `@Validated`

| | `@Valid` | `@Validated` |
|---|---|---|
| From | `jakarta.validation` (the standard) | `org.springframework.validation.annotation` (Spring) |
| Supports validation **groups** | ❌ | ✅ `@Validated(OnCreate.class)` |
| On a method **parameter** | ✅ | ✅ |
| Cascades into nested objects | ✅ | ❌ *(use `@Valid` inside)* |
| On a **class** to enable method validation | ❌ | ✅ |

```java
// Groups: the same DTO validated differently for create vs update
public interface OnCreate {}
public interface OnUpdate {}

public class UserDto {
    @Null(groups = OnCreate.class)      @NotNull(groups = OnUpdate.class) private Long id;
    @NotBlank(groups = {OnCreate.class, OnUpdate.class})                  private String email;
}

@PostMapping public UserDto create(@Validated(OnCreate.class) @RequestBody UserDto d) { ... }
@PutMapping  public UserDto update(@Validated(OnUpdate.class) @RequestBody UserDto d) { ... }
```

**Validating loose parameters** (not a DTO). On **Boot 2.7 / Framework ≤6.0** this needs `@Validated` **on the class**, which switches on AOP-based method validation:
```java
@RestController
@Validated                                    // ← REQUIRED for the annotations below to fire
public class SearchController {
    @GetMapping("/search")
    public List<Hit> search(@RequestParam @NotBlank @Size(max = 100) String q,
                            @RequestParam @Min(1) @Max(100) int limit) { ... }
}
```
⚠️ **Boot 2.7 / Framework 5.3–6.0:** without class-level `@Validated`, `@NotBlank` on a `@RequestParam` is **silently ignored**. And because it's AOP-based, a violation throws **`ConstraintViolationException`** (→ 500 by default) rather than `MethodArgumentNotValidException` (→ 400), so you must handle it.

✅ **Framework 6.1+ (Boot 3.2+, Boot 4): built-in method validation.** Spring MVC now validates constraint annotations on controller parameters **itself**, with no class-level `@Validated`. A violation raises **`HandlerMethodValidationException` → 400**. The Framework reference is explicit: *"If a controller has a class level `@Validated`, then method validation is applied through an AOP proxy. In order to take advantage of the Spring MVC built-in support for method validation added in Spring Framework 6.1, you need to remove the class level `@Validated` annotation from the controller."* When parameters carry constraints, the built-in method validation also covers `@Valid @RequestBody` in the same method and reports through `HandlerMethodValidationException`. So a modern `@RestControllerAdvice` should handle **both** `MethodArgumentNotValidException` and `HandlerMethodValidationException`.

### W7.5 Where validation runs, and what gets thrown

```
@RequestBody + @Valid  ─── fails ──→ MethodArgumentNotValidException  → 400  (automatic)
@ModelAttribute + @Valid ─ fails ──→ BindException                    → 400  (automatic)
                                     ...unless a BindingResult follows the parameter,
                                        in which case NOTHING is thrown and you inspect it
@RequestParam + @Validated on class ─→ ConstraintViolationException            (AOP; Boot 2.7 style)
@RequestParam + constraints, 6.1+ ───→ HandlerMethodValidationException        → 400  (built-in)
service method + @Validated on class → ConstraintViolationException   → 500 unless handled
```

> 📌 **Omit `BindingResult` and the two paths throw *different* exceptions.** `@RequestBody` + `@Valid` throws **`MethodArgumentNotValidException`**; `@ModelAttribute` + `@Valid` — the *form* case — throws **`BindException`**. They are easy to conflate because since **Spring Framework 6.0** `MethodArgumentNotValidException extends BindException`, so catching `BindException` catches both. It did **not** in Spring 5.
> Source: [MethodArgumentNotValidException javadoc](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/bind/MethodArgumentNotValidException.html)

### W7.6 `BindingResult` [Q55]

> **Your question:** *"what is BindingResult?"*

`BindingResult` is the **error report** produced by binding + validation. Declaring it as a parameter tells Spring *"don't throw — hand me the errors and let me decide."*

```java
@PostMapping("/register")
public String register(@Valid @ModelAttribute("userForm") UserForm form,
                       BindingResult bindingResult) {     // ⚠️ MUST be immediately after
    if (bindingResult.hasErrors()) {
        return "registration-form";                       // re-render the form with errors
    }
    userService.register(form);
    return "redirect:/success";
}
```

⚠️ **The position is load-bearing.** `BindingResult` must be the **immediately following** parameter. This does *not* work — Spring can't tell which object the result belongs to, and throws `IllegalStateException` at startup or binds the result to the wrong target:
```java
public String register(@Valid UserForm form, Model model, BindingResult result)   // ❌ WRONG
public String register(@Valid UserForm form, BindingResult result, Model model)   // ✅ RIGHT
```
With two validated objects you need two results, each following its own object:
```java
public String x(@Valid A a, BindingResult ra, @Valid B b, BindingResult rb)       // ✅
```

**The useful API:**
```java
bindingResult.hasErrors()                       // any error at all?
bindingResult.hasFieldErrors("email")           // this field specifically?
bindingResult.getFieldErrors()                  // List<FieldError>
bindingResult.getGlobalErrors()                 // List<ObjectError> — whole-object errors
bindingResult.getFieldError("email").getDefaultMessage();
bindingResult.getFieldError("email").getRejectedValue();   // what the user actually typed
bindingResult.rejectValue("email", "duplicate", "That email is already registered.");  // add your own
bindingResult.reject("form.invalid", "Something is wrong with this form.");            // global
```

💡 `rejectValue` is how you add **business-rule errors** (duplicate email, insufficient balance) to the *same* error collection as the annotation-driven ones, so the view renders them identically.

⚠️ **In a `@RestController`, do NOT use `BindingResult`.** It forces per-endpoint error-formatting boilerplate. Let `MethodArgumentNotValidException` propagate and format it **once** in a `@RestControllerAdvice` ([§W8.8](#w88-global-exception-handling-with-problemdetail-)). `BindingResult` belongs to the server-rendered-form flow, where re-displaying the form *is* the error handling.

### W7.7 Custom validation annotations [Q55]

> **Your question:** *"how to add custom validation (i think we need to create our custom java annotation for that?)"*

**Yes — two pieces: the annotation, and a `ConstraintValidator` that implements it.**

**Step A — the annotation:**
```java
package com.example.demo.validation;

import jakarta.validation.Constraint;
import jakarta.validation.Payload;
import java.lang.annotation.*;

@Target({ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)                 // ⚠️ MUST be RUNTIME — reflection reads it
@Constraint(validatedBy = CouponValidator.class)    // links the annotation to its logic
public @interface ValidCoupon {
    String message() default "Invalid coupon code format.";   // ⚠️ these three members are
    Class<?>[] groups() default {};                           //    MANDATORY by the spec —
    Class<? extends Payload>[] payload() default {};          //    omit one and it won't compile
}
```

**Step B — the validator:**
```java
package com.example.demo.validation;

import jakarta.validation.ConstraintValidator;
import jakarta.validation.ConstraintValidatorContext;

public class CouponValidator implements ConstraintValidator<ValidCoupon, String> {
    @Override
    public boolean isValid(String value, ConstraintValidatorContext context) {
        if (value == null || value.trim().isEmpty()) {
            return true;     // ⚠️ let @NotBlank own emptiness — one constraint, one concern
        }
        return value.toUpperCase().startsWith("SAVE");   // the business rule
    }
}
```

⚠️ **Returning `true` for null is the convention, not an oversight.** If every constraint also rejected null, a null field would produce three or four errors instead of one. Let `@NotNull`/`@NotBlank` report nullness; let your constraint report *format*.

💡 **A `ConstraintValidator` is a Spring bean — you can inject into it.** This is how you write a database-backed rule:
```java
public class UniqueEmailValidator implements ConstraintValidator<UniqueEmail, String> {
    private final UserRepository repo;
    public UniqueEmailValidator(UserRepository repo) { this.repo = repo; }   // ✅ injected

    @Override public boolean isValid(String email, ConstraintValidatorContext ctx) {
        return email == null || !repo.existsByEmail(email);
    }
}
```
⚠️ But be careful: this runs a query on **every** validation, it can't see other fields, and it is inherently racy (you still need a `UNIQUE` constraint in the database). For anything beyond a simple existence check, do it in the service layer and report it with `bindingResult.rejectValue(...)`.

**A class-level constraint** — when the rule spans fields and you want the error on a specific one:
```java
@Target({ElementType.TYPE})                       // ← TYPE, not FIELD
@Retention(RetentionPolicy.RUNTIME)
@Constraint(validatedBy = PasswordsMatchValidator.class)
public @interface PasswordsMatch {
    String message() default "Passwords do not match";
    Class<?>[] groups() default {};
    Class<? extends Payload>[] payload() default {};
}

public class PasswordsMatchValidator implements ConstraintValidator<PasswordsMatch, SignupForm> {
    @Override public boolean isValid(SignupForm f, ConstraintValidatorContext ctx) {
        if (Objects.equals(f.getPassword(), f.getConfirmPassword())) return true;
        ctx.disableDefaultConstraintViolation();              // don't attach to the class
        ctx.buildConstraintViolationWithTemplate(ctx.getDefaultConstraintMessageTemplate())
           .addPropertyNode("confirmPassword")                // ← attach the error HERE
           .addConstraintViolation();
        return false;
    }
}
```

### W7.8 Custom error messages [Q55]

> **Your question:** *"for defining custom error message do we need to use some special file name inside the resource folder like message.properties and how to define the custom error message for a particular field and particular error type because a field might have several error messages based on the error type [like `typeMismatch.custom-object.age="custom-error"`]?"*

**Your instinct is right, and the hierarchical-key idea is exactly how it works.** But there are **two separate file conventions**, and mixing them up is a common time sink:

| File | Owned by | Exact location | Resolves |
|---|---|---|---|
| **`ValidationMessages.properties`** | Jakarta Bean Validation (the spec) | **classpath root**, name is mandated | `{braced.keys}` inside the annotation's `message` attribute |
| **`messages.properties`** | Spring (`MessageSource`) | `src/main/resources/`, name configurable via `spring.messages.basename` | Spring **error codes** like `Min.userForm.age`, plus `{braced.keys}` (Boot bridges them) |

💡 **In a Spring Boot app, use `messages.properties` for everything** — Boot's `MessageInterpolatorFactory` wraps Hibernate's interpolator in a `MessageSourceMessageInterpolator`, so `{braced.keys}` in annotations also resolve from your Spring `MessageSource`. You rarely need `ValidationMessages.properties` at all.

#### The error-code hierarchy

When Spring turns a `ConstraintViolation` into a `FieldError`, it generates a **ranked list of codes** (`DefaultMessageCodesResolver`), most specific first:

```
For @Min failing on UserForm.age (an int):

    Min.userForm.age      ← most specific: this constraint, this object, this field
    Min.age               ← this constraint, any object, this field name
    Min.int               ← this constraint, this field TYPE
    Min                   ← this constraint anywhere
    <the annotation's interpolated `message` attribute>   ← the fallback default
```

The `MessageSource` tries each code in turn; the **first that resolves wins**. This gives you exactly what you asked for: **different messages for different failure types on the same field.**

```properties
# src/main/resources/messages.properties

# Conversion failure — user typed letters into a numeric input.
# `typeMismatch` is generated by the BINDER, not by an annotation.
typeMismatch.userForm.age=Please enter a valid whole number for your age.

# Constraint failures on the SAME field, distinguished by which constraint failed
Min.userForm.age=Registration is restricted to individuals 18 years and older.
Max.userForm.age=Age value cannot exceed 99 years.
NotBlank.userForm.username=Username cannot be blank.
Size.userForm.username=Username must be between {2} and {1} characters.

# Broad fallbacks
NotBlank=This field is required.
typeMismatch=Invalid value.
```

⚠️ Note the numbered placeholders: **`{0}` is the field name, and `{1}`, `{2}`… are the constraint's attributes in *alphabetical order of attribute name***. For `@Size(min=3, max=20)` that's `max` then `min` → `{1}` is `max` and `{2}` is `min`. Counter-intuitive, and worth a comment in the file.

⚠️ **The properties file wins over the annotation's `message` attribute.** The annotation message is only the *default* used when no code resolves. So `@Size(message = "too long")` is overridden by a matching `Size.userForm.username` entry — useful for i18n, surprising when you're debugging.

**Internationalisation is then free** — add `messages_de.properties`, `messages_fr.properties`, and Spring picks by `Accept-Language`:
```properties
spring.messages.basename=messages,validation-messages
spring.messages.encoding=UTF-8
spring.messages.fallback-to-system-locale=false
```

⚠️ **[+] These codes are NOT applied automatically in a JSON API.** Thymeleaf's `th:errors` and JSP's `<form:errors>` run each `FieldError` through the `MessageSource`. Boot's default JSON error body does **not** — it uses `getDefaultMessage()`, i.e. the annotation's message. To get `messages.properties` resolution in a REST response you must do it yourself:
```java
@RestControllerAdvice
@RequiredArgsConstructor
public class ValidationAdvice {
    private final MessageSource messageSource;

    @ExceptionHandler(MethodArgumentNotValidException.class)
    public ProblemDetail onInvalid(MethodArgumentNotValidException ex, Locale locale) {
        Map<String, String> errors = new LinkedHashMap<>();
        for (FieldError fe : ex.getBindingResult().getFieldErrors()) {
            // FieldError implements MessageSourceResolvable → resolves Min.userForm.age & co.
            errors.put(fe.getField(), messageSource.getMessage(fe, locale));
        }
        ProblemDetail pd = ProblemDetail.forStatus(HttpStatus.BAD_REQUEST);
        pd.setTitle("Validation failed");
        pd.setProperty("errors", errors);
        return pd;
    }
}
```

### W7.9 End-to-end worked example [Q55]

> **Your question:** *"show me an end to end example of spring validation of a field validation for a form… explain with an example with all of these above asked getting used there"*

**Scenario:** a registration form with a number range, a custom `@ValidCoupon` constraint, externalised messages, `@InitBinder` trimming, `BindingResult`, and Thymeleaf error rendering — every piece you asked about, in one flow.

**Step A — the custom annotation + validator** — as in [§W7.7](#w77-custom-validation-annotations-q55) (`ValidCoupon` / `CouponValidator`).

**Step B — the form backing bean:**
```java
package com.example.demo.dto;

import com.example.demo.validation.ValidCoupon;
import jakarta.validation.constraints.*;          // ⚠️ jakarta, NOT javax (Boot 3+)

public class UserForm {

    @NotBlank(message = "Username cannot be blank.")
    @Size(min = 3, max = 20, message = "Username must be between 3 and 20 characters.")
    private String username;

    @Min(value = 18)                 // message resolved from messages.properties
    @Max(value = 99)
    private int age;

    @ValidCoupon                     // our custom constraint
    private String promoCode;

    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }
    public int getAge() { return age; }
    public void setAge(int age) { this.age = age; }
    public String getPromoCode() { return promoCode; }
    public void setPromoCode(String promoCode) { this.promoCode = promoCode; }
}
```
💡 This uses getters/setters because Thymeleaf's `th:field` needs a mutable bean to re-render rejected input. **For a JSON API, use a `record` instead** — immutable, no boilerplate, and constructor binding is mass-assignment-safe ([§W6.11](#w611--mass-assignment-the-vulnerability-initbinder-actually-defends-against)).

**Step C — `src/main/resources/messages.properties`:**
```properties
# Custom override when the user inputs text instead of an integer
typeMismatch.userForm.age=The age entered must be a valid numeric number.

# Hierarchy overrides for validation constraints
Min.userForm.age=Registration is restricted to individuals 18 years and older.
Max.userForm.age=Age value cannot exceed 99 years.
```

**Step D — the controller:**
```java
package com.example.demo.controller;

import com.example.demo.dto.UserForm;
import jakarta.validation.Valid;
import org.springframework.beans.propertyeditors.StringTrimmerEditor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.WebDataBinder;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/register")
public class UserRegistrationController {

    // Trims whitespace from every incoming String; "" becomes null
    @InitBinder
    public void initBinder(WebDataBinder dataBinder) {
        StringTrimmerEditor stringTrimmerEditor = new StringTrimmerEditor(true);
        dataBinder.registerCustomEditor(String.class, stringTrimmerEditor);
    }

    // GET /register — render the empty form
    @GetMapping
    public String showForm(Model model) {
        model.addAttribute("userForm", new UserForm());   // ⚠️ key MUST match th:object
        return "registration-form";
    }

    // POST /register — handle the submission
    @PostMapping
    public String processRegistration(
            @Valid @ModelAttribute("userForm") UserForm userForm,
            BindingResult bindingResult,                  // ⚠️ immediately after the object
            Model model) {

        if (bindingResult.hasErrors()) {
            return "registration-form";                   // re-render WITH errors + rejected values
        }
        return "registration-success";
    }
}
```

**Step E — `src/main/resources/templates/registration-form.html`:**
```html
<!DOCTYPE html>
<html xmlns:th="http://thymeleaf.org">
<head><title>User Registration</title></head>
<body>
    <h2>Create an Account</h2>

    <form th:action="@{/register}" th:object="${userForm}" method="post">
        <div>
            <label>Username:</label>
            <input type="text" th:field="*{username}" />
            <!-- Displays structural validation error for username -->
            <p th:if="${#fields.hasErrors('username')}" th:errors="*{username}" style="color:red;"></p>
        </div>

        <div>
            <label>Age:</label>
            <input type="text" th:field="*{age}" />
            <!-- Displays either type mismatch or min/max numeric range errors -->
            <p th:if="${#fields.hasErrors('age')}" th:errors="*{age}" style="color:red;"></p>
        </div>

        <div>
            <label>Promo Code:</label>
            <input type="text" th:field="*{promoCode}" />
            <!-- Displays custom annotation validation failure -->
            <p th:if="${#fields.hasErrors('promoCode')}" th:errors="*{promoCode}" style="color:red;"></p>
        </div>

        <button type="submit">Submit Registration</button>
    </form>
</body>
</html>
```
💡 `th:field="*{age}"` expands to `id="age" name="age" value="<current value>"` — including the **rejected** value, so the user doesn't lose what they typed. That single behaviour is most of why server-rendered forms use `@ModelAttribute` + `BindingResult` rather than exceptions.

**The full request trace on a bad submission** (`username=" ab "`, `age=abc`, `promoCode=XYZ`):

| Step | What happens |
|---|---|
| 1 | `POST /register`, `Content-Type: x-www-form-urlencoded` |
| 2 | `@InitBinder` registers the `StringTrimmerEditor` on a fresh `WebDataBinder` |
| 3 | Bind `username` → trimmed to `"ab"` ✅ set |
| 4 | Bind `age` → `"abc"` can't convert → **`typeMismatch` FieldError**, `age` stays `0` |
| 5 | Bind `promoCode` → `"XYZ"` ✅ set |
| 6 | Validation runs: `@Size(min=3)` fails on `"ab"`; `@ValidCoupon` fails on `"XYZ"`; `@Min(18)` is **skipped** — Spring doesn't re-validate a field that already failed conversion |
| 7 | `BindingResult` now holds 3 `FieldError`s |
| 8 | `hasErrors()` → true → return `"registration-form"` |
| 9 | Thymeleaf renders; `th:errors` resolves each via `MessageSource`: `typeMismatch.userForm.age` hits, `Size.userForm.username` misses → falls back to the annotation's `message` |
| 10 | User sees three red messages, with their input still in the boxes |

### W7.10 Validation in a REST API — what changes

```java
@RestController
@RequestMapping("/api/users")
@Validated                                            // needed on Boot 2.7; on 6.1+ REMOVE it (built-in validation, W7.4)
public class UserApiController {

    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public UserDto create(@Valid @RequestBody CreateUserRequest req) {   // no BindingResult!
        return service.create(req);
    }

    @GetMapping
    public List<UserDto> search(@RequestParam @NotBlank @Size(max = 50) String q) {
        return service.search(q);
    }
}
```

| | Form (MVC) | REST (JSON) |
|---|---|---|
| Binding | `@ModelAttribute` + `WebDataBinder` | `@RequestBody` + Jackson |
| `@InitBinder` applies | ✅ | ⚠️ only its validators (`addValidators`); editors/allowed fields don't touch JSON ([§W6.9](#w69-initbinder-q55-q56)) |
| DTO style | mutable bean (getters/setters) | ✅ **`record`** |
| Handle errors | `BindingResult` in the method | ✅ **`@RestControllerAdvice`**, once |
| Exception | `BindException` | `MethodArgumentNotValidException` |
| Result | re-render the form | 400 + `ProblemDetail` |

### W7.11 Comparison: Bean Validation vs Pydantic vs Zod [Q55]

> **Your question:** *"are these similar to zod in express or pydantic in python + fastapi?"*

**Conceptually identical — all three validate an incoming payload's shape before your business code runs.** The implementation philosophy is what differs:

| | **Jakarta Bean Validation** | **Pydantic** (FastAPI) | **Zod** (Express/TS) |
|---|---|---|---|
| Style | **declarative annotations** on fields | type hints + `Field()` | a fluent **schema object** |
| Where the rules live | **on the class** | **on the model** | in a **separate schema value** |
| Runs | via reflection, triggered by `@Valid` | automatically on model construction | explicitly: `schema.parse(x)` |
| Type coercion | separate concern (`Converter`) | ✅ built in and central | ✅ built in |
| Output type | the same class you annotated | the model | an **inferred** TS type |
| Cross-field | `@AssertTrue`, class-level constraint | `@model_validator` | `.refine()` / `.superRefine()` |
| Custom rule | `ConstraintValidator` class | `@field_validator` function | `.refine(fn, msg)` |
| Nested | `@Valid` to cascade (⚠️ opt-in!) | ✅ automatic | ✅ automatic |
| i18n | ✅ first-class via `MessageSource` | manual | manual |
| DI in validators | ✅ **validators are Spring beans** | ❌ awkward | ❌ closures only |

```java
// Java
public record User(@NotBlank @Size(max=50) String name, @Min(18) int age, @Email String email) {}
```
```python
# Pydantic
class User(BaseModel):
    name:  str = Field(min_length=1, max_length=50)
    age:   int = Field(ge=18)
    email: EmailStr
```
```typescript
// Zod
const User = z.object({
  name:  z.string().min(1).max(50),
  age:   z.number().int().gte(18),
  email: z.string().email(),
});
```

**The three differences that will actually bite you coming from Pydantic:**
1. ⚠️ **Nested validation is opt-in in Java.** Pydantic cascades automatically; Java needs an explicit inner `@Valid`. Forgetting it is the most common silent validation gap.
2. ⚠️ **Bean Validation does not coerce types.** Pydantic will happily turn `"25"` into `25`. In Spring, conversion is a *separate* stage (`ConversionService`) that runs *before* validation, and a failure there produces a `typeMismatch` error rather than a constraint violation.
3. ⚠️ **You must add the dependency.** Pydantic *is* FastAPI's request layer. In Spring, validation is an optional starter that fails **silently** when missing.

✅ **The one place Java is clearly ahead:** validators are **Spring beans**, so a constraint can inject a repository or a client. Doing the equivalent cleanly in Pydantic or Zod is genuinely awkward.

---


## W8. Writing responses: @ResponseBody, ResponseEntity, message converters, and global error handling

[§W4.10](#w410-invoke-then-java-object-to-json) showed the machinery that turns a return value into bytes. This chapter covers the decisions you make as an author: which annotation, which return type, and how errors become responses. It ends with the global, standard error format ([§W8.8](#w88-global-exception-handling-with-problemdetail-)).

### W8.1 `@Controller` vs `@RestController`: what "= `@Controller` + `@ResponseBody`" means

> **Your questions:** *"@RestController = @Component + @ResponseBody?"* · *"so only @ResponseBody differentiates @RestController and @Controller?"*

📌 **Correction:** it is **`@Controller` + `@ResponseBody`**, not `@Component` + `@ResponseBody`. This is the actual source of the annotation:
```java
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Controller          // ← which is itself meta-annotated with @Component
@ResponseBody
public @interface RestController { String value() default ""; }
```
The difference matters. `@Component` only makes the class a bean. `@Controller` is what makes `RequestMappingHandlerMapping` scan the class for `@GetMapping`/`@PostMapping` methods: its `isHandler(beanType)` check is literally "does this type carry `@Controller`?". A `@Component` class full of `@GetMapping` methods registers **no routes**.

⚠️ **Version note:** Spring Framework 5.3 (Boot 2.7) also treated a class with only a type-level `@RequestMapping` as a controller. **Framework 6.0 removed that.** From the 6.0 release notes: *"Spring MVC and Spring WebFlux no longer detect controllers based solely on a type-level `@RequestMapping` annotation."* Old `@Component @RequestMapping("/x")` classes silently lose their endpoints when migrated from Boot 2.7 to Boot 3/4.

**And yes, `@ResponseBody` is the only difference.** It changes what your **return value** means:

| | `@Controller` | `@RestController` |
|---|---|---|
| `return "orders";` | a **view name** → `ViewResolver` → render `orders.html` (Thymeleaf, [§W11](#w11-thymeleaf-and-server-side-rendering-q15-q16)) | the literal text `orders` written to the body |
| `return orderDto;` | ❌ Spring tries to resolve a view (usually an error) | `orderDto` → JSON via an `HttpMessageConverter` |
| Typical use | server-rendered HTML pages | JSON APIs |

You can mix the two styles: put `@ResponseBody` on individual methods of a `@Controller`, or return a `ResponseEntity` (which implies a body).

🐍🟨 `@Controller` + view name is Express's `res.render('orders', model)` / FastAPI's `TemplateResponse`. `@RestController` is `res.json(obj)` / FastAPI returning a dict.

### W8.2 `@RequestBody` vs `@ResponseBody`: input vs output

> **Your question:** *"and not @RequestBody?"* (i.e., why isn't `@RequestBody` part of `@RestController`?)

Because they work in **opposite directions** and at **different levels**:

| | `@RequestBody` | `@ResponseBody` |
|---|---|---|
| Direction | **in**: HTTP body → Java object | **out**: Java return value → HTTP body |
| Goes on | a **method parameter** | a **method** or a **class** |
| Handled by | `RequestResponseBodyMethodProcessor` as an argument resolver | the same class, as a return-value handler |
| Can be class-wide? | ❌ only *one* parameter of a method can be the body, and many methods have none (GETs) | ✅ "every method in this class returns data" is a sensible default |

A class-wide `@RequestBody` would make no sense: Spring couldn't know which parameter is the body, and a `GET /orders/{id}` has no body at all. So you still write `@RequestBody` per parameter, even in a `@RestController`:
```java
@RestController
class OrderController {
    @PostMapping("/orders")
    OrderDto create(@Valid @RequestBody CreateOrderRequest req) { … }   // @RequestBody: still needed
}
```
Forgetting it is the classic trap from [§W6.2](#w62-the-complete-where-does-this-value-come-from-table-q55): the POJO silently becomes `@ModelAttribute` and all fields are `null`.

### W8.3 `HttpMessageConverter` and Jackson: who actually writes the JSON

> **Your question:** *"what is HttpMessageConverter / how is jackson used?"*

`HttpMessageConverter<T>` is Spring's interface for "turn HTTP bytes into a Java object, and back". It has `canRead`/`read` and `canWrite`/`write`, plus a list of supported media types. Spring MVC keeps an ordered list of converters and asks each one in turn:

```
@RequestBody  : Content-Type header ──► first converter with canRead(type, mediaType)  ──► Java object
return value  : Accept header + produces ──► first converter with canWrite(type, mediaType) ──► bytes
```

| Converter (typical) | Handles |
|---|---|
| `ByteArrayHttpMessageConverter` | `byte[]` |
| `StringHttpMessageConverter` | `String` → `text/plain` (⚠️ so a `String` return from a `@RestController` is **not** JSON-quoted) |
| `ResourceHttpMessageConverter` | `Resource` (file downloads) |
| **Jackson JSON converter** | any object ↔ `application/json` |
| Jackson XML converter | only if `jackson-dataformat-xml` is on the classpath |

**Which Jackson? This is version-specific:**

| Stack | JSON converter | Mapper bean | Package |
|---|---|---|---|
| Boot 2.7 / Framework 5.3, Boot 3.x / Framework 6.x | `MappingJackson2HttpMessageConverter` | `ObjectMapper` | `com.fasterxml.jackson` (Jackson 2) |
| **Boot 4.x / Framework 7.x** | **`JacksonJsonHttpMessageConverter`** | **`JsonMapper`** (Jackson 3) | **`tools.jackson`** |

The Framework 7.0 release notes say: *"we default to supporting Jackson 3.x… falling back to Jackson 2.x"*. Jackson 2 support is deprecated; per those notes, auto-detection is to be disabled in 7.1 and the support removed in 7.2. Boot 4's JSON docs: *"Jackson 3 is the preferred and default library."* A Jackson 2 compatibility module (`spring-boot-jackson2`, `spring.jackson2.*` properties) exists for migration. Note that the Jackson **annotations** (`@JsonProperty`, `@JsonIgnore`) keep their `com.fasterxml.jackson.annotation` package in Jackson 3, so most DTOs compile unchanged.

**Customising** (Boot does the wiring for you):
- `spring.jackson.*` properties (naming strategy, null inclusion, dates; [§W4.8](#w48-json-to-java-object-where-jsonparse-really-lives));
- a customizer bean (`Jackson2ObjectMapperBuilderCustomizer` on Boot 2.7/3; `JsonMapperBuilderCustomizer` on Boot 4);
- `WebMvcConfigurer.configureMessageConverters(...)` only if you really need to replace the list.

To change **every** JSON response after the controller (wrap in an envelope, add a header), implement `ResponseBodyAdvice<Object>` in a `@ControllerAdvice`. It runs just before the converter writes, which is where `postHandle` is already too late ([§W5.2](#w52-the-exact-order-of-events)).

🐍 This is Pydantic's `model_validate_json` / `model_dump_json` that FastAPI calls for you. 🟨 It's `express.json()` + `res.json()`.

### W8.4 `produces` and `consumes`

> **Your question:** *"what is produces and consumes in the mapping?"*

They narrow **which requests a mapping accepts**, based on media-type headers:

| Attribute | Checks request header | Mismatch → | Also does |
|---|---|---|---|
| `consumes = "application/json"` | `Content-Type` (what the client **sends**) | **415** Unsupported Media Type | — |
| `produces = "application/json"` | `Accept` (what the client **wants back**) | **406** Not Acceptable | sets the response `Content-Type` |

```java
@PostMapping(path = "/orders",
             consumes = MediaType.APPLICATION_JSON_VALUE,
             produces = MediaType.APPLICATION_JSON_VALUE)
public OrderDto create(@RequestBody CreateOrderRequest req) { … }

// Same path, different representation: chosen by the Accept header
@GetMapping(path = "/reports/{id}", produces = "text/csv")
public String csv(@PathVariable long id) { … }
@GetMapping(path = "/reports/{id}", produces = MediaType.APPLICATION_JSON_VALUE)
public ReportDto json(@PathVariable long id) { … }
```
- Both accept a list and negation (`produces = {"application/json", "application/xml"}`, `consumes = "!text/plain"`).
- A method-level value **overrides** a class-level value (it does not merge).
- **Without them** Spring still works: it uses the `Content-Type` to choose a reader and the `Accept` header plus the available converters to choose a writer. They are for **documentation, routing between overloads, and early 415/406**.
- ⚠️ They are **not a security control**. A client can send any header; `consumes` only guarantees which converter parses the body.

🔗 The 404/405/415/406 decision table is in [§W4.7](#w47-dispatcherservletdodispatch-and-routing).

### W8.5 `ResponseEntity` vs plain return + `@ResponseStatus`

> **Your questions, merged:** *"what's the difference between ResponseEntity and @ResponseStatus?"* · *"when to use which?"* · *"can we use both together?"* · *"what about headers?"* · *"I didn't get it clearly, and how does error handling work in both?"*

**Analogy: a vending machine.** `@ResponseStatus` is the label printed on the machine: *"successful purchases always return 201"*. It is fixed at compile time and is the same for every call. `ResponseEntity` is a clerk who hands you an envelope and decides at runtime what goes on it: the status, any headers, and the body.

| | Plain return type + `@ResponseStatus` | `ResponseEntity<T>` |
|---|---|---|
| Status | **fixed**, declared once (default 200 without the annotation) | **chosen at runtime** (`ok()`, `created(uri)`, `notFound()`, `status(…)`) |
| Headers | ❌ not from the return value (you'd have to inject `HttpServletResponse`) | ✅ `.header()`, `.eTag()`, `.location()`, `.cacheControl()` |
| Body | the returned object | `.body(obj)`, or `.build()` for none |
| Readability / testability | ✅ cleanest; the method returns domain data | more verbose; the method mentions HTTP |
| Typical use | 95% of CRUD endpoints | `201` + `Location`, conditional `304`, downloads with `Content-Disposition`, "200 or 204 depending on data" |

```java
// Fixed status → @ResponseStatus
@PostMapping @ResponseStatus(HttpStatus.CREATED)
public OrderDto create(@Valid @RequestBody CreateOrderRequest r) { return service.create(r); }

// Status/headers decided at runtime → ResponseEntity
@GetMapping("/{id}/invoice")
public ResponseEntity<byte[]> invoice(@PathVariable String id) {
    byte[] pdf = service.invoicePdf(id);
    return ResponseEntity.ok()
            .contentType(MediaType.APPLICATION_PDF)
            .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + id + ".pdf\"")
            .body(pdf);
}
```

**Can you combine them?** On the same method, the `ResponseEntity`'s status wins, so the combination is pointless and misleading; don't do it. **`@ResponseStatus` has a second, separate use**: on an **exception class**, where it means "if this exception escapes, respond with this status" ([§W8.6](#w86-error-handling-in-both-styles)).

⚠️ `@ResponseStatus(code = …, reason = "…")` with a **`reason`** makes Spring call `response.sendError(...)`. That produces the container's error page, not your return value, so don't put `reason` on a success handler.

🔗 The `ResponseEntity` builder examples are also in [§W4.12](#w412-the-complete-annotation-reference).

### W8.6 Error handling in both styles

The rule that clears up the confusion: **don't encode errors in your return value. Throw an exception, and map exceptions to responses in one place.** Both styles then handle errors identically:

```
controller (either style) ──throws OrderNotFoundException──►
   DispatcherServlet catches it ──► HandlerExceptionResolvers, in order:
      1. ExceptionHandlerExceptionResolver  → your @ExceptionHandler (local, then @ControllerAdvice)
      2. ResponseStatusExceptionResolver    → @ResponseStatus on the exception class, ResponseStatusException
      3. DefaultHandlerExceptionResolver    → Spring's own exceptions (405, 415, 400…)
   nothing matched ──► container → Boot's /error (BasicErrorController) → 500
```

| Way to produce an error response | Example | When |
|---|---|---|
| `@ResponseStatus` on the exception class | `@ResponseStatus(NOT_FOUND) class OrderNotFoundException` | simplest; status only, default body |
| `throw new ResponseStatusException(...)` | `throw new ResponseStatusException(NOT_FOUND, "no order")` | one-off; no custom class |
| `@ExceptionHandler` returning `ProblemDetail` / `ResponseEntity` | [§W8.8](#w88-global-exception-handling-with-problemdetail-) | ✅ production: one consistent JSON error format |
| `return ResponseEntity.notFound().build()` | inside the controller | only when "not found" is a **normal outcome** of this endpoint, not an error |

❌ **Anti-pattern**: catching exceptions in every controller and returning `ResponseEntity.status(500).body(e.getMessage())`. It duplicates logic, leaks internal messages, and bypasses `@ControllerAdvice`.

### W8.7 `@ControllerAdvice` vs `@RestControllerAdvice`

> **Your question:** *"difference between @ControllerAdvice and @RestControllerAdvice?"*

The same relationship as [§W8.1](#w81-controller-vs-restcontroller-what--controller--responsebody-means): `@RestControllerAdvice` = **`@ControllerAdvice` + `@ResponseBody`**. The return values of its `@ExceptionHandler` methods are written to the body by a message converter instead of being treated as view names.

| | `@ControllerAdvice` | `@RestControllerAdvice` |
|---|---|---|
| Handler returns a POJO / `ProblemDetail` | treated as a **view** unless the method has `@ResponseBody` | serialised to JSON ✅ |
| Handler returns `ResponseEntity` | ✅ written as the body; no `@ResponseBody` needed | ✅ |
| Handler returns `"error/404"` (String) | ✅ renders the error page (MVC apps) | writes the text `error/404` |

What an advice class can contain (it applies to all controllers, or the ones you scope it to):
- `@ExceptionHandler` methods (global error mapping);
- `@InitBinder` methods (global binder setup, [§W6.9](#w69-initbinder-q55-q56));
- `@ModelAttribute` methods (add attributes to every model);
- it can also implement `ResponseBodyAdvice` / `RequestBodyAdvice`.

```java
@RestControllerAdvice(basePackages = "com.example.api")      // scope: only these controllers
// also: assignableTypes = {OrderController.class}, annotations = RestController.class
class ApiErrors { … }
```

📌 **Not AOP.** Despite the name "advice", there is no proxy. At startup `ExceptionHandlerExceptionResolver` collects `@ControllerAdvice` beans, and the `DispatcherServlet` consults it when a handler throws. So it catches exceptions from controllers, interceptors and argument resolution, but **not from filters** (those run outside the `DispatcherServlet`, [§W5.1](#w51-the-two-layers-in-one-picture)), and not from `@Async`/scheduled code.

**Order of precedence:** an `@ExceptionHandler` inside the controller beats any advice. Among several advice beans, use `@Order`. Within one class, the most specific exception type wins.

### W8.8 Global exception handling with `ProblemDetail` [+]

Instead of `try`/`catch` in every controller, handle exceptions **once**. Spring 6 / Boot 3 ship **`ProblemDetail`**, an implementation of **RFC 9457** (formerly RFC 7807) — the standard "problem details for HTTP APIs" format.

```java
@RestControllerAdvice                              // = @ControllerAdvice + @ResponseBody
@RequiredArgsConstructor
@Slf4j
public class GlobalExceptionHandler {

    private final MessageSource messageSource;

    @ExceptionHandler(OrderNotFoundException.class)
    public ProblemDetail onNotFound(OrderNotFoundException e) {
        ProblemDetail pd = ProblemDetail.forStatusAndDetail(HttpStatus.NOT_FOUND, e.getMessage());
        pd.setTitle("Order not found");
        pd.setType(URI.create("https://api.example.com/errors/order-not-found"));
        pd.setProperty("orderId", e.orderId());
        return pd;
    }

    @ExceptionHandler(MethodArgumentNotValidException.class)   // @Valid on @RequestBody — see W7.5
    public ProblemDetail onInvalid(MethodArgumentNotValidException e, Locale locale) {
        Map<String, String> errors = new LinkedHashMap<>();
        for (FieldError fe : e.getBindingResult().getFieldErrors()) {
            errors.put(fe.getField(), messageSource.getMessage(fe, locale));   // see W7.8
        }
        ProblemDetail pd = ProblemDetail.forStatus(HttpStatus.BAD_REQUEST);
        pd.setTitle("Validation failed");
        pd.setProperty("errors", errors);
        return pd;
    }

    @ExceptionHandler(AccessDeniedException.class)
    public ProblemDetail onDenied(AccessDeniedException e) {
        return ProblemDetail.forStatusAndDetail(HttpStatus.FORBIDDEN, "You may not perform this action");
    }

    @ExceptionHandler(Exception.class)                        // ⚠️ the catch-all, LAST
    public ProblemDetail onUnexpected(Exception e) {
        String ref = UUID.randomUUID().toString();
        log.error("Unhandled exception ref={}", ref, e);       // full stack trace to the LOG
        ProblemDetail pd = ProblemDetail.forStatusAndDetail(
                HttpStatus.INTERNAL_SERVER_ERROR, "An unexpected error occurred");  // NOT to the client
        pd.setProperty("reference", ref);                      // the user can quote this in a ticket
        return pd;
    }
}
```
```json
Content-Type: application/problem+json

{ "type": "https://api.example.com/errors/order-not-found",
  "title": "Order not found", "status": 404,
  "detail": "No order with id ord-42", "instance": "/api/v1/orders/ord-42",
  "orderId": "ord-42" }
```

⚠️ **`@ExceptionHandler(AccessDeniedException.class)` has a side effect with Spring Security.** Method-security denials (`@PreAuthorize`) are thrown inside the `DispatcherServlet`, so this advice catches them **before** Security's `ExceptionTranslationFilter` sees them. An **anonymous** user then gets your 403 instead of Security's 401 / login redirect. Either rethrow it, check whether the user is authenticated, or leave it to Spring Security ([§S4](05-spring-security.md#s4-authorization-what-are-you-allowed-to-do)).

⚠️ **The `Exception.class` catch-all also swallows Spring MVC's own exceptions** (405, 415, missing parameter, `HandlerMethodValidationException`…) and turns them into 500s, because without other handlers it is the best match. Extend `ResponseEntityExceptionHandler` (see below) so those keep their proper 4xx status.

⚠️ **Never leak a stack trace or an internal message to a client.** It reveals class names, framework versions, and sometimes SQL. Log the detail with a correlation reference; return the reference.

💡 **Resolution rules worth knowing:** Spring picks the **most specific** matching `@ExceptionHandler` by exception hierarchy, so `@ExceptionHandler(Exception.class)` is a safe catch-all. Extend **`ResponseEntityExceptionHandler`** to also customise the built-in Spring MVC exceptions from [§W4.11](#w411-the-exception-path). And for the simplest cases you can skip the advice entirely:
```java
@ResponseStatus(HttpStatus.NOT_FOUND)              // on the exception class itself
public class OrderNotFoundException extends RuntimeException { ... }

throw new ResponseStatusException(HttpStatus.NOT_FOUND, "No such order");   // or inline
```

🐍 This is FastAPI's `@app.exception_handler(...)` and Express's `app.use((err, req, res, next) => ...)` — with the difference that Java's is **type-dispatched** rather than a single function switching on the error.


## W9. CORS: @CrossOrigin, CorsFilter, and Spring Security

> **Your questions, merged:** *"what is CORS and how do we handle it in spring boot?"* · *"how does @CrossOrigin work behind the scenes?"* · *"is CORS handled in the filter chain or in the interceptor?"* · *"if both global config and @CrossOrigin are present, which one wins?"* · *"if Spring Security is configured with cors(), do we still need @CrossOrigin / the MVC config?"* · *"why is allowCredentials needed, and why permitAll on OPTIONS?"*

The source answers to these questions **contradicted each other** (one said "CORS runs in an interceptor", a later one said "CORS is done in the filter chain, not the interceptor"; one said "the more specific config wins"). This chapter gives the version checked against the Spring docs and source. 🔗 For the security side (CSRF next to CORS) see [§S6](05-spring-security.md#s6-csrf-and-cors).

### W9.1 CORS in 60 seconds

**CORS is enforced by the browser, not by your server.** A page served from `https://app.example.com` that calls `https://api.example.com` with `fetch` is making a **cross-origin** request (origin = scheme + host + port). The browser lets the JavaScript read the response only if the server's response says that origin is allowed. Your server just adds headers. `curl`, Postman and server-to-server calls ignore CORS completely.

```
Browser (page from https://app.example.com)                  API (https://api.example.com)
  │ ① "non-simple" request? (PUT/DELETE, JSON body, Authorization header…)
  │──── OPTIONS /orders  (the PREFLIGHT) ─────────────────────────────►│
  │     Origin: https://app.example.com                                 │
  │     Access-Control-Request-Method: POST                             │
  │     Access-Control-Request-Headers: content-type, authorization    │
  │◄─── 200  Access-Control-Allow-Origin: https://app.example.com ─────│
  │          Access-Control-Allow-Methods: GET,POST                     │
  │          Access-Control-Allow-Headers: content-type, authorization  │
  │          Access-Control-Max-Age: 1800                               │
  │ ② the ACTUAL request                                                │
  │──── POST /orders  Origin: https://app.example.com ────────────────►│
  │◄─── 201  Access-Control-Allow-Origin: https://app.example.com ─────│
  │ ③ JS may read the response only if the Allow-Origin header matches
```
- A **simple** request (GET/HEAD/POST with only "safe" headers and a form/text content type) skips step ①. It still needs `Access-Control-Allow-Origin` on the response.
- The preflight carries **no cookies or credentials**. That one fact explains most of the Spring Security behaviour in [§W9.5](#w95-spring-security-and-cors).

🐍 FastAPI: `app.add_middleware(CORSMiddleware, allow_origins=[...])`. 🟨 Express: `app.use(cors({ origin: [...] }))`. Both are middleware, i.e. "filter-level".

### W9.2 The four ways to configure CORS in Spring, and where each runs

| Option | Where it runs | Scope |
|---|---|---|
| `@CrossOrigin` on a controller/method | **Spring MVC**: the `HandlerMapping` adds CORS processing to the handler chain | that controller/method |
| `WebMvcConfigurer.addCorsMappings(...)` (global MVC config) | **Spring MVC**, same mechanism | URL patterns |
| a `CorsFilter` bean (`org.springframework.web.filter.CorsFilter`) | **Servlet filter chain**, before the `DispatcherServlet` | URL patterns in a `UrlBasedCorsConfigurationSource` |
| Spring Security `http.cors(...)` | Security's own `CorsFilter`, early in the **security filter chain** | whatever `CorsConfigurationSource` it finds ([§W9.5](#w95-spring-security-and-cors)) |

So the answer to "filter chain or interceptor?" is: **it depends on which option you use**. The first two are MVC-level; the last two are filter-level.

```java
// Option 1: per controller
@CrossOrigin(origins = "https://app.example.com", maxAge = 3600)
@RestController
class OrderController { … }

// Option 2: global MVC config
@Configuration
class WebConfig implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/api/**")
                .allowedOrigins("https://app.example.com")
                .allowedMethods("GET", "POST", "PUT", "DELETE")
                .allowedHeaders("Content-Type", "Authorization")
                .maxAge(3600);
    }
}
```
**`@CrossOrigin` defaults** (verified in the Framework reference): all origins, all headers, the HTTP methods the method is mapped to, `maxAge` 30 minutes. `allowCredentials` is **off** by default.

### W9.3 How `@CrossOrigin` works behind the scenes

1. **Startup:** while `RequestMappingHandlerMapping` registers each handler method, it also reads `@CrossOrigin` from the class and the method, and stores a `CorsConfiguration` next to the `HandlerMethod`.
2. **Request time:** in `AbstractHandlerMapping.getHandler(...)`, after finding the handler, Spring checks whether the request is a CORS request (it has an `Origin` header that differs from the server's). If so, it merges the global and handler-level configs ([§W9.4](#w94-global--local-combined-not-most-specific-wins)) and calls `getCorsHandlerExecutionChain(...)`:

```java
// AbstractHandlerMapping — simplified from the real source (Framework 6.x/7.x)
if (CorsUtils.isPreFlightRequest(request)) {
    // preflight: your controller is NOT called. A built-in handler answers the OPTIONS.
    PreFlightHttpRequestHandler handler = new PreFlightHttpRequestHandler(config);
    chain = new HandlerExecutionChain(handler, interceptors);
    chain.addInterceptor(0, handler);
} else {
    // actual request: a CorsInterceptor is put FIRST in the interceptor list
    chain.addInterceptor(0, new CorsInterceptor(config));
}
```
3. The `CorsInterceptor`'s `preHandle` runs `DefaultCorsProcessor`: it checks the origin/method/headers, adds the `Access-Control-Allow-*` headers, or rejects with **403** ("Invalid CORS request").

The Framework reference says the same thing in words: *"Preflight requests are handled directly, while simple and actual CORS requests are intercepted, validated, and have required CORS response headers set."*

📌 So with `@CrossOrigin` or `addCorsMappings`, CORS **does** run as an (internal) interceptor inside the `DispatcherServlet`. The later claim "CORS always happens in the filter chain" is only true for a `CorsFilter` or Spring Security.

### W9.4 Global + local: combined, not "most specific wins"

When a global mapping and `@CrossOrigin` both apply, Spring **combines** them with `CorsConfiguration.combine(...)`. From the Framework reference: *"The rules for combining global and local configuration are generally additive — for example, all global and all local origins. For those attributes where only a single value can be accepted, for example, `allowCredentials` and `maxAge`, the local overrides the global value."*

| Property | Global | `@CrossOrigin` | Result |
|---|---|---|---|
| origins | `https://a.com` | `https://b.com` | **both** `a.com` and `b.com` |
| methods | `GET, POST` | `*` | `*` (the `combine` javadoc: a `*` on either side wins) |
| `maxAge` | 3600 | 600 | **600** (local overrides) |
| `allowCredentials` | `false` | `true` | **true** (local overrides) |

**Correction to the source answer:** "the method-level `@CrossOrigin` replaces the global config" is wrong for list properties. You can't use `@CrossOrigin` to *narrow* a broad global origin list.

### W9.5 Spring Security and CORS

The Spring Security reference explains why order matters: *"CORS must be processed before Spring Security, because the pre-flight request does not contain any cookies (that is, the `JSESSIONID`)."* If security ran first, the preflight would be rejected as unauthenticated (401), and the browser would block the real request even though your `@CrossOrigin` is correct, because the MVC-level CORS code never gets a chance to run.

So with Security you enable CORS **in the security chain**:
```java
@Bean
SecurityFilterChain api(HttpSecurity http) throws Exception {
    http.cors(Customizer.withDefaults())          // Security adds its CorsFilter early
        .authorizeHttpRequests(a -> a.anyRequest().authenticated());
    return http.build();
}

@Bean
UrlBasedCorsConfigurationSource corsConfigurationSource() {
    CorsConfiguration c = new CorsConfiguration();
    c.setAllowedOrigins(List.of("https://app.example.com"));
    c.setAllowedMethods(List.of("GET", "POST", "PUT", "DELETE"));
    c.setAllowedHeaders(List.of("Content-Type", "Authorization"));
    UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
    source.registerCorsConfiguration("/api/**", c);
    return source;
}
```

**Where does `.cors(withDefaults())` get its configuration?** (verified against the Security reference):

| Your app has… | Security uses… |
|---|---|
| exactly one `UrlBasedCorsConfigurationSource` bean | that bean. It does **not** read `@CrossOrigin`; only the URL patterns registered in it count |
| no such bean, and Spring MVC is present | **Spring MVC's own CORS config**, which includes `@CrossOrigin` and `addCorsMappings`. Docs: *"If you use Spring MVC's CORS support, you can omit specifying the `CorsConfigurationSource` and Spring Security uses the CORS configuration provided to Spring MVC."* |
| more than one `CorsConfigurationSource` bean | no automatic configuration; pass one explicitly: `.cors(c -> c.configurationSource(mySource))` |

**Correction to the source answer:** it said the `corsConfigurationSource` bean "bridges" to `@CrossOrigin`. It doesn't. The bridge to MVC's config only happens when you **don't** declare your own source. Internally, Security 5.x/6.x looked up the MVC config through `HandlerMappingIntrospector`. Framework 7.0 deprecates that SPI. ✅ **Verified in source (`CorsConfigurer`, Security 7.0.8 and 7.1.2; Boot 4.1.1 ships Security 7.1.1).** With `.cors(withDefaults())`, Security picks the first match:
1. a source you passed with `.cors(c -> c.configurationSource(...))`;
2. a bean named `corsFilter`;
3. a bean named `corsConfigurationSource`;
4. Spring MVC's `mvcHandlerMappingIntrospector` bean. This `HandlerMappingIntrospector` implements `CorsConfigurationSource`, and it is what reads `@CrossOrigin` and your `WebMvcConfigurer.addCorsMappings`.

So **Security 7 still uses `HandlerMappingIntrospector` by default**, even though Framework 7.0 marks it `@Deprecated(since = "7.0", forRemoval = true)`. Framework 7's `WebMvcConfigurationSupport` still registers the bean.

In **Security 7.1** there is a fifth option, used only when none of the above is found or when you set it explicitly with `.cors(c -> c.preFlightRequestHandler(...))`. Security then registers a `PreFlightRequestFilter` instead of `CorsFilter`. That filter answers preflights only, and the actual request's CORS headers are left to MVC. Security 7.0 has no such option: it throws `NoSuchBeanDefinitionException` instead.

**So do you still need `@CrossOrigin`?**

| Setup | Do this |
|---|---|
| No Spring Security | `@CrossOrigin` or `addCorsMappings` is enough |
| Spring Security + `UrlBasedCorsConfigurationSource` bean | define CORS **only** in that bean. `@CrossOrigin` is then mostly redundant: the security `CorsFilter` already answered the preflight and added headers (it would still run for actual requests and combine, which is confusing) |
| Spring Security, no source bean, `.cors(withDefaults())` | keep `@CrossOrigin` / `addCorsMappings`; Security reuses them |

⚠️ `.cors(CorsConfigurer::disable)` removes Spring Security's CORS support. The Security docs: *"you are not removing CORS protection from your browser… users will not be able to interact with your Spring backend from a cross-origin browser application."*

### W9.6 `allowCredentials`, `OPTIONS` `permitAll`, and other pitfalls

**`allowCredentials(true)`** sends `Access-Control-Allow-Credentials: true`. It is needed when the browser should send **cookies** (a session cookie, an HttpOnly refresh-token cookie) or HTTP auth with `fetch(..., { credentials: 'include' })`.
- It is **not** needed for a JWT that your JavaScript puts in the `Authorization` header itself. That case needs `Authorization` in `allowedHeaders` (and triggers a preflight).
- ⚠️ With credentials on, the spec forbids `Access-Control-Allow-Origin: *`. Spring rejects `allowedOrigins("*")` + `allowCredentials(true)` with an `IllegalArgumentException`. List explicit origins, or use `allowedOriginPatterns("https://*.example.com")`.

**`requestMatchers(HttpMethod.OPTIONS, "/**").permitAll()`** is a common snippet. With `.cors()` enabled it is **redundant**: Security's `CorsFilter` answers preflights before the authorization filter. It's harmless, but don't rely on it *instead of* `.cors()`, because then no CORS headers are added.

**Other gotchas:**
- ⚠️ **Error responses need CORS headers too.** If a filter returns 401/500 before CORS is processed, the browser shows a misleading "CORS error" instead of the real status. Putting CORS in the filter chain first (Security's `.cors()`) avoids this.
- Origins must match **exactly**: `https://app.example.com` ≠ `https://app.example.com/` ≠ `http://…` ≠ `…:3000`.
- Keep allowed origins in configuration (`app.cors.allowed-origins` per profile), not hard-coded.
- CORS is **not** an API security mechanism. It stops other *websites* from reading responses in a *browser*; it does nothing against `curl`. Authentication is still required ([§S2](05-spring-security.md#s2-authentication-who-are-you)).


## W10. Request-scoped context: RequestContextHolder and LocaleContextHolder

> **Your questions, merged:** *"what is RequestContextHolder and LocaleContextHolder? is it similar to contextvar in python?"* · *"what happens to them if I start a new thread / use a thread pool / virtual threads?"*

Both holders are **static access points to per-request data, backed by a `ThreadLocal`**. The `ThreadLocal` mechanics (what it is, why pools leak it, `InheritableThreadLocal`, `ScopedValue`) are explained in [§J6](01-java.md#j6-concurrency-and-multithreading-q2q9). This chapter covers the two Spring holders built on it.

### W10.1 What they hold, and who fills them

| | `RequestContextHolder` | `LocaleContextHolder` |
|---|---|---|
| Package | `org.springframework.web.context.request` | `org.springframework.context.i18n` (core, not web-only) |
| Holds | `RequestAttributes` (in a servlet app a `ServletRequestAttributes`, wrapping the `HttpServletRequest`/`HttpServletResponse`) | `LocaleContext`: the request's `Locale` (+ `TimeZone`) |
| Filled by | `FrameworkServlet.processRequest` (`DispatcherServlet`'s parent class), and earlier by Boot's `OrderedRequestContextFilter` | `FrameworkServlet` too, from the `LocaleResolver` (the `Accept-Language` header by default) |
| Cleared | in a `finally` at the end of the request | same |
| Typical reader | code with no access to the request, e.g. a `@Service` that needs a header; request/session-**scoped beans** use it internally | `MessageSource` lookups, formatting/validation messages ([§W7.8](#w78-custom-error-messages-q55)) |
| Outside a request | `getRequestAttributes()` → `null`; `currentRequestAttributes()` throws `IllegalStateException` | returns the JVM default `Locale` |

```java
// Anywhere on the request thread
HttpServletRequest req = ((ServletRequestAttributes) RequestContextHolder.currentRequestAttributes()).getRequest();
String tenant = req.getHeader("X-Tenant-Id");

Locale locale = LocaleContextHolder.getLocale();      // e.g. de_DE from Accept-Language
String msg = messageSource.getMessage("order.notFound", null, locale);
```

🐍 **Similar to Python's `contextvars.ContextVar`?** In purpose, yes: both give "ambient" per-request data without passing it through every call. Mechanically they differ:
- A `ContextVar` follows the **async task** (asyncio copies the context into each task).
- A `ThreadLocal` follows the **OS/JVM thread**. It works in Spring MVC because there is **one thread per request** ([§W1.5](#w15-one-servlet-many-threads--the-concurrency-model-q44)).
- Java's closest equivalent to a `ContextVar` is `ScopedValue` (final in JDK 25) ([§J6](01-java.md#j6-concurrency-and-multithreading-q2q9)).
- 🟨 In Node the equivalent is `AsyncLocalStorage`.

💡 **Prefer method parameters when you can.** A controller can just declare `Locale locale`, `HttpServletRequest req`, or `@RequestHeader("X-Tenant-Id") String tenant` ([§W4.8](#w48-json-to-java-object-where-jsonparse-really-lives) resolver table) and pass the value to the service. Code that reaches into a static holder is harder to test and silently breaks off the request thread.

### W10.2 New threads, pools and virtual threads

The holder is tied to the **request thread**. Any work that hops threads loses it unless you carry it over:

| Where the code runs | What it sees |
|---|---|
| request thread (controller, service, interceptor) | ✅ the request's attributes and locale |
| `new Thread(...)` / `CompletableFuture.supplyAsync(...)` / `@Async` / a pool thread | ❌ `null` (or **another request's** stale value, if someone forgot to clear a pooled thread) |
| a child thread, **if** the attributes were set as inheritable | ⚠️ a copy of the *reference*. See the warning below |

**Ways to make it visible (version-tagged):**
- **Inheritable flag:** `RequestContextHolder.setRequestAttributes(attrs, true)`, or `DispatcherServlet.setThreadContextInheritable(true)` (`spring.mvc` has no property for it; you set it on the servlet). This uses an `InheritableThreadLocal`. It only helps for threads *created* during the request, so it is useless with a pool whose threads already exist. The Spring javadoc discourages it for pooled threads.
- **`TaskDecorator` (recommended for pools):** capture the value on the submitting thread and set/clear it around the task:
```java
@Bean
TaskDecorator requestContextDecorator() {
    return task -> {
        RequestAttributes attrs = RequestContextHolder.getRequestAttributes();   // captured on request thread
        Locale locale = LocaleContextHolder.getLocale();
        return () -> {
            try {
                RequestContextHolder.setRequestAttributes(attrs);
                LocaleContextHolder.setLocale(locale);
                task.run();
            } finally {
                RequestContextHolder.resetRequestAttributes();             // ⚠️ always clean up
                LocaleContextHolder.resetLocaleContext();
            }
        };
    };
}
```
  Boot applies a single `TaskDecorator` bean to its auto-configured `@Async`/`ThreadPoolTaskExecutor`. **Framework 6.1+** also ships `ContextPropagatingTaskDecorator`, which propagates every registered `ThreadLocalAccessor` (MDC, tracing, Security context) via Micrometer's context-propagation library.
- **Virtual threads** (Boot 3.2+ with `spring.threads.virtual.enabled=true`): virtual threads **do** inherit `InheritableThreadLocal`s by default, and Boot's virtual-thread executor (`SimpleAsyncTaskExecutor`) creates a fresh thread per task instead of pooling. But plain `ThreadLocal`s (what the holders use by default) are still not copied, so you still need the decorator.

⚠️ **The real danger: using the request after it has finished.** Even if you propagate `RequestAttributes` to another thread, once the request completes the attributes are marked inactive (*"request is not active anymore"*), and Tomcat **recycles** `HttpServletRequest` objects for the next request. A background task that calls `request.getHeader(...)` a few seconds later can read **another user's** data or throw. **Copy the values you need (`String tenant = …`) before handing work off**, and pass those values, not the request.

🔗 `@Async` and executor configuration: [§P3](06-spring-production.md#p3-background-work-scheduled-and-async). The same propagation problem for the Security context (`SecurityContextHolder`, also a `ThreadLocal`): [§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext).

## W11. Thymeleaf and server-side rendering [Q15, Q16]

### W11.1 What Thymeleaf is, and the EJS comparison [Q15]

> **Your question:** *"what is thymeleaf in spring boot and is this similar to ejs in express to generate the server html?"*

**Yes.** Thymeleaf is a server-side Java template engine that dynamically generates and renders HTML on the server. Conceptually it is highly similar to **EJS** in Express: both act as the **View** layer in MVC, combining a static layout with backend data before sending the finished page to the browser.

They reach that goal through **completely different design philosophies**:

| Feature | **Thymeleaf** (Spring Boot) | **EJS** (Express.js) |
|---|---|---|
| Language ecosystem | Java | JavaScript / Node.js |
| Template syntax | **Natural HTML attributes** (`th:text`) | **Scriptlet tags** (`<%= data %>`) |
| Design paradigm | **Natural Templating** — the file stays valid HTML that a browser can open directly, with no server running | **Code injection** — the file relies on broken HTML containing JavaScript blocks, which breaks native browser rendering |
| Integration | Tight, first-class binding with Spring MVC, Spring Security and Spring beans | Simple object data injection passed explicitly from Express routes |

#### Syntax comparison

**1. Displaying a variable**
```html
<!-- EJS: injects JavaScript into the HTML using tag delimiters -->
<h1>Welcome, <%= username %>!</h1>
```
```html
<!-- Thymeleaf: a custom HTML5 attribute. Opened directly in a browser it
     safely falls back to displaying the placeholder text ("Guest"). -->
<h1 th:text="${username}">Welcome, Guest!</h1>
```

**2. Looping through a list**
```html
<!-- EJS: functional JavaScript control loops across broken HTML blocks -->
<ul>
  <% items.forEach(function(item) { %>
    <li><%= item.name %></li>
  <% }); %>
</ul>
```
```html
<!-- Thymeleaf: the HTML tag structure stays entirely intact -->
<ul>
  <li th:each="item : ${items}" th:text="${item.name}">Item Placeholder</li>
</ul>
```

💡 **"Natural templating" is the whole point of the design.** Because `th:*` are just HTML5 attributes and the tag body holds realistic placeholder content, a designer can open `registration-form.html` by double-clicking it and see a styled, sensible page — no JVM, no Maven, no running application. With EJS or JSP, the raw file renders as garbage. That's why Spring Boot favours Thymeleaf over the older **JSP** it replaced.

⚠️ Nit on the snippets above and in [§W7.9](#w79-end-to-end-worked-example-q55): the canonical namespace is `xmlns:th="http://www.thymeleaf.org"` (with `www.`). It's purely a hint for IDE autocompletion and XML validators — Thymeleaf itself ignores it — so the `www`-less form still works, but use the canonical one.

### W11.2 Do you create the HTML file yourself? [Q16]

> **Your question:** *"we have to return the file name like `helloworld` and springboot will automatically create a file… or we need to manually create this `helloworld.html` file inside the template directory manually? i think it should because without that how will it know what content to render for that file?"*

**Your reasoning is 100% correct.** You create the file. Spring Boot cannot guess your layout, styling or markup.

**What you do manually:**
1. Create `helloworld.html` inside `src/main/resources/templates/`.
2. Write the HTML and `th:*` attributes in it.
3. Write a controller that returns the `String` `"helloworld"`.

**What Spring Boot automates:** the **View Resolver**. In Express you explicitly write `res.render('pages/helloworld.ejs')` and configure path joins yourself. In Spring Boot, adding the Thymeleaf dependency auto-configures the prefix and suffix:

```
spring.thymeleaf.prefix = classpath:/templates/      ← automatic
spring.thymeleaf.suffix = .html                      ← automatic

return "helloworld"  →  classpath:/templates/ + helloworld + .html
```

```java
@Controller                                   // ⚠️ @Controller, NOT @RestController
public class MyController {
    @GetMapping("/hello")
    public String sayHello(Model model) {
        model.addAttribute("message", "Hello World from Spring Boot!");
        return "helloworld";                  // ← a VIEW NAME, not a response body
    }
}
```
```html
<!-- src/main/resources/templates/helloworld.html — created BY YOU -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head><title>Hello Page</title></head>
<body>
    <!-- Thymeleaf replaces this text with the data from the controller -->
    <h1 th:text="${message}">Placeholder Text</h1>
</body>
</html>
```

⚠️ **The single most common beginner mistake here:** using `@RestController` instead of `@Controller`. With `@RestController`, `@ResponseBody` is implied, so Spring writes the literal string `helloworld` to the response body as `text/plain`. You see the word "helloworld" in your browser instead of a page. ([§W4.10](#w410-invoke-then-java-object-to-json))

**The resolution chain, concretely** — this is the `ViewResolver` step of [§W3.3](#w33-end-to-end-requestresponse--the-classic-view-rendering-flow-q50-q52):
```
controller returns "helloworld"
   → ViewNameMethodReturnValueHandler puts it in the ModelAndView
   → DispatcherServlet.resolveViewName()
   → ThymeleafViewResolver: "classpath:/templates/" + "helloworld" + ".html"
   → template found → SpringTemplateEngine.process(template, context)
   → the Model's attributes become template variables
   → rendered HTML written to the response
   → 404 / TemplateInputException if the file doesn't exist
```

**The dependency:**
```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

### W11.3 [+] The five expression types — the cheatsheet that matters

This is the part tutorials bury, and it's the thing you'll look up constantly:

| Syntax | Name | Purpose | Example |
|---|---|---|---|
| `${...}` | **Variable** | read a model attribute (SpEL) | `th:text="${user.name}"` |
| `*{...}` | **Selection** | read a property of the current `th:object` | `th:field="*{username}"` |
| `#{...}` | **Message** | i18n from `messages.properties` | `th:text="#{login.title}"` |
| `@{...}` | **Link/URL** | context-aware URL — prepends the context path | `th:href="@{/css/app.css}"` |
| `~{...}` | **Fragment** | reference a reusable fragment | `th:replace="~{layout :: header}"` |

```html
<!-- @{...} builds URLs with path variables and query params -->
<a th:href="@{/users/{id}/edit(id=${user.id}, tab='profile')}">Edit</a>
<!--                                → /app-context/users/5/edit?tab=profile -->
```
💡 **Always use `@{...}` for URLs, never a hardcoded `/css/app.css`.** It's the only form that survives the app being deployed under a non-root context path.

**The attributes you'll use 95% of the time:**

| Attribute | Does |
|---|---|
| `th:text` | sets the escaped text content |
| ⚠️ `th:utext` | **unescaped** — renders raw HTML. **This is an XSS hole** unless the value is sanitised. |
| `th:each="i : ${list}"` | loop. `th:each="i, stat : ${list}"` gives `stat.index`, `stat.count`, `stat.first`, `stat.last`, `stat.odd` |
| `th:if` / `th:unless` | conditional rendering (removes the element entirely) |
| `th:switch` / `th:case` | multi-branch |
| `th:object` + `th:field` | form binding ([§W7.9](#w79-end-to-end-worked-example-q55)) |
| `th:href` / `th:src` / `th:action` | URLs |
| `th:attr` / `th:classappend` | arbitrary / appended attributes |
| `th:fragment` / `th:replace` / `th:insert` | layout composition |
| `th:with` | a local variable |
| `<th:block>` | an invisible wrapper element, for looping without extra markup |

💡 **`th:text` escapes by default** — `<script>` becomes `&lt;script&gt;`. This is the opposite of EJS, where `<%= %>` escapes but `<%- %>` doesn't, and you have to remember which. Thymeleaf's default is the safe one.

**Fragments = EJS partials / Jinja `{% include %}`:**
```html
<!-- templates/fragments/layout.html -->
<nav th:fragment="navbar(active)">
  <a th:href="@{/}" th:classappend="${active=='home'} ? 'selected'">Home</a>
</nav>
```
```html
<!-- any page -->
<div th:replace="~{fragments/layout :: navbar('home')}"></div>
```
| | Does |
|---|---|
| `th:insert` | inserts the fragment **inside** the host tag |
| `th:replace` | **replaces** the host tag with the fragment ✅ usually what you want |

### W11.4 [+] Configuration and production gotchas

```properties
spring.thymeleaf.cache=false      # ⚠️ DEV ONLY — otherwise you must restart to see edits
                                  #    (Boot sets this to false automatically with devtools)
spring.thymeleaf.prefix=classpath:/templates/
spring.thymeleaf.suffix=.html
spring.thymeleaf.encoding=UTF-8
spring.thymeleaf.mode=HTML
spring.thymeleaf.check-template-location=true
spring.web.resources.static-locations=classpath:/static/   # css/js/img live HERE, not templates/
```

⚠️ **`templates/` is not web-accessible; `static/` is.** A file in `src/main/resources/templates/` can only be reached by a controller returning its view name. CSS, JS and images go in `src/main/resources/static/` and are served directly at `/css/app.css`. Putting a stylesheet in `templates/` gives you a silent 404.

⚠️ **Thymeleaf 3.1 (Spring Boot 3.x) removed the servlet expression objects** — `#request`, `#response`, `#session` and `#servletContext` no longer exist. Templates that used `${#request.getContextPath()}` or `${#httpServletRequest...}` break on upgrade. Pass what you need through the `Model` instead, or use `@{...}` for the context path. This is one of the most-hit Boot 2 → 3 migration errors in view code.

**Spring Security integration** needs its own dialect:
```xml
<dependency>
    <groupId>org.thymeleaf.extras</groupId>
    <artifactId>thymeleaf-extras-springsecurity6</artifactId>   <!-- ⚠️ ...6 for Boot 3 -->
</dependency>
```
```html
<div sec:authorize="hasRole('ADMIN')">Admin panel</div>
<span sec:authentication="name">username</span>
```
💡 Thymeleaf also **auto-inserts the CSRF hidden field** into any `<form th:action="...">` when Spring Security is on the classpath — which is why CSRF "just works" for server-rendered forms and is a manual problem for SPAs ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)).

### W11.5 [+] When *not* to use Thymeleaf

Be clear-eyed about this, because as a backend engineer you'll mostly be building APIs:

| Situation | Use |
|---|---|
| React / Vue / Angular / mobile front end | ❌ no Thymeleaf — `@RestController` + JSON |
| Public content site needing SEO and fast first paint | ✅ Thymeleaf |
| Internal admin tools, dashboards, CRUD back offices | ✅ Thymeleaf — enormously less work than a separate SPA |
| Emails, PDFs, generated reports | ✅ Thymeleaf (it renders to a `String`, not just to a response) |
| HTMX / Turbo "hypermedia-driven" apps | ✅ Thymeleaf — a strong current-generation fit |
| Anything with `@RestController` | ❌ no view layer at all |

```java
// Thymeleaf outside the web layer — rendering an email body
@Service
@RequiredArgsConstructor
public class EmailService {
    private final SpringTemplateEngine templateEngine;

    public String renderWelcome(User user) {
        Context ctx = new Context(Locale.ENGLISH);
        ctx.setVariable("user", user);
        return templateEngine.process("emails/welcome", ctx);   // → an HTML String
    }
}
```

🐍🟨 **Equivalents, for orientation:** Thymeleaf ↔ **EJS/Pug/Handlebars** (Express) ↔ **Jinja2** (Flask/FastAPI) ↔ **Django templates** ↔ **ERB** (Rails) ↔ **Razor** (ASP.NET). Thymeleaf's distinguishing feature against every one of them is natural templating; its distinguishing weakness is verbosity.

---

## W12. API documentation: OpenAPI and Swagger [Q32, Q33]

### W12.1 Is this the same Swagger as FastAPI's? [Q32]

> **Your question:** *"is this swagger same as what we have used for python+fastapi api documentation generation?"*

**Yes — the core specification is identical.** Both use the **OpenAPI Specification (OAS)**. Only the *generator* differs:

| | FastAPI | Spring Boot |
|---|---|---|
| Who generates the spec | FastAPI itself, from your Pydantic models + type hints | the **springdoc-openapi** library, scanning classes by reflection |
| When | at application launch | at runtime, on first request to `/v3/api-docs` |
| Spec version | OpenAPI 3.1 | OpenAPI 3.0 or 3.1, chosen by `springdoc.api-docs.version`. Current springdoc (3.2.0) defaults to `openapi_3_1`. Since **2.8.0** (Jan 2025, changelog #2790: "Moving to OpenAPI 3.1 as the default") 2.x does too. **Before 2.8.0 the default was OpenAPI 3.0** (the property was unset) |
| UI | Swagger UI at `/docs`, ReDoc at `/redoc` | **the same Swagger UI**, at `/swagger-ui/index.html` |
| Built in? | ✅ zero dependencies | ❌ **one dependency to add** |

**The generated JSON is interchangeable.** The file your Spring Boot app produces can be uploaded to SwaggerHub, imported into Postman, or handed to a front-end team used to FastAPI — it is the same artifact.

⚠️ **Terminology worth getting right**, because the words are used loosely everywhere:
- **OpenAPI** — the *specification* (the JSON/YAML schema format). Formerly called "Swagger Specification" up to 2.0.
- **Swagger** — SmartBear's *toolset* built around it: Swagger UI, Swagger Editor, Swagger Codegen.
- **springdoc-openapi** — the Spring library that generates OpenAPI from your code. ✅ this is what you add.
- **SpringFox** — the **old, dead** library. Last release 3.0.0 in 2020, does not work with Boot 3. ⚠️ Most blog posts you'll find still use it; if a tutorial says `@Api`, `@ApiOperation` or `Docket`, it's SpringFox and it's obsolete.

### W12.2 The dependency [Q32]

```xml
<!-- Spring Boot 3.x -->
<dependency>
    <groupId>org.springdoc</groupId>
    <artifactId>springdoc-openapi-starter-webmvc-ui</artifactId>
    <version>2.9.1</version>
</dependency>
```
⚠️ **springdoc is not managed by the Spring Boot BOM — you must pin the version yourself.** And the version must match your Boot generation:

| springdoc | Spring Boot | Note |
|---|---|---|
| **1.x** | Boot 2.x | `springdoc-openapi-ui` (old artifact name) |
| **2.9.1** | **Boot 3.x** | ✅ what you want today |
| 3.1.1 | Boot 4 | |

*(`2.6.0` still works but is behind; 2.9.1 is the current Boot 3 line as of September 2026.)*

📌 **Update (checked on springdoc.org, November 2026):** the current releases are **2.10.0** for Boot 3.x and **3.2.0** for Boot 4.x. Boot 4 projects (e.g. Boot 4.1.x) need the **3.x** line. Bump the versions above accordingly.

| Artifact | For |
|---|---|
| `springdoc-openapi-starter-webmvc-ui` | Spring MVC **+ Swagger UI** ✅ |
| `springdoc-openapi-starter-webmvc-api` | Spring MVC, spec only, no UI — good for production |
| `springdoc-openapi-starter-webflux-ui` / `-api` | WebFlux |

That's all. Restart, and both endpoints exist:
- `http://localhost:8080/swagger-ui/index.html` — the interactive UI
- `http://localhost:8080/v3/api-docs` — the raw JSON
- `http://localhost:8080/v3/api-docs.yaml` — the raw YAML

### W12.3 Does it work with Spring Data REST? [Q32]

> **Your question:** *"does openapi-swagger exist for spring-data-rest as well or only with @RestController?"*

**Yes — you are not restricted to `@RestController`.** springdoc has explicit, built-in support for the Spring Data REST engine. It scans your `@RepositoryRestResource` interfaces at runtime and documents all the automated CRUD routes, `/search` paths and parameters.

```xml
<!-- ⚠️ For Spring Data REST you need this ADDITIONAL module -->
<dependency>
    <groupId>org.springdoc</groupId>
    <artifactId>springdoc-openapi-starter-data-rest</artifactId>
    <version>2.9.1</version>
</dependency>
```
Other optional modules worth knowing: `springdoc-openapi-starter-common` (core), and the Spring HATEOAS / Spring Security integrations that ship inside the starters.

⚠️ **But the annotations don't reach the generated methods.** You cannot put `@Operation` on `findById` — you didn't write it. For automated routes you document the **entity fields** with `@Schema`, and springdoc flows those descriptions into every generated operation (`GET`, `POST`, `PUT`, `DELETE`). This is one more argument for [§D5.8](04-spring-data.md#d58-projections-vs-dtos-q31): DTOs + controllers are far more documentable.

### W12.4 Customizing the paths [Q32]

> **Your question:** *"can we configure the custom path for swagger ui using .env (application.properties) variables? and how to configure custom path for api-docs?"*

**Yes, entirely through properties** — so they can come from environment variables via relaxed binding ([§C3.5](02-spring-core.md#c35-relaxed-binding-env-var-to-property-name-)).

```properties
# 1. Custom path for the interactive HTML dashboard  (default: /swagger-ui/index.html)
springdoc.swagger-ui.path=/developer-portal/docs.html

# 2. Custom path for the raw metadata endpoint       (default: /v3/api-docs)
springdoc.api-docs.path=/api/v1/specification
```
Now `http://localhost:8080/developer-portal/docs.html` loads Swagger UI.

**[+] The rest of the properties you'll actually use:**
```properties
# ⚠️ THE MOST IMPORTANT ONE — turn the whole thing OFF in production
springdoc.api-docs.enabled=false
springdoc.swagger-ui.enabled=false

# UI behaviour
springdoc.swagger-ui.operationsSorter=method          # or alpha
springdoc.swagger-ui.tagsSorter=alpha
springdoc.swagger-ui.tryItOutEnabled=true
springdoc.swagger-ui.filter=true                      # a search box over operations
springdoc.swagger-ui.displayRequestDuration=true
springdoc.swagger-ui.doc-expansion=none               # collapse everything by default

# Scanning
springdoc.packages-to-scan=com.example.api
springdoc.paths-to-match=/api/**
springdoc.paths-to-exclude=/internal/**
springdoc.show-actuator=true                          # document actuator endpoints too

# Group several specs (public API / admin API / internal)
springdoc.group-configs[0].group=public
springdoc.group-configs[0].paths-to-match=/api/public/**
springdoc.group-configs[1].group=admin
springdoc.group-configs[1].paths-to-match=/api/admin/**
```
💡 **Grouping is genuinely useful** — a dropdown in Swagger UI switches between specs, so you can publish the public spec to partners without exposing your admin surface.

Because these are ordinary properties, an env var works: `SPRINGDOC_SWAGGER_UI_PATH=/internal-docs`, or a profile:
```yaml
# application-prod.yml — never ship the docs UI publicly by accident
springdoc:
  api-docs:
    enabled: false
  swagger-ui:
    enabled: false
```

### W12.5 Why you'd want the JSON/YAML endpoint [Q32]

> **Your question:** *"can we get all the endpoint in json/yaml format [when are these useful]?"*

Hitting `/v3/api-docs` returns a dense JSON blob that no human wants to read. Its value is **automation**:

| Use | How |
|---|---|
| **Client SDK generation** | Feed the JSON to `openapi-generator-cli` and get type-safe clients in **TypeScript, Swift, Kotlin, Dart, Go, Python** — front-end and mobile teams stop hand-writing HTTP code. |
| **CI/CD breaking-change tests** | Commit the spec to git. On each build, diff the new spec against the committed one and **fail the build** if a field was removed or a type changed. Tools: `openapi-diff`, `oasdiff`. |
| **API gateways** | AWS API Gateway, Apigee, Kong and Azure APIM read the spec directly to configure routing, security and rate limits. |
| **Contract testing** | Validate that real responses match the advertised schema (`atlassian/swagger-request-validator`). |
| **Mock servers** | Prism or WireMock serve a fake backend straight from the spec, so front-end work starts before the backend exists. |

```bash
# Snapshot the spec at build time (e.g. via the springdoc Maven plugin), then:
npx @openapitools/openapi-generator-cli generate \
    -i target/openapi.json -g typescript-axios -o ../frontend/src/api

# Fail CI on a breaking change
npx oasdiff breaking api/openapi-baseline.json target/openapi.json
```
💡 **Generating the spec at build time** (`springdoc-openapi-maven-plugin`) rather than scraping a running server is the pattern that makes all of the above reliable in CI.

### W12.6 Enriching the docs with `@Operation` and `@Schema` [Q33]

> **Your question [Q33]:** *"how to add code comments / descriptions to your auto-generated documentation using @Operation and @Schema annotations"*

The annotations live in **`io.swagger.v3.oas.annotations`** — note **v3**; the `io.swagger.annotations` (v2) package is the obsolete SpringFox one.

#### `@Operation` on controller methods

```java
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/v1/users")
public class UserManagementController {

    @Operation(
        summary = "Promote a user to Premium tier",
        description = "Processes the account upgrade logic, deducts initialization billing, "
                    + "and triggers a confirmation email notification loop downstream."
    )
    @ApiResponses(value = {
        @ApiResponse(responseCode = "200", description = "User account successfully upgraded to premium tier."),
        @ApiResponse(responseCode = "402", description = "Payment Required - User lacks sufficient account balance."),
        @ApiResponse(responseCode = "404", description = "Target User Identifier not found in database records.")
    })
    @PutMapping("/{id}/promote")
    public ResponseEntity<UserResponseDto> promoteUser(@PathVariable("id") Long id) {
        return ResponseEntity.ok(new UserResponseDto("Alice Smith", "PREMIUM"));
    }
}
```

#### `@Schema` on DTOs and fields

```java
import io.swagger.v3.oas.annotations.media.Schema;

@Schema(description = "Data Transfer Object containing updated profile information for the user account.")
public class UserUpdateDto {

    @Schema(
        description = "The primary email address associated with the user account.",
        example = "developer.support@example.com",
        requiredMode = Schema.RequiredMode.REQUIRED
    )
    private String email;

    @Schema(
        description = "The display profile name of the target user.",
        example = "JohnDoe99",
        maxLength = 50,
        minLength = 3
    )
    private String displayName;

    @Schema(
        description = "Current account classification status flag.",
        allowableValues = {"REGULAR", "PREMIUM", "SUSPENDED"},
        example = "REGULAR"
    )
    private String membershipStatus;
}
```

#### What changes visually in Swagger UI

| Area | Before | After |
|---|---|---|
| **Endpoint panel** | the bare signature `PUT /api/v1/users/{id}/promote` | the summary *"Promote a user to Premium tier"*; expanding shows the markdown description of the billing and email side effects |
| **Response catalog** | generic defaults | exact descriptions for 200, 402, 404 |
| **Mock schema box** | empty or `"string"` | pre-filled with your `example` values, so "Try it out" works in one click without guessing formats |

#### [+] The rest of the annotation set

| Annotation | On | Purpose |
|---|---|---|
| `@Tag(name=, description=)` | class | groups operations into a named section |
| `@Parameter(description=, example=)` | parameter | documents one parameter |
| `@RequestBody` *(swagger's)* | parameter | documents the body — ⚠️ **name clash** with Spring's `@RequestBody`; fully qualify one of them |
| `@Hidden` | class/method/field | exclude from the docs entirely |
| `@SecurityRequirement(name=)` | method/class | marks the endpoint as requiring auth |
| `@ArraySchema` | field | documents collection element types |
| `@OpenAPIDefinition` | a config class | global title, version, contact, servers |

💡 **Bean Validation annotations are picked up automatically.** `@NotBlank`, `@Size(min,max)`, `@Min`, `@Max`, `@Pattern` and `@Email` on your DTO already become `required`, `minLength`/`maxLength`, `minimum`/`maximum` and `pattern` in the schema — so [§W7](#w7-validation-q55) buys you documentation for free. This is the closest Spring gets to FastAPI's "the type hints *are* the docs".

**Global metadata:**
```java
@Configuration
@OpenAPIDefinition(
    info = @Info(title = "Orders API", version = "v1",
                 description = "Order lifecycle management",
                 contact = @Contact(name = "Platform Team", email = "platform@example.com")),
    servers = { @Server(url = "https://api.example.com", description = "Production"),
                @Server(url = "http://localhost:8080",   description = "Local") })
public class OpenApiConfig {
    @Bean
    public OpenAPI customOpenApi() {          // the programmatic alternative
        return new OpenAPI().components(new Components()
            .addSecuritySchemes("bearerAuth", new SecurityScheme()
                .type(SecurityScheme.Type.HTTP).scheme("bearer").bearerFormat("JWT")))
            .addSecurityItem(new SecurityRequirement().addList("bearerAuth"));
    }
}
```
💡 That `bearerAuth` scheme adds the **"Authorize" button** to Swagger UI, letting you paste a JWT and have it sent on every "Try it out" — the single most useful thing to configure once security is on.

### W12.7 Documenting gRPC [Q32]

> **Your question:** *"do we have any such tool to generate documentation for grpc as well? what are the dependencies required for this or is this auto provided?"*

**Yes, tools exist — but you cannot use Swagger UI out of the box**, because gRPC sends binary Protobuf over HTTP/2, and OpenAPI describes JSON over HTTP/1.1-style semantics. Two approaches:

#### Approach A — the Protobuf gateway (gRPC to OpenAPI/Swagger)

If you want standard Swagger HTML dashboards for a gRPC service, the industry standard is **grpc-gateway** with the **`protoc-gen-openapiv2`** plugin.
- **How it works:** it acts as a **reverse proxy** that accepts REST/JSON requests, transforms them into binary gRPC packets, and routes them to your downstream service.
- **The doc generation:** the compiler scans your `.proto` contract and emits a `swagger.json`, which you feed into a standard Swagger UI.

✅ Best when you must expose the same service over both gRPC (internal) and REST (external).

#### Approach B — native Protobuf doc generators

If you don't want a REST proxy, generate documentation directly from the `.proto` files with **`protoc-gen-doc`** or **sabledocs**. They read the comments in your `.proto` and produce clean Markdown or HTML pages describing services, messages and payloads.

```protobuf
// order_service.proto — these comments become the documentation
service OrderService {
  // Fetches a single order by its identifier.
  // Returns NOT_FOUND if the order does not exist.
  rpc GetOrder(GetOrderRequest) returns (Order);
}
```

⚠️ **Dependencies are NOT auto-provided by Spring Boot.** You install protoc compiler plugins or configure a build tool — **Buf** is the modern choice — in your pipeline:
```yaml
# buf.gen.yaml
version: v2
plugins:
  - remote: buf.build/grpc-ecosystem/openapiv2
    out: gen/openapiv2
  - remote: buf.build/community/pseudomuto-doc
    out: gen/docs
    opt: [markdown,index.md]
```

💡 **[+] The thing to internalise:** with gRPC the `.proto` file **is** the contract and **is** the documentation — machine-readable, versioned, and directly compilable into clients in every language. That's strictly stronger than OpenAPI, which is *derived* from code and can drift from it. The downside is that you need a proto registry (Buf Schema Registry, or a shared repo) for consumers to discover it, whereas an OpenAPI endpoint is just a URL. Generating docs is therefore less urgent in gRPC than in REST — the schema is already the source of truth.

---



---

[⬅ 02-spring-core.md](02-spring-core.md) · [🏠 Start here](00-start-here.md) · [04-spring-data.md ➡](04-spring-data.md)
