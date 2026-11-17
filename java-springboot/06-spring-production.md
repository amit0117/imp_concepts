# Spring in Production — Downstream Calls, Resilience, Scheduling and Config

[⬅ 05-spring-security.md](05-spring-security.md) · [🏠 Start here](00-start-here.md)

> Part of the Java & Spring Boot learning set. Section labels in this file start with **P**. The legend, version landscape, quick revision sheet and glossary live in [00-start-here.md](00-start-here.md).

## Contents

- [P1. Calling downstream services: RestTemplate, WebClient, gRPC interceptors [Q17–Q21]](#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21)
  - [P1.1 The vocabulary [Q19]](#p11-the-vocabulary-q19)
  - [P1.2 `ClientInterceptor` vs `ServerInterceptor` [Q17]](#p12-clientinterceptor-vs-serverinterceptor-q17)
  - [P1.3 The mental model: interceptors are middleware, not exceptions [Q18]](#p13-the-mental-model-interceptors-are-middleware-not-exceptions-q18)
  - [P1.4 The error flow compared: REST vs gRPC [Q18]](#p14-the-error-flow-compared-rest-vs-grpc-q18)
  - [P1.5 Writing a gRPC `ClientInterceptor`: the 4-step formula [Q19]](#p15-writing-a-grpc-clientinterceptor-the-4-step-formula-q19)
  - [P1.6 Interceptor ordering — and the reversal trap](#p16-interceptor-ordering--and-the-reversal-trap)
  - [P1.7 The complete worked example: a gateway calling a payment service [Q20]](#p17-the-complete-worked-example-a-gateway-calling-a-payment-service-q20)
  - [P1.8 Where `RestTemplate` sits relative to the exception [Q21]](#p18-where-resttemplate-sits-relative-to-the-exception-q21)
  - [P1.9 [+] `RestTemplate` vs `WebClient` vs `RestClient` vs `@HttpExchange`](#p19--resttemplate-vs-webclient-vs-restclient-vs-httpexchange)
  - [P1.10 [+] Protobuf: the schema, and the Java it generates](#p110--protobuf-the-schema-and-the-java-it-generates)
  - [P1.11 [+] gRPC: what codegen gives you, and how a call actually runs](#p111--grpc-what-codegen-gives-you-and-how-a-call-actually-runs)
  - [P1.12 [+] Inside a gRPC call: the call objects, the callbacks, and the unary lifecycle](#p112--inside-a-grpc-call-the-call-objects-the-callbacks-and-the-unary-lifecycle)
  - [P1.13 [+] Interceptors: client/server symmetry and execution order](#p113--interceptors-clientserver-symmetry-and-execution-order)
  - [P1.14 [+] `StreamObserver`: the rules, corrected](#p114--streamobserver-the-rules-corrected)
  - [P1.15 [+] What the `.proto` generates, and how to read it](#p115--what-the-proto-generates-and-how-to-read-it)
- [P2. Resilience: retries, recovery and circuit breakers](#p2-resilience-retries-recovery-and-circuit-breakers)
  - [P2.1 [+] Resilience: timeouts, retries, circuit breakers](#p21--resilience-timeouts-retries-circuit-breakers)
  - [P2.2 Spring Retry: `@EnableRetry`, `@Retryable`, `@Recover` [+]](#p22-spring-retry-enableretry-retryable-recover-)
  - [P2.3 How `@Retryable` works inside: the AOP chain [+]](#p23-how-retryable-works-inside-the-aop-chain-)
  - [P2.4 Resilience4j retry, and how it differs from Spring Retry [+]](#p24-resilience4j-retry-and-how-it-differs-from-spring-retry-)
  - [P2.5 Combining `@Retry` and `@CircuitBreaker`: why the order matters [+]](#p25-combining-retry-and-circuitbreaker-why-the-order-matters-)
  - [P2.6 Spring Framework 7 / Boot 4: native `@Retryable`, `@EnableResilientMethods` and `@ConcurrencyLimit` [+]](#p26-spring-framework-7--boot-4-native-retryable-enableresilientmethods-and-concurrencylimit-)
  - [P2.7 Which one should I use? [+]](#p27-which-one-should-i-use-)
- [P3. Background work: @Scheduled and @Async](#p3-background-work-scheduled-and-async)
  - [P3.1 Enabling scheduling [+]](#p31-enabling-scheduling-)
  - [P3.2 Writing scheduled tasks, and the four trigger types [+]](#p32-writing-scheduled-tasks-and-the-four-trigger-types-)
  - [P3.3 The scheduler thread pool, and why one slow task delays the rest [+]](#p33-the-scheduler-thread-pool-and-why-one-slow-task-delays-the-rest-)
  - [P3.4 Externalizing intervals [+]](#p34-externalizing-intervals-)
  - [P3.5 `@Async`: running any method on another thread [+]](#p35-async-running-any-method-on-another-thread-)
  - [P3.6 `@Scheduled` + `@Async`: allowing overlapping runs [+]](#p36-scheduled--async-allowing-overlapping-runs-)
  - [P3.7 Production gotchas [+]](#p37-production-gotchas-)
- [P4. Externalized configuration at scale: Spring Cloud Config and runtime refresh](#p4-externalized-configuration-at-scale-spring-cloud-config-and-runtime-refresh)
  - [P4.1 The problem it solves [+]](#p41-the-problem-it-solves-)
  - [P4.2 Config Server and Config Client [+]](#p42-config-server-and-config-client-)
  - [P4.3 The stale-config problem, and `/actuator/refresh` [+]](#p43-the-stale-config-problem-and-actuatorrefresh-)
  - [P4.4 Automating refresh: Spring Cloud Bus and the `/monitor` webhook [+]](#p44-automating-refresh-spring-cloud-bus-and-the-monitor-webhook-)
  - [P4.5 With AWS Parameter Store / Secrets Manager [+]](#p45-with-aws-parameter-store--secrets-manager-)
  - [P4.6 Summary [+]](#p46-summary-)
- [P5. Production-grade concerns [+]](#p5-production-grade-concerns-)
  - [P5.1 Project structure](#p51-project-structure)
  - [P5.2 DTOs vs entities — never expose your entities [+]](#p52-dtos-vs-entities--never-expose-your-entities-)
  - [P5.3 Testing [+]](#p53-testing-)
  - [P5.4 Actuator: health, metrics [+]](#p54-actuator-health-metrics-)
  - [P5.5 Observability: structured logging and tracing [+]](#p55-observability-structured-logging-and-tracing-)
  - [P5.6 The deployment shape [+]](#p56-the-deployment-shape-)
  - [P5.7 The production checklist](#p57-the-production-checklist)

---

## P1. Calling downstream services: RestTemplate, WebClient, gRPC interceptors [Q17–Q21]

### P1.1 The vocabulary [Q19]

> **Your question [Q19]:** *"what is RestTemplate and StatusRuntimeException, ResponseErrorHandler, ClientHttpRequestInterceptor?"*

| Term | World | What it is |
|---|---|---|
| **`RestTemplate`** | REST client | Spring's classic **synchronous** HTTP client for calling other microservices |
| **`ClientHttpRequestInterceptor`** | REST client | **middleware for `RestTemplate`** — intercepts the whole request/response, for global logging, timing, or appending `Authorization: Bearer …` to every outgoing call |
| **`ResponseErrorHandler`** | REST client | customises how `RestTemplate` reacts to HTTP errors — e.g. turning a 404/500 into **your own domain exception** instead of the default `HttpClientErrorException` |
| **`StatusRuntimeException`** | gRPC client | the **unchecked exception a gRPC stub throws** whenever a remote call returns a non-`OK` status (`NOT_FOUND`, `UNAVAILABLE`, …) |
| **`ClientInterceptor`** | gRPC client | the gRPC analogue of `ClientHttpRequestInterceptor` |
| **`ServerInterceptor`** | gRPC server | the gRPC analogue of a servlet filter / `HandlerInterceptor` |

### P1.2 `ClientInterceptor` vs `ServerInterceptor` [Q17]

> **Your question [Q17]:** *"do we have anything like ClientInterceptor in grpc error handling? is this similar to some ServerInterceptor in grpc?"*

**Yes — think of them as mirror images across the wire.** A `ServerInterceptor` handles errors on the server side *before they go out*; a `ClientInterceptor` handles them on the client side *right as they come back*.

| Feature | **`ServerInterceptor`** | **`ClientInterceptor`** |
|---|---|---|
| Where it lives | on the **server** application | on the **client** application |
| REST analogy | Spring's `HandlerInterceptor` or `@ControllerAdvice` | Spring's `ClientHttpRequestInterceptor` (with `RestTemplate` / `WebClient`) |
| Error-handling role | catches unexpected Java runtime crashes (e.g. `NullPointerException`), translates them into a gRPC status code (e.g. `INTERNAL`), and flushes them down the stream | intercepts the **inbound** error code arriving over the wire, letting you log it, transform it, or trigger retries **before your business code sees it** |

**How error handling works behind the scenes.** When a downstream gRPC service returns `NOT_FOUND` or `UNAVAILABLE`, the networking layer reads those **trailers**. Before throwing a `StatusRuntimeException` into your code, it passes the failure through your `ClientInterceptor`.

```java
import io.grpc.*;

public class DownstreamErrorInterceptor implements ClientInterceptor {

    @Override
    public <ReqT, RespT> ClientCall<ReqT, RespT> interceptCall(
            MethodDescriptor<ReqT, RespT> method, CallOptions callOptions, Channel next) {

        // 1. Intercept the outgoing call and forward it to the next channel step
        return new ForwardingClientCall.SimpleForwardingClientCall<ReqT, RespT>(next.newCall(method, callOptions)) {

            @Override
            public void start(Listener<RespT> responseListener, Metadata headers) {

                // 2. Intercept the incoming response listener
                super.start(new ForwardingClientCallListener.SimpleForwardingClientCallListener<RespT>(responseListener) {

                    @Override
                    public void onClose(Status status, Metadata trailers) {
                        // 3. Check if the status returned from downstream is NOT OK
                        if (!status.isOk()) {
                            System.err.println("Downstream RPC Failed! Method: " + method.getFullMethodName()
                                    + " | Status Code: " + status.getCode()
                                    + " | Reason: " + status.getDescription());

                            if (status.getCode() == Status.Code.UNAVAILABLE) {
                                // Take action if a critical downstream service is completely down
                            }
                        }
                        // 4. Pass the status forward. If it's an error, this triggers StatusRuntimeException
                        super.onClose(status, trailers);
                    }
                }, headers);
            }
        };
    }
}
```

**When to use which:**
- **`ServerInterceptor`** — when you are writing the service that *provides* data, and want to guarantee your API never leaks raw Java crashes to consumers.
- **`ClientInterceptor`** — when your app *calls* other microservices and you want one central place to track downstream health, monitor errors, or inject global security tokens.

### P1.3 The mental model: interceptors are middleware, not exceptions [Q18]

**Interceptors and errors are two entirely different concepts in gRPC, and keeping them apart changes how you design error handling.**

> 📌 **`ClientInterceptor` and `ServerInterceptor` are middleware, not exception types.** They do not extend `Throwable`, they cannot be `throw`n, and nothing inherits from them to create error types. They are **network filters** — exactly like a `HandlerInterceptor` or a servlet filter in REST.

**Why gRPC has to work this way.** In REST you might define `class UserNotFoundException extends RuntimeException`, throw it in a service, and catch **that exact class** in `@ControllerAdvice`. **gRPC cannot do this, because a Java exception cannot travel across a network socket** — especially when the downstream service is written in Go or Python. So gRPC separates the **error object** from the **network filter**.

| | What is actually raised / caught |
|---|---|
| **To RAISE an error (server side, e.g. `order-service`)** | You do **not** throw an interceptor. Call `responseObserver.onError(Status.NOT_FOUND.withDescription("…").asRuntimeException())`. ⚠️ Simply **`throw`ing** a `StatusRuntimeException` from a plain grpc-java service method does **not** send `NOT_FOUND`: the server's safety net closes the call with **`UNKNOWN`** (see the listener table in [§P1.12](#p112--inside-a-grpc-call-the-call-objects-the-callbacks-and-the-unary-lifecycle)). Throwing only works if a `ServerInterceptor` (or a framework layer) catches the exception and translates it, which is one of the main reasons such interceptors exist. |
| **To CATCH an error (client side, e.g. `api-gateway`)** | The gRPC core library turns the arriving error code **back** into a `StatusRuntimeException`. Your code catches that with an ordinary `try`/`catch`. |

**So what do the interceptors do?** They are **traffic observers standing at the side of the highway**:
- **`ServerInterceptor`** (on the service raising the error) — if your code crashes with a raw `NullPointerException`, it intercepts **before the socket breaks**, converts it into a deliberate status (e.g. `Status.INTERNAL` with a safe description), and sends it out. Without such an interceptor, grpc-java itself closes the call with `UNKNOWN`.
- **`ClientInterceptor`** (on the gateway receiving the error) — when the binary error frame arrives, it intercepts **before your gateway logic**, so you can log, map or read metadata.

```
SERVER SIDE (order-service)          CLIENT SIDE (api-gateway)
─────────────────────────────────           ──────────────────────────────────
  your service impl                            your gateway code
        │ throws StatusRuntimeException              ▲ catches StatusRuntimeException
        ▼                                            │
  ServerInterceptor   ← observes, maps         ClientInterceptor  ← observes, logs
        │                                            ▲
        ▼         grpc-status: 5 (trailer)           │
   ════════════════ THE WIRE (HTTP/2 binary) ════════
```

### P1.4 The error flow compared: REST vs gRPC [Q18]

| Step | **REST API approach** | **gRPC approach** |
|---|---|---|
| **1. Downstream fails** | `order-service` throws a custom `OrderNotFoundException` | `order-service` calls `responseObserver.onError(...)` with code `NOT_FOUND` (or throws, and a `ServerInterceptor` translates the exception) |
| **2. Server middleware** | `@ControllerAdvice` catches it, converts to HTTP 404 and a JSON body | a `ServerInterceptor` can intercept the lifecycle to catch unhandled errors and format custom gRPC metadata trailers |
| **3. Over the wire** | an HTTP/1.1 text package: `HTTP/1.1 404 Not Found` + JSON body | an HTTP/2 **binary** package with a trailing metadata key: `grpc-status: 5` |
| **4. Gateway receives** | `RestTemplate`/`WebClient` receives the 404; a `ResponseErrorHandler` inspects the code | your `ClientInterceptor` intercepts the `onClose()` event and reads `grpc-status: 5` |
| **5. Gateway catches** | `RestTemplate` throws `HttpClientErrorException.NotFound`; you catch it | the stub throws `StatusRuntimeException`; you catch that standard class |

> **Summary for a gateway architecture:** the **downstream service** uses `StatusRuntimeException` to raise errors, and a `ServerInterceptor` to catch raw Java crashes globally before they leave. The **upstream gateway** uses a `ClientInterceptor` to monitor and log incoming network errors globally, while the **business code catches `StatusRuntimeException`** to handle the failure.

💡 **[+] The gRPC status codes worth memorising**, since you'll be mapping them constantly:

| Code | # | Means | Retry? |
|---|---|---|---|
| `OK` | 0 | success | — |
| `INVALID_ARGUMENT` | 3 | client sent bad data (≈ 400) | ❌ never |
| `NOT_FOUND` | 5 | ≈ 404 | ❌ |
| `ALREADY_EXISTS` | 6 | ≈ 409 | ❌ |
| `PERMISSION_DENIED` | 7 | ≈ 403 | ❌ |
| `RESOURCE_EXHAUSTED` | 8 | rate limited / quota (≈ 429) | ✅ with backoff |
| `FAILED_PRECONDITION` | 9 | state is wrong for this op | ❌ |
| `ABORTED` | 10 | concurrency conflict | ✅ |
| `UNIMPLEMENTED` | 12 | ≈ 501 — often a **version skew** between client and server protos | ❌ |
| `INTERNAL` | 13 | ≈ 500, a server bug | ❌ |
| **`UNAVAILABLE`** | 14 | ≈ 503 — service down, connection refused | ✅ **the one you retry** |
| `DEADLINE_EXCEEDED` | 4 | your own timeout fired | ⚠️ carefully — the work may have succeeded |
| `UNAUTHENTICATED` | 16 | ≈ 401 | ❌ |

⚠️ **`UNAVAILABLE` and `DEADLINE_EXCEEDED` are the two you'll see in production**, and they mean different things: `UNAVAILABLE` usually means the call never landed (safe to retry); `DEADLINE_EXCEEDED` means **you gave up**, and the server may well have completed the work — so retrying a non-idempotent operation can double-charge someone.

### P1.5 Writing a gRPC `ClientInterceptor`: the 4-step formula [Q19]

> **Your question [Q19]:** *"isn't this DownstreamErrorInterceptor a decorator? also what's the syntax for writing an interceptor if I wanted to do it for a custom use case? what are the steps that I should follow?"*

**Yes — it is textbook Decorator Pattern**, nested twice:
1. It takes an existing gRPC `ClientCall` and wraps it in a `SimpleForwardingClientCall`.
2. Inside that, it takes the network event `Listener` and wraps it in a `SimpleForwardingClientCallListener`.

By *decorating* these components it intercepts lifecycle events (`start`, `onClose`) **without breaking the underlying engine** — every overridden method ends by calling `super`, which forwards to the real object.

**The repeatable 4-step formula:**

| Step | What |
|---|---|
| **1. Implement the interface** | `implements ClientInterceptor`, override `interceptCall` — your entry point on every downstream call |
| **2. Decorate the outgoing request** | return a `ForwardingClientCall` wrapper instead of the raw `next.newCall()`, so you can intercept **outbound** actions like adding headers |
| **3. Decorate the inbound response** | inside that wrapper, override `start()` and wrap `responseListener` in a `ForwardingClientCallListener`, so you can intercept **inbound** events |
| **4. Override your target lifecycle hook** | put your logic in the matching hook |

**The lifecycle hooks:**

| Hook | Fires when | Good for |
|---|---|---|
| `start(listener, headers)` | the call begins | **injecting headers / auth tokens** |
| `sendMessage(msg)` | a request payload goes out | request logging, payload size metrics |
| `onHeaders(headers)` | response headers arrive | reading server metadata |
| `onMessage(msg)` | a response payload arrives | **caching, payload inspection** |
| `onClose(status, trailers)` | the call finishes | ✅ **error handling, metrics, logging** |
| `onReady()` | the stream is writable | flow control on streaming calls |

**A worked custom example — a timer:**
```java
import io.grpc.*;
import java.util.concurrent.TimeUnit;

// STEP 1: Implement the base ClientInterceptor interface
public class MetricsTimerInterceptor implements ClientInterceptor {

    @Override
    public <ReqT, RespT> ClientCall<ReqT, RespT> interceptCall(
            MethodDescriptor<ReqT, RespT> method, CallOptions callOptions, Channel next) {

        long startTimeNanos = System.nanoTime();

        // STEP 2: Decorate the outbound call
        return new ForwardingClientCall.SimpleForwardingClientCall<ReqT, RespT>(next.newCall(method, callOptions)) {

            @Override
            public void start(Listener<RespT> responseListener, Metadata headers) {

                // STEP 3: Decorate the inbound response listener
                super.start(new ForwardingClientCallListener.SimpleForwardingClientCallListener<RespT>(responseListener) {

                    @Override
                    public void onClose(Status status, Metadata trailers) {
                        try {
                            // STEP 4: Hook into onClose to calculate duration
                            long elapsedNanos  = System.nanoTime() - startTimeNanos;
                            long elapsedMillis = TimeUnit.NANOSECONDS.toMillis(elapsedNanos);

                            System.out.println("RPC Performance Metric -> Method: " + method.getFullMethodName()
                                    + " | Duration: " + elapsedMillis + "ms"
                                    + " | Status: " + status.getCode());
                        } finally {
                            // Crucial: ALWAYS pass the event forward down the decorator chain
                            super.onClose(status, trailers);
                        }
                    }
                }, headers);
            }
        };
    }
}
```
⚠️ **That `finally` is not decoration — it is load-bearing.** If your logging throws and `super.onClose()` is skipped, the call **never completes**: the caller's future never resolves and the thread hangs until its deadline. Every `super.*` call in an interceptor belongs in a `finally`.

⚠️ **`interceptCall` runs once per call, but `start()` may run more than once** if gRPC retries or hedges internally. Don't put "exactly once" logic (like incrementing a counter) in `interceptCall`'s body expecting it to line up 1:1 with network attempts.

### P1.6 Interceptor ordering — and the reversal trap

> **Your question [Q19]:** *"how to choose… whether the interceptor should be near the application or near the network by just changing the order of the interceptors. Suppose you have two client interceptors: a caching interceptor and a logging interceptor. What order should they be in? You might want the logging interceptor closer to the network to better monitor your application's communication and ignore cached RPCs."*

Interceptors compose like layers of an onion, and you do choose "application-near" vs "network-near" by position:

*(Your diagram, preserved.)*
```
   [ YOUR APPLICATION CODE ] 
               │
               ▼
   ┌───────────────────────┐
   │  Caching Interceptor  │ ◄─── Application-Near (Catches calls early to return cached data)
   └───────────────────────┘
               │
               ▼
   ┌───────────────────────┐
   │  Logging Interceptor  │ ◄─── Network-Near (Only logs requests that actually hit the wire)
   └───────────────────────┘
               │
               ▼
     [ THE NETWORK WIRE ]
```
**And the reasoning is correct:** the request hits **caching** first; on a hit it returns immediately and never reaches **logging**, so your logs contain only real over-the-wire traffic.

> ⚠️ **The trap: `ClientInterceptors.intercept()` applies the list in REVERSE.** Write the arguments in the order the diagram reads and you get the opposite composition — logging ends up application-near, logging your cache hits, which is exactly the thing the design was meant to avoid.
>
> From the grpc-java javadoc, verbatim:
> - **`ClientInterceptors.intercept(channel, a, b, c)`** — *"The **last** interceptor will have its `ClientInterceptor.interceptCall()` called **first**."*
> - **`ClientInterceptors.interceptForward(channel, a, b, c)`** — *"The **first** interceptor will have its `interceptCall()` called first."*
>
> So, to get the composition in the diagram above:
>
> ```java
> // ✅ option 1 — use intercept() and write the list BACKWARDS
> Channel ch = ClientInterceptors.intercept(channel, loggingInterceptor, cachingInterceptor);
>
> // ✅ option 2 — use interceptForward() and write the list in intuitive order
> Channel ch = ClientInterceptors.interceptForward(channel, cachingInterceptor, loggingInterceptor);
> ```
> 💡 **Prefer `interceptForward()`.** It means declaration order = execution order = the diagram above, so the code matches the mental model and the next reader doesn't have to remember this trap.

⚠️ **The same reversal applies on the server side**, and it is one more place to get caught:
- **`ServerInterceptors.intercept(service, a, b, c)`** — the **last** interceptor's `interceptCall()` runs **first**.
- **`ServerInterceptors.interceptForward(service, a, b, c)`** — the first runs first.
- ⚠️ Repeated calls to **`ServerBuilder.intercept(...)`** are **also** applied last-added-first.

**A quick reference, because this is genuinely hard to keep straight:**

| API | Declaration order → execution order |
|---|---|
| `ClientInterceptors.intercept(ch, a, b)` | **b, then a** ⚠️ reversed |
| `ClientInterceptors.interceptForward(ch, a, b)` | a, then b ✅ |
| `ServerInterceptors.intercept(svc, a, b)` | **b, then a** ⚠️ reversed |
| `ServerInterceptors.interceptForward(svc, a, b)` | a, then b ✅ |
| `ServerBuilder.intercept(a).intercept(b)` | **b, then a** ⚠️ reversed |
| Spring MVC `HandlerInterceptor` via `@Order` | lowest order first ✅ |
| Servlet `Filter` via `@Order` | lowest order first ✅ |

💡 **How to settle it in five seconds on a real codebase:** put a `log.info("ENTER {}", getClass().getSimpleName())` at the top of each `interceptCall` and make one call. Never reason it out from memory — I'd verify it even having just written this table.

**What belongs where:**

| Position | Interceptor | Why |
|---|---|---|
| **Application-near** (runs first) | caching, deduplication, tracing **span creation**, retry orchestration | must see *logical* calls, including ones that never hit the network |
| **Network-near** (runs last) | logging, metrics, auth header injection, compression | must see *actual* wire traffic, and auth headers must survive every retry |

⚠️ **Auth token injection belongs network-near.** If it runs application-near and a retry happens below it, the retried attempt reuses a token that may have expired mid-sequence.

### P1.7 The complete worked example: a gateway calling a payment service [Q20]

> **Your question [Q20]:** *"explain these with a sample example"*

**Scenario:** a ride-demand gateway calling a downstream payment service — **built the REST way first, then the gRPC way**, so you can compare directly.

#### Scenario 1 — the REST architecture

**1. The custom exception**
```java
public class PaymentFailedException extends RuntimeException {
    public PaymentFailedException(String message) { super(message); }
}
```

**2. The interceptor (`ClientHttpRequestInterceptor`)** — acts **near the network**, injecting a correlation ID into every outgoing request:
```java
import org.springframework.http.client.*;
import java.io.IOException;

public class RestLoggingAndTrackingInterceptor implements ClientHttpRequestInterceptor {
    @Override
    public ClientHttpResponse intercept(HttpRequest request, byte[] body,
                                        ClientHttpRequestExecution execution) throws IOException {
        request.getHeaders().add("X-Correlation-ID", "TRACK-12345");
        System.out.println("REST Network Call Outbound -> URI: " + request.getURI());
        return execution.execute(request, body);        // move to the next step
    }
}
```

**3. The error handler (`ResponseErrorHandler`)** — acts **near the application**, translating 4xx/5xx into a domain exception before `RestTemplate` blows up:
```java
import org.springframework.http.client.ClientHttpResponse;
import org.springframework.web.client.ResponseErrorHandler;
import java.io.IOException;

public class RestPaymentErrorHandler implements ResponseErrorHandler {
    @Override
    public boolean hasError(ClientHttpResponse response) throws IOException {
        return response.getStatusCode().isError();      // triggers on 4xx or 5xx
    }

    @Override
    public void handleError(ClientHttpResponse response) throws IOException {
        if (response.getStatusCode().value() == 402) {  // 402 Payment Required
            throw new PaymentFailedException("Insufficient funds in user account.");
        }
        throw new RuntimeException("Generic downstream REST failure.");
    }
}
```

**4. Wiring it together in the gateway**
```java
@Service
public class RideGatewayRestService {
    private final RestTemplate restTemplate;

    public RideGatewayRestService(RestTemplateBuilder builder) {
        this.restTemplate = builder
            .interceptors(new RestLoggingAndTrackingInterceptor())   // Network-Near
            .errorHandler(new RestPaymentErrorHandler())             // App-Near
            .build();
    }

    public void processRidePayment() {
        try {
            restTemplate.postForObject("http://payment-service/charge", null, String.class);
        } catch (PaymentFailedException e) {
            System.err.println("Handled business error smoothly: " + e.getMessage());
        }
    }
}
```
💡 **Always build `RestTemplate` from `RestTemplateBuilder`, never `new RestTemplate()`.** The builder applies Boot's auto-configured timeouts, metrics instrumentation, and any `RestTemplateCustomizer` beans in the context. A bare `new RestTemplate()` has **no timeouts at all** — see [§P2.1](#p21--resilience-timeouts-retries-circuit-breakers).

#### Scenario 2 — the gRPC architecture, same use case

One `ClientInterceptor` handles both outgoing metadata injection *and* inbound error watching:
```java
import io.grpc.*;

public class GrpcTrackingAndErrorInterceptor implements ClientInterceptor {

    @Override
    public <ReqT, RespT> ClientCall<ReqT, RespT> interceptCall(
            MethodDescriptor<ReqT, RespT> method, CallOptions callOptions, Channel next) {

        return new ForwardingClientCall.SimpleForwardingClientCall<ReqT, RespT>(next.newCall(method, callOptions)) {

            @Override
            public void start(Listener<RespT> responseListener, Metadata headers) {
                // Network-Near: inject the correlation tag into the binary headers
                Metadata.Key<String> trackingKey =
                        Metadata.Key.of("x-correlation-id", Metadata.ASCII_STRING_MARSHALLER);
                headers.put(trackingKey, "TRACK-12345");

                System.out.println("gRPC Network Call Outbound -> Method: " + method.getFullMethodName());

                super.start(new ForwardingClientCallListener.SimpleForwardingClientCallListener<RespT>(responseListener) {
                    @Override
                    public void onClose(Status status, Metadata trailers) {
                        if (!status.isOk()) {
                            System.err.println("Downstream gRPC Error Captured! Code: " + status.getCode()
                                    + " | Description: " + status.getDescription());
                        }
                        // Pass control back — an error status natively triggers StatusRuntimeException
                        super.onClose(status, trailers);
                    }
                }, headers);
            }
        };
    }
}
```
⚠️ **Metadata keys must be lowercase.** `Metadata.Key.of("X-Correlation-Id", ...)` throws at runtime — HTTP/2 header names are lowercase by specification. A very common first-time error.

```java
@Service
public class RideGatewayGrpcService {

    @GrpcClient("payment-service")     // the auto-generated stub
    private PaymentServiceGrpc.PaymentServiceBlockingStub paymentStub;

    public void processRidePayment(PaymentRequest request) {
        try {
            // The interceptor runs silently under the hood here
            PaymentResponse response = paymentStub.chargeUser(request);
            System.out.println("Payment settled successfully: " + response.getTransactionId());

        } catch (StatusRuntimeException e) {            // the native gRPC error object
            Status.Code code = e.getStatus().getCode();

            if (code == Status.Code.FAILED_PRECONDITION) {
                System.err.println("Business Error: Payment declined due to low balance. " + e.getMessage());
            } else if (code == Status.Code.UNAVAILABLE) {
                System.err.println("Network Error: Payment microservice is down. Activating fallback queue.");
            } else {
                System.err.println("System Error: Something unexpected went wrong.");
            }
        }
    }
}
```

> **Summary of the comparison:** the **REST** flow **splits** responsibilities — `ClientHttpRequestInterceptor` decorates the outgoing request metadata, `ResponseErrorHandler` traps bad status codes coming in. The **gRPC** flow **bundles** both into a single `ClientInterceptor` via deep object composition (decorating the `ClientCall` *and* its `Listener`), while your application layer acts cleanly on a standard `StatusRuntimeException`.

💡 **[+] Passing rich error details in gRPC.** `Status.getDescription()` is just a string. For structured errors (field-level validation, retry hints), use `com.google.rpc.Status` with typed `Any` details via `StatusProto.toStatusRuntimeException(...)` — the gRPC equivalent of a `ProblemDetail` body ([§W8.8](03-spring-web.md#w88-global-exception-handling-with-problemdetail-)).

### P1.8 Where `RestTemplate` sits relative to the exception [Q21]

> **Your question [Q21]:** *"where is this RestTemplate declared in the PaymentFailedException?"*

**It isn't. They are two completely separate classes with entirely different jobs.**

**`PaymentFailedException`** is a plain custom exception. Its only job is to carry an error message when a business rule breaks. **It knows nothing about networks, URLs, protocols, or `RestTemplate`:**
```java
// It only extends RuntimeException. No fields, no logic, no RestTemplate.
public class PaymentFailedException extends RuntimeException {
    public PaymentFailedException(String message) { super(message); }
}
```

**Where do they meet?** Inside `RestPaymentErrorHandler` and `RideGatewayRestService`. Think of it as an assembly line:

```
1. RestTemplate                makes the physical network call to payment-service
2. the network                 responds 402 Payment Required
3. RestPaymentErrorHandler     catches that bad response and CREATES + THROWS PaymentFailedException
4. RideGatewayRestService      the try block aborts; control drops into catch (PaymentFailedException e)
```

```java
public class RestPaymentErrorHandler implements ResponseErrorHandler {
    @Override
    public boolean hasError(ClientHttpResponse response) throws IOException {
        return response.getStatusCode().isError();
    }

    @Override
    public void handleError(ClientHttpResponse response) throws IOException {
        if (response.getStatusCode().value() == 402) {
            // ...WE instantiate and throw the custom exception HERE
            throw new PaymentFailedException("Insufficient funds in user account.");
        }
        throw new RuntimeException("Generic downstream REST failure.");
    }
}
```
```java
@Service
public class RideGatewayRestService {
    private final RestTemplate restTemplate;          // declared HERE, at the class level

    public RideGatewayRestService(RestTemplateBuilder builder) {
        this.restTemplate = builder
            .interceptors(new RestLoggingAndTrackingInterceptor())
            .errorHandler(new RestPaymentErrorHandler())     // hooking up the handler
            .build();
    }

    public void processRidePayment() {
        try {
            restTemplate.postForObject("http://payment-service/charge", null, String.class);   // 1
        } catch (PaymentFailedException e) {                                                   // 2
            System.err.println("Handled business error smoothly: " + e.getMessage());
        }
    }
}
```

💡 **The general principle worth extracting:** an **exception class is a pure data carrier**. It never knows who throws it or who catches it. The *thrower* (`ResponseErrorHandler`), the *carrier* (`PaymentFailedException`) and the *catcher* (`RideGatewayRestService`) are three separate concerns. This is the same separation as a DTO that knows nothing about the controller returning it — and getting used to it is a large part of reading Java codebases fluently.

### P1.9 [+] `RestTemplate` vs `WebClient` vs `RestClient` vs `@HttpExchange`

`RestTemplate` is **no longer the default recommendation**, and on Framework 7 it is formally deprecated. Worth knowing before you write new code.

| Client | Since | Style | Status |
|---|---|---|---|
| **`RestTemplate`** | Spring 3 | blocking, template-method | ⚠️ **Maintenance mode** in Spring 5.x–6.x (Boot 2.7 / 3.x: not deprecated, no new features). **Deprecated in Spring Framework 7** (Boot 4): the Framework reference says *"As of Spring Framework 7.0, `RestTemplate` is deprecated in favor of `RestClient` and will be removed in a future version"*. Migrate with `RestClient.create(restTemplate)`. |
| **`WebClient`** | Spring 5 | non-blocking (also usable blocking) | ✅ fully supported; needs `spring-boot-starter-webflux` |
| **`RestClient`** | **Spring 6.1** | **blocking, fluent** | ✅ **the modern default for a blocking app** — `WebClient`'s API with `RestTemplate`'s semantics |
| **`@HttpExchange`** | Spring 6 | **declarative interface** | ✅ ideal for downstream clients — a Feign-like, Spring-native approach |

```java
// RestClient — the modern blocking client. No reactive dependency required.
@Bean
RestClient paymentClient(RestClient.Builder builder) {
    return builder.baseUrl("http://payment-service")
        .requestInterceptor((req, body, exec) -> {                 // same interceptor interface
            req.getHeaders().add("X-Correlation-ID", MDC.get("correlationId"));
            return exec.execute(req, body);
        })
        .defaultStatusHandler(HttpStatusCode::isError, (req, res) -> {
            if (res.getStatusCode().value() == 402)
                throw new PaymentFailedException("Insufficient funds in user account.");
            throw new RuntimeException("Generic downstream REST failure.");
        })
        .build();
}

PaymentResponse r = paymentClient.post().uri("/charge")
        .body(request).retrieve().body(PaymentResponse.class);
```

```java
// @HttpExchange — declarative. This is the closest thing to a typed gRPC stub, for REST.
@HttpExchange(url = "/payments", accept = "application/json")
public interface PaymentApi {
    @PostExchange("/charge")
    PaymentResponse charge(@RequestBody PaymentRequest request);

    @GetExchange("/{id}")
    PaymentResponse get(@PathVariable String id);
}

@Bean
PaymentApi paymentApi(RestClient paymentClient) {
    return HttpServiceProxyFactory
            .builderFor(RestClientAdapter.create(paymentClient))
            .build()
            .createClient(PaymentApi.class);
}
```
✅ **`@HttpExchange` is what I'd reach for in a gateway.** It gives every downstream a typed interface — trivially mockable in tests, and the call site reads like a method call rather than a URL string. It is Spring's native answer to OpenFeign, with no extra dependency.

🐍🟨 **Your equivalents:** `RestClient` ↔ `requests` (Python) / `axios` (JS). `WebClient` ↔ `httpx.AsyncClient` / `fetch`. `@HttpExchange` ↔ a generated OpenAPI client, or `retrofit` if you've met Android.

### P1.10 [+] Protobuf: the schema, and the Java it generates

If your only serialisation experience is JSON + Pydantic, protobuf feels alien for about an hour and then feels obvious. Here is the whole model.

#### The shape of the thing

| | JSON + Pydantic (FastAPI) | Protobuf + gRPC |
|---|---|---|
| Schema lives in | Python classes | a **`.proto` file** — language-neutral, the single source of truth |
| Client/server agree how? | by convention + docs | by **compiling the same `.proto`** |
| Wire format | UTF-8 text | **binary**, field *numbers* not names |
| Field names on the wire | yes, repeated in every message | ❌ **no** — only the tag numbers |
| Types checked | at runtime, by Pydantic | at **compile time**, by the generated classes |
| Human-readable | ✅ | ❌ (this is the real trade-off) |

```protobuf
syntax = "proto3";
package com.example.orders.v1;

option java_package = "com.example.orders.v1";
option java_outer_classname = "OrderProtos";
option java_multiple_files = true;        // ← one .java file per message, not one giant outer class

message Order {
  string id          = 1;                 // ← 1, 2, 3 are FIELD NUMBERS, not values
  optional string note = 2;
  Money total        = 3;
  repeated Item items = 4;
  map<string, string> metadata = 5;
  Status status      = 6;

  enum Status { STATUS_UNSPECIFIED = 0; PENDING = 1; COMPLETED = 2; }
}
```

⚠️ **Field numbers are the contract, not the field names.** You may rename `id` to `orderId` freely — the wire format is unaffected. You may **never** reuse or change a number. That is why proto files carry `reserved 7, 9 to 11;` lines: they stop a future developer from recycling a retired number and silently mis-decoding old data. This is the exact opposite of JSON, where the *name* is the contract.

#### What `protoc` generates in Java

Messages are **immutable and `final`**, built through a nested `Builder` — the same pattern as `String` in Java:

```java
// Build (builder is mutable, message is not)
Order order = Order.newBuilder()
        .setId("abc-123")
        .setTotal(Money.newBuilder().setAmount(1250).setCurrency("USD").build())
        .addItems(item1)
        .addAllItems(moreItems)
        .putMetadata("source", "mobile")
        .setStatus(Order.Status.PENDING)
        .build();                                   // ← immutable from here on

// Modify → you get a NEW object
Order updated = order.toBuilder().setStatus(Order.Status.COMPLETED).build();
```

⚠️ **Builders are not thread-safe**; the built messages are. Build on one thread, share the result freely.

| Field kind | Generated on the message | Generated only on the builder |
|---|---|---|
| singular, **explicit** presence | `hasFoo()`, `getFoo()` | `setFoo()`, `clearFoo()` |
| singular, **implicit** presence | `getFoo()` | `setFoo()`, `clearFoo()` |
| `repeated Item items` | `getItemsCount()`, `getItems(i)`, `getItemsList()` | `setItems()`, `addItems()`, `addAllItems()`, `clearItems()` |
| `map<string,string> metadata` | `getMetadataMap()`, `getMetadataOrDefault()`, `containsMetadata()`, `getMetadataCount()` | `putMetadata()`, `removeMetadata()`, `clearMetadata()` |
| `oneof choice` | `hasX()`/`getX()` per option, **`getChoiceCase()`** | setters, `clearChoice()` |
| `enum Status` | `getStatus()` (enum), **`getStatusValue()`** (int) | `setStatus()`, `setStatusValue()` |

#### ⚠️ Field presence — the single biggest protobuf gotcha

**In proto3, a plain scalar field cannot tell "set to zero" apart from "not set".** There is no `hasX()` and no `null`; an unset `int32` reads back as `0`, an unset `string` as `""`, an unset `bool` as `false`. On the wire, a field holding its default value is **not transmitted at all**.

> *"Without the `optional` label, proto3 APIs do not track presence for basic types (numeric, string, bytes, and enums)."*

| Field type | `optional` keyword | `hasX()` generated? |
|---|---|---|
| singular numeric / string / bytes / enum | ❌ no | **❌ no** |
| singular numeric / string / bytes / enum | ✅ yes | ✅ yes |
| **singular message** | either | ✅ **yes, always** |
| `oneof` member | n/a | ✅ yes |
| `repeated` | n/a | ❌ — *"there is no distinction between an empty and a not-present repeated field"* |
| `map` | n/a | ❌ same |

```protobuf
int32 discount_percent          = 1;   // ⚠️ 0 and "absent" are indistinguishable
optional int32 discount_percent = 2;   // ✅ hasDiscountPercent() exists
```

💡 **Why this matters in a gateway.** A `PATCH`-style update where `0` is a meaningful value — "set the discount to 0" vs "leave the discount alone" — is *unrepresentable* without `optional`. The official recommendation is blunt: *"We recommend always adding the `optional` label for proto3 basic types."*

💡 **Two more conventions that exist for the same reason:**
- **Every enum's first value must be `0` and should be named `*_UNSPECIFIED`** — because `0` is what you get when the field was never set. Never give `0` a real business meaning.
- Unknown enum values decode to **`UNRECOGNIZED`** in Java rather than throwing, so a new server value does not crash an old client. ⚠️ Calling `getNumber()` on `UNRECOGNIZED` throws — use `getStatusValue()` if you need the raw int.

📌 **Python parallel:** `optional` in proto3 is doing the job of Pydantic's `Optional[int] = None` — distinguishing "absent" from "zero". Pydantic gets this for free because Python has `None`; protobuf had to add it back as an explicit opt-in.

---

### P1.11 [+] gRPC: what codegen gives you, and how a call actually runs

#### The four call types

```protobuf
service OrderService {
  rpc GetOrder     (GetOrderRequest)        returns (Order);                 // 1 unary
  rpc ListOrders   (ListOrdersRequest)      returns (stream Order);          // 2 server streaming
  rpc UploadEvents (stream Event)           returns (UploadSummary);         // 3 client streaming
  rpc Chat         (stream ChatMessage)     returns (stream ChatMessage);    // 4 bidirectional
}
```

| Type | Analogy | Use for |
|---|---|---|
| **Unary** | a normal REST call | 95 % of what you write |
| **Server streaming** | Server-Sent Events | large result sets, live feeds |
| **Client streaming** | chunked upload | batched telemetry |
| **Bidirectional** | WebSocket | chat, long-lived negotiation |

Streaming of any kind is possible because gRPC runs on **HTTP/2**, which multiplexes many logical streams over one TCP connection.

#### The three generated stubs

For each `service`, the protobuf gRPC plugin generates one outer class — `OrderServiceGrpc` — containing:

| Generated artifact | You use it to |
|---|---|
| `OrderServiceGrpc.OrderServiceImplBase` | **extend** it to write the server |
| `OrderServiceGrpc.OrderServiceBlockingStub` | call synchronously — returns `Order` directly |
| `OrderServiceGrpc.OrderServiceStub` | call asynchronously — results arrive via `StreamObserver` |
| `OrderServiceGrpc.OrderServiceFutureStub` | call asynchronously — returns a `ListenableFuture<Order>` |

**Server side:**

```java
public class OrderServiceImpl extends OrderServiceGrpc.OrderServiceImplBase {

    @Override
    public void getOrder(GetOrderRequest request, StreamObserver<Order> responseObserver) {
        Order order = repository.find(request.getId());
        responseObserver.onNext(order);        // send the message
        responseObserver.onCompleted();        // ⚠️ MUST be called, or the client hangs
    }
}
```

⚠️ **`onCompleted()` is not optional.** Forgetting it leaves the client blocked until its deadline expires. Even for a unary call, the response is modelled as a stream of exactly one message followed by a completion — which is why unary and streaming share one API shape.

**Client side:**

```java
// Blocking — the easy default
Order order = blockingStub
        .withDeadlineAfter(500, TimeUnit.MILLISECONDS)     // ✅ always set a deadline
        .getOrder(GetOrderRequest.newBuilder().setId("abc").build());

// Async
asyncStub.getOrder(request, new StreamObserver<Order>() {
    @Override public void onNext(Order value)     { handle(value); }
    @Override public void onError(Throwable t)    { log.error("rpc failed", t); }
    @Override public void onCompleted()           { log.info("done"); }
});
```

📌 **`StreamObserver` vs Go's `context.Context`.** These are often confused because both appear in every gRPC signature. They are different things:
- **`StreamObserver<T>`** is the *response channel* — the callback you push results into (server) or receive results from (client). Its Go equivalent is the `stream` parameter, or simply the returned value for unary calls.
- **Deadlines, cancellation, and request-scoped values** are Java's `io.grpc.Context` and `CallOptions.withDeadlineAfter(...)` — *those* are the true `context.Context` analogues.

| Concern | Go | Java gRPC |
|---|---|---|
| carrying a deadline | `context.WithTimeout` | `stub.withDeadlineAfter(...)` |
| cancellation signal | `ctx.Done()` | `io.grpc.Context.current().isCancelled()` |
| request-scoped values | `context.WithValue` | `Context.Key<T>` |
| sending the reply | `return resp, nil` | `responseObserver.onNext(...); onCompleted();` |

#### Errors: status codes, not exceptions

gRPC has **no HTTP status codes**. It has 17 canonical `Status.Code` values, and an error is sent by completing the call with a non-`OK` status:

```java
responseObserver.onError(Status.NOT_FOUND
        .withDescription("order " + id + " not found")
        .asRuntimeException());
```

| gRPC status | Rough HTTP equivalent |
|---|---|
| `OK` | 200 |
| `INVALID_ARGUMENT` | 400 |
| `UNAUTHENTICATED` | 401 |
| `PERMISSION_DENIED` | 403 |
| `NOT_FOUND` | 404 |
| `ALREADY_EXISTS` | 409 |
| `RESOURCE_EXHAUSTED` | 429 |
| `FAILED_PRECONDITION` | 400/409 |
| `ABORTED` | 409 |
| `UNIMPLEMENTED` | 501 |
| `INTERNAL` | 500 |
| `UNAVAILABLE` | 503 |
| `DEADLINE_EXCEEDED` | 504 |

⚠️ **`DEADLINE_EXCEEDED` vs `UNAVAILABLE`** is the distinction to internalise for a gateway: `UNAVAILABLE` means the server was unreachable and the call is generally **safe to retry**; `DEADLINE_EXCEEDED` means your deadline elapsed and **the server may well have completed the work** — retrying a non-idempotent call here causes duplicates.

On the client, a failed call throws `StatusRuntimeException`, and you recover the code with `Status.fromThrowable(t).getCode()`. This is the exception that [§P1.8](#p18-where-resttemplate-sits-relative-to-the-exception-q21) and the interceptor material in [§P1.2](#p12-clientinterceptor-vs-serverinterceptor-q17)–[§P1.6](#p16-interceptor-ordering--and-the-reversal-trap) are all built around.

#### How the build produces all this

```
  order.proto
      │
      │   protoc  +  protoc-gen-grpc-java plugin
      ▼
  ┌────────────────────────┬──────────────────────────┐
  │  Order.java            │  OrderServiceGrpc.java   │
  │  GetOrderRequest.java  │   ├─ ImplBase            │
  │  OrderProtos.java      │   ├─ BlockingStub        │
  │  (immutable + Builder) │   ├─ Stub                │
  │                        │   └─ FutureStub          │
  └────────────────────────┴──────────────────────────┘
      │
      ▼  generated into build output, NEVER hand-edited, NEVER committed
  compiled alongside your source
```

⚠️ **Never edit generated code, and never commit it.** It is regenerated on every build; your edit disappears at the next `mvn compile` / `bazel build`. If you need behaviour on a generated type, wrap it or use an extension method — not a patch.

💡 **The Maven/Gradle/Bazel job.** In Maven this is `protobuf-maven-plugin`; in Bazel it is `java_proto_library` / `java_grpc_library` targets. Large organisations often keep `.proto` files in one shared IDL tree so that every service compiles the *same* schema.

📌 **Coming in Spring Boot 4.1:** first-class gRPC auto-configuration, so the server and channel are wired by a starter rather than by hand ([§R2.4.7](00-start-here.md#r247-other-framework-7-additions-worth-knowing)).

---

### P1.12 [+] Inside a gRPC call: the call objects, the callbacks, and the unary lifecycle

> **Version note.** Everything in this section was verified against the **grpc-java 1.49.2** sources, the version I was working with (`io.grpc.ServerCall`, `ClientCall`, `ServerCalls`, `ServerCallImpl`, `ServerImpl`). Later releases may differ in details.

#### Two objects per side: one to *send*, one to *receive*

`ServerCall` and `ServerCall.Listener` are the **same conversation seen from two directions**. Express analogy: `res` (you write to it) and the request events (`req.on('data')`, `'end'`, `'close'`) are two separate objects; gRPC makes that split explicit.

| Side | Object you **call** (outbound) | Object the framework **calls** (inbound callbacks) |
|---|---|---|
| Server | `ServerCall<ReqT,RespT>`: `sendHeaders`, `sendMessage`, `request(n)`, `isReady`, `isCancelled`, `close(status, trailers)` | `ServerCall.Listener<ReqT>`: `onMessage`, `onHalfClose`, `onCancel`, `onComplete`, `onReady` |
| Client | `ClientCall<ReqT,RespT>`: `start(listener, headers)`, `request(n)`, `sendMessage`, `halfClose`, `cancel` | `ClientCall.Listener<RespT>`: `onHeaders`, `onMessage`, `onClose(status, trailers)`, `onReady` |

| Server listener callback | Meaning |
|---|---|
| `onMessage(req)` | one request message arrived |
| `onHalfClose()` | the client will send **no more** messages (for unary: "the request is complete, now run the handler") |
| `onCancel()` | the call ended **abnormally** (client cancelled, deadline, transport failure) |
| `onComplete()` | the call ended **normally** |
| `onReady()` | the outbound side can accept more without buffering |

`onComplete` vs `onCancel` is decided by the final **transport status** when the stream closes (`ServerImpl`'s `closedInternal`), not by what your handler did. Exactly one of them fires.

#### Diagram (a): the unary call lifecycle

```
 CLIENT                                                         SERVER
 ──────                                                         ──────
 stub.method(req)
   │  ClientCall.start(listener, headers) ───── HEADERS ──────▶  ServerInterceptor.interceptCall(call, headers, next)
   │  ClientCall.sendMessage(req)         ───── DATA ─────────▶     └─ next.startCall(call, headers) ⇒ returns Listener
   │  ClientCall.halfClose()              ───── END_STREAM ───▶  Listener.onMessage(req)      (UnaryServerCallListener STORES it)
   │                                                             Listener.onHalfClose()        ◀── handler is INVOKED here
   │                                                               └─ your impl: method(req, StreamObserver)
   │                                                                    responseObserver.onNext(resp)    → call.sendHeaders (auto) + call.sendMessage
   │                                                                    responseObserver.onCompleted()   → call.close(Status.OK, trailers)
   │  Listener.onHeaders(h)    ◀────────── HEADERS ──────────────
   │  Listener.onMessage(resp) ◀────────── DATA ─────────────────
   │  Listener.onClose(OK, t)  ◀────────── TRAILERS ─────────────  Listener.onComplete()      (normal end; onCancel() if abnormal)
```

**Why the handler runs in `onHalfClose`, not `onMessage`:** for unary, `UnaryServerCallListener` only stores the request in `onMessage` and calls your method in `onHalfClose`. That is also how it detects protocol violations: `onHalfClose` with no stored request gives `MISSING_REQUEST`; a second `onMessage` gives `TOO_MANY_REQUESTS`.

**Consequence for interceptors (verified):** if a wrapping listener *swallows* `onHalfClose` without forwarding it, the handler is never invoked and the call never completes on its own. If it forwards `onHalfClose` after its own code already closed the call, the server hits `IllegalStateException`/`MISSING_REQUEST`; it does **not** "run the handler with no request". That is why an interceptor that can abort a call (for example, one that decrypts the request) should keep a `requestAborted` flag and return early in `onHalfClose`.

#### What `ServerCallImpl` enforces (verified in source)

| Situation | Result |
|---|---|
| `close` called twice | `IllegalStateException("call already closed")` |
| `sendMessage` before `sendHeaders` at the **raw `ServerCall` level** | `IllegalStateException`. `StreamObserver` hides this because its `onNext` sends headers automatically |
| Unary call closed with `OK` but no response sent | the server converts it to `INTERNAL` ("Completed without a response") |
| Unary call sends two responses | `INTERNAL` ("Too many responses") |
| A listener callback **throws** | safety net in the server: the call is closed with **`UNKNOWN`** (`Status.fromThrowable` also maps unrecognised throwables to `UNKNOWN`) |

#### Express comparison

| Express | gRPC-java |
|---|---|
| `app.use((req,res,next)=>{...; next()})` | `ServerInterceptor.interceptCall(call, headers, next)`; calling `next.startCall(call, headers)` ≈ `next()` |
| forgetting `next()` hangs the request | returning a listener that never forwards `onHalfClose` hangs the call |
| `res.send()` twice → "headers already sent" | `close` twice → `IllegalStateException("call already closed")` |
| one event loop, handler must not block | **thread-per-call from an executor**; blocking is normal, but `directExecutor()` means *your* thread runs the callbacks |

### P1.13 [+] Interceptors: client/server symmetry and execution order

| | `ServerInterceptor` | `ClientInterceptor` |
|---|---|---|
| Method | `interceptCall(ServerCall call, Metadata headers, ServerCallHandler next)` | `interceptCall(MethodDescriptor method, CallOptions callOptions, Channel next)` |
| "Continue" | `next.startCall(call, headers)` returns a `ServerCall.Listener` | `next.newCall(method, callOptions)` returns a `ClientCall` |
| Wrap outbound | `ForwardingServerCall` / `SimpleForwardingServerCall` (intercept `sendMessage`, `close`) | `ForwardingClientCall` / `SimpleForwardingClientCall` (intercept `start`, `sendMessage`) |
| Wrap inbound | `ForwardingServerCallListener` / `SimpleForwardingServerCallListener` (`onMessage`, `onHalfClose`) | `ForwardingClientCallListener` (`onHeaders`, `onMessage`, `onClose`) |
| Where headers are touched | `headers` argument (request metadata in) | `start(listener, headers)` (request metadata out) |
| Contract | The returned listener must **never be null**; a throw closes the call with an error | build the call with `next.newCall`, then wrap it. ✅ A throw from `interceptCall` is **not** turned into a gRPC status: `InterceptorChannel.newCall` calls it directly, so the raw exception reaches the stub caller. To fail a call cleanly, extend `CheckedForwardingClientCall`; exceptions thrown in `checkedStart()` *before* `delegate().start()` are delivered to the listener as `onClose(Status.fromThrowable(e))` (grpc-java `ClientInterceptors` source) |

**Server execution order (the add-vs-run trap).** `ServerBuilder.intercept(...)` documents that interceptors run in the **reverse** of the order they were added, so the **last added runs first**. So if you register `[A, B, C]`, `C` runs first. This matters when one interceptor depends on another: an interceptor that puts a request context into the gRPC `Context` must run *before* every interceptor that reads it, so it must be registered *last*.

**Template-method pattern for interceptors.** A common design is a base class, say `ServerInterceptorBase`, that declares a `final` 3-argument `interceptCall` that looks up the `RequestContext` and then calls an `abstract` 4-argument `interceptCall(requestContext, call, headers, next)`. Subclasses cannot forget the lookup; this is the Java answer to "decorate every middleware with the same preamble".

### P1.14 [+] `StreamObserver`: the rules, corrected

`StreamObserver<T>` is the *application-level* view over the call objects. The server hands you one to **write** responses to; a client-side one **receives** responses.

| Method | Server side (`responseObserver`) | Client side (async stub callback) |
|---|---|---|
| `onNext(v)` | send one response (sends headers first if not yet sent) | one response arrived |
| `onError(t)` | end the call with an error status (`Status.fromThrowable`; plain exceptions become `UNKNOWN`) | the call failed |
| `onCompleted()` | end the call with `OK` | the call finished OK |

Rules that were wrong in the first draft of these notes, now fixed:

- ❌ *"`onCompleted` may only follow `onNext`."* **Only for unary/client-streaming responses.** Server-streaming and bidi may legally complete after zero or many `onNext`. For a **unary** method, `onCompleted` with no `onNext` is converted by the server to `INTERNAL` ("Completed without a response").
- ❌ *"`sendHeaders` is called automatically if omitted."* **Only through `StreamObserver`.** With the raw `ServerCall` it is required (see 21.13).
- ❌ *"Calling `onError` then `onCompleted` crashes the app."* Overstated: it is a **contract violation** (a call can end only once). What actually happens, verified in grpc-java source:
- `ServerCallStreamObserverImpl.onError`/`onCompleted` just call `call.close(...)`. The second close hits `checkState(!closeCalled, "call already closed")`, which throws `IllegalStateException` **out of your `onCompleted()` call**, so the rest of your method doesn't run.
- If you don't catch it, `ServerImpl`'s listener tries to close the stream with `UNKNOWN`. That has no effect, because the stream is already closed. `SerializingExecutor` then logs it at `SEVERE` ("Exception while executing runnable") and carries on.
- The client has already received the **first** status (your error).

So the result is a noisy log and a half-run method, not a crashed app. Don't do it.
- ✅ Choose **exactly one** terminal call: `onCompleted` **or** `onError`. A well-written handler base class does precisely this: error branch `onError(statusErrorResponse); return;`, success branch `onNext` then `onCompleted`.
- `ServerCalls.asyncUnaryCall(handler)` wraps your `UnaryMethod` into a `UnaryServerCallHandler` (which creates `UnaryServerCallListener` and a `ServerCallStreamObserverImpl`). That is the entire bridge from the callback world to "just implement a method".

### P1.15 [+] What the `.proto` generates, and how to read it

For a `greeter.proto` with a `Greeter` service, the build (Maven/Gradle protobuf plugin or Bazel `java_grpc_library`; the generated Java is usually **not checked in**) produces, for the **older plugin layout**:

| Generated | What it is |
|---|---|
| `GreeterGrpc` | the service holder: `ImplBase`, three stubs, `MethodDescriptor` getters, descriptor suppliers |
| `GreeterGrpc.GreeterImplBase` | `abstract class ... implements BindableService`. You **extend** it; the name is `<Service>ImplBase`, **not** an "implementation of the base". Default method bodies return `UNIMPLEMENTED` |
| `bindService()` (final) | builds a `ServerServiceDefinition` using internal `MethodHandlers` and `ServerCalls.asyncUnaryCall` |
| `GreeterStub` / `GreeterBlockingStub` / `GreeterFutureStub` | async (`StreamObserver`), blocking, and `ListenableFuture` clients (see 21.12) |
| `getSayHelloMethod()` | the **`MethodDescriptor`**: full name `package.Service/Method` (no leading slash), `MethodType`, marshallers |
| message classes | extend `GeneratedMessageV3` in this build, with a `*OrBuilder` interface and an outer `*Proto` class holding the file `Descriptor` |

**Two things called "descriptor":** the protobuf **`Descriptors.Descriptor`** describes a *message type* (fields, numbers, for reflection and JSON). gRPC's **`MethodDescriptor`** describes an *RPC method* (name, type, request/response marshallers). They are unrelated classes that share a word.

> **Layout caveat.** Newer protoc-gen-grpc-java layouts generate an `AsyncService` interface that `ImplBase` implements, and newer protobuf-java releases use `GeneratedMessage` instead of `GeneratedMessageV3`. ✅ Per the official release notes: `AsyncService` arrived in **grpc-java 1.54.0**, and the `GeneratedMessage` base class in **protobuf v26.0 (Java 4.26)**. Protobuf v28 (4.28) added binary-compatibility shims for old `GeneratedMessageV3` gencode. I only verified the **old** layout (`ImplBase` with a `final bindService()`, `GeneratedMessageV3`), by disassembling generated classes from a grpc-java 1.49 build. Do not assume the newer names here; check the generated output for the version in use. Protobuf basics are in 21.11.

#### Misconceptions I had → reality

| I thought | Reality |
|---|---|
| `map`/`filter`/`forEach` each loop the whole list | lazy and fused: one element at a time through the pipeline (§J2.9) |
| Java "arity" works like JS `fn.length` | the interface signature is checked at compile time (§J2.8) |
| `StreamObserver` can be a lambda | it has 3 abstract methods; not functional |
| the handler runs when the request arrives | for unary it runs in `onHalfClose` (21.13) |
| `ImplBase` = "the implementation of the base" | the base class **you extend**: `<Service>ImplBase` |
| `ServerCall` and `ServerCall.Listener` are the same | outbound vs inbound (21.13) |
| `.proto` generates only message classes | also stubs, `ImplBase`, `MethodDescriptor`, `OrBuilder`, file descriptor (21.16) |
| registered first = runs first | reverse: last listed runs first (21.14) |
| interceptor can return `null` listener to "ignore" | must never be null; use an empty `new ServerCall.Listener<ReqT>() {}` after closing the call |

#### Self-check (answers below each)

1. **Which callback invokes a unary handler, and why not `onMessage`?** `onHalfClose`; `onMessage` only stores the request so protocol violations (`MISSING_REQUEST`, `TOO_MANY_REQUESTS`) are detectable.
2. **Is `Predicate<T>` a functional interface? Is `StreamObserver<T>`?** Yes (`boolean test(T)`); no (three abstract methods).
3. **Which fires, `onComplete` or `onCancel`, and who decides?** Exactly one; the final transport status at stream close.
4. **A unary handler calls `onCompleted()` without `onNext`. Result?** The server closes with `INTERNAL` ("Completed without a response").
5. **You register server interceptors `[A, B, C]`. Which runs first?** `C` (reverse of the list).
6. **What type does `GreeterGrpc::newFutureStub` have when passed as a stub factory?** A `Function<ManagedChannel, Stub>` (a method reference to a static factory).
7. **Why does the encryption interceptor guard `onHalfClose` with a flag?** After it has closed the call for a decrypt failure, forwarding `onHalfClose` would make `UnaryServerCallListener` attempt to run the handler on a call that is already closed (it surfaces as `IllegalStateException`/`MISSING_REQUEST`, not as the handler running with an empty request).
8. **Difference between protobuf `Descriptor` and gRPC `MethodDescriptor`?** Message-type metadata vs RPC-method metadata.


## P2. Resilience: retries, recovery and circuit breakers

When you call another service ([§P1](#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21)), it **will** sometimes be slow or fail. This chapter covers the four tools that keep one bad downstream from taking you down, from simplest to most powerful:

```
 your method ──► [timeout]          "don't wait forever"                 HTTP client / gRPC deadline
            ──► [retry]            "try again on a blip"                Spring Retry, Framework 7, Resilience4j
            ──► [circuit breaker]  "stop calling a service that's down" Resilience4j @CircuitBreaker
            ──► [concurrency cap]  "don't send it 500 calls at once"    @Bulkhead, Framework 7 @ConcurrencyLimit
```

| Library | Status (Nov 2026) | Use it when |
|---|---|---|
| **Spring Retry** (`@EnableRetry`, `@Retryable`, `@Recover`) | ⚠️ **No longer maintained.** Its README says it is archived and superseded by Spring Framework 7 | You're on Boot 2.7/3.x and only need simple retries (most legacy code you'll read) |
| **Spring Framework 7 core** (`@EnableResilientMethods`, `@Retryable`, `@ConcurrencyLimit`) | Built into `spring-context` since 7.0 (Boot 4) | Boot 4: simple retries and concurrency caps, with no extra dependency |
| **Resilience4j** | Active; the industry standard | You need circuit breakers, rate limiters, bulkheads, metrics, or YAML-tunable policies |

🔗 All three are **AOP proxies** around your bean ([§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-), [§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)). So the usual proxy rules apply: a call from another method **in the same class** (`this.charge()`) skips the retry entirely.

### P2.1 [+] Resilience: timeouts, retries, circuit breakers

**Everything above handles the happy path and clean errors. This is what keeps a gateway alive when a downstream misbehaves** — and it's the part most often missing from tutorial code.

⚠️ **The single most important line in this whole section:** **a bare `new RestTemplate()` has no timeouts.** A hung downstream will hold your Tomcat worker thread **forever**. With 200 workers ([§W4.4](03-spring-web.md#w44-tomcat-accepts-the-socket)), 200 slow calls take the entire service down — the classic cascading failure.

```java
@Bean
RestClient paymentClient(RestClient.Builder builder) {
    ClientHttpRequestFactorySettings settings = ClientHttpRequestFactorySettings.DEFAULTS
            .withConnectTimeout(Duration.ofSeconds(2))     // time to establish the TCP connection
            .withReadTimeout(Duration.ofSeconds(5));       // time to wait for the response
    return builder.baseUrl("http://payment-service")
                  .requestFactory(ClientHttpRequestFactories.get(settings))
                  .build();
}
```
⚠️ **Version note:** the snippet above is the **Boot 3.0–3.3** API. `ClientHttpRequestFactories` and the old `org.springframework.boot.web.client.ClientHttpRequestFactorySettings` were deprecated in 3.4 and **removed in Boot 4**. The Boot 4 equivalent:
```java
@Bean
RestClient paymentClient(RestClient.Builder builder) {
    HttpClientSettings settings = HttpClientSettings.defaults()
            .withTimeouts(Duration.ofSeconds(2), Duration.ofSeconds(5));   // connect, read
    return builder.baseUrl("http://payment-service")
                  .requestFactory(ClientHttpRequestFactoryBuilder.detect().build(settings))
                  .build();
}
```
In Boot 4 you can also set the timeouts for every auto-configured client with properties: `spring.http.clients.connect-timeout=2s` and `spring.http.clients.read-timeout=5s`. On Boot 2.7 you set timeouts on the `RestTemplateBuilder` instead: `.setConnectTimeout(...)` / `.setReadTimeout(...)`.
```java
// gRPC: a deadline is per-call and PROPAGATES to downstream services — a genuine advantage over REST
PaymentResponse r = paymentStub
        .withDeadlineAfter(3, TimeUnit.SECONDS)
        .chargeUser(request);
```
💡 **gRPC deadlines propagate automatically through the call graph.** If the gateway sets 3s and calls service A which calls service B, B sees the remaining budget and stops work that can no longer be delivered. There is no REST equivalent without manually forwarding a header.

**Resilience4j** is the standard library (Hystrix is long dead):
```xml
<dependency>
    <groupId>io.github.resilience4j</groupId>
    <artifactId>resilience4j-spring-boot3</artifactId>
</dependency>
```
```java
@CircuitBreaker(name = "payment", fallbackMethod = "paymentFallback")
@Retry(name = "payment")
@Bulkhead(name = "payment")                 // caps concurrent calls to this downstream
// @TimeLimiter(name = "payment")           // ⚠️ NOT on a synchronous method — see the correction below
public PaymentResponse charge(PaymentRequest r) { return paymentApi.charge(r); }

private PaymentResponse paymentFallback(PaymentRequest r, Exception e) {
    log.warn("payment circuit open, queueing", e);
    return PaymentResponse.queued(r.id());
}
```
```yaml
resilience4j:
  circuitbreaker:
    instances:
      payment:
        slidingWindowSize: 100
        failureRateThreshold: 50          # open at 50% failures
        waitDurationInOpenState: 30s
        permittedNumberOfCallsInHalfOpenState: 10
  retry:
    instances:
      payment:
        maxAttempts: 3
        waitDuration: 200ms
        enableExponentialBackoff: true
        retryExceptions: [java.io.IOException, org.springframework.web.client.HttpServerErrorException]
```

📌 **Correction (`@TimeLimiter`):** an earlier version of this example put `@TimeLimiter` on the synchronous `charge(...)` method. Resilience4j's `TimeLimiterAspect` only accepts methods that return a `CompletionStage` (for example `CompletableFuture`) or a reactive type. On a plain return type it throws `IllegalReturnTypeException` ("CompletionStage expected"). For a blocking call, the HTTP client's **read timeout** above is your time limit. Use `@TimeLimiter` like this:
```java
@TimeLimiter(name = "payment")
public CompletableFuture<PaymentResponse> chargeAsync(PaymentRequest r) {
    return CompletableFuture.supplyAsync(() -> paymentApi.charge(r), executor);
}
```
Starter artifacts: `resilience4j-spring-boot2` (Boot 2.7) and `resilience4j-spring-boot3` (Boot 3). Both need `spring-boot-starter-aop` (renamed `spring-boot-starter-aspectj` in Boot 4) and actuator on the classpath. ✅ **Boot 4 has its own starter: `resilience4j-spring-boot4`** (Maven Central, version 2.4.0, the same release as `resilience4j-spring-boot3` 2.4.0). Its POM is built against Spring Boot 4.0 and Framework 7.0. On Boot 4, use the `boot4` artifact, not `boot3`.

⚠️ **Only retry idempotent operations.** Retrying `POST /charge` after a `DEADLINE_EXCEEDED` can charge the customer twice, because the timeout tells you nothing about whether the server finished. The fix is an **idempotency key** on the request — which is exactly why the `@RequestHeader("X-Idempotency-Key")` appears in the worked example in [§W4.17](03-spring-web.md#w417-a-complete-annotated-worked-example).

---


### P2.2 Spring Retry: `@EnableRetry`, `@Retryable`, `@Recover` [+]

> **Your notes:** *"Automatic retry mechanism provided by Spring. We need the `spring-retry` dependency, and `@EnableRetry` on the configuration class. `@Retryable(retryFor = RuntimeException.class, maxAttempts = 4, backoff = @Backoff(delay = 2000, multiplier = 2))` enables exponential backoff. By default, after all retries fail Spring rethrows the error; with `@Recover` we can return something else. These work on AOP."*

Your notes are right. Here is the complete, version-accurate picture.

**Setup (Boot 2.7 / 3.x):**
```xml
<dependency><groupId>org.springframework.retry</groupId><artifactId>spring-retry</artifactId></dependency>
<dependency><groupId>org.springframework.boot</groupId><artifactId>spring-boot-starter-aop</artifactId></dependency> <!-- the annotations need AOP at runtime -->
```
⚠️ **Boot 4 removed dependency management for Spring Retry**, so you must give it an explicit `<version>`. The Boot 4 migration guide recommends moving to Spring Framework's own `@Retryable` instead ([§P2.6](#p26-spring-framework-7--boot-4-native-retryable-enableresilientmethods-and-concurrencylimit-)).

```java
@SpringBootApplication
@EnableRetry                       // once, globally: on the main class or any @Configuration class
public class OrderApplication { ... }

@Service
public class PaymentClientService {

    @Retryable(
        retryFor = { RuntimeException.class, TimeoutException.class },   // ✅ an array: as many types as you like
        maxAttempts = 4,                                                  // ⚠️ counts the FIRST call: 1 call + 3 retries
        backoff = @Backoff(delay = 2000, multiplier = 2))                 // waits 2s, 4s, 8s
    public String callPaymentService(String orderId) { ... }

    @Recover                                   // runs ONLY when all 4 attempts have failed
    public String recover(RuntimeException ex, String orderId) {
        return "Payment queued for later processing";
    }
}
```

**Your questions, answered:**

| Question | Answer |
|---|---|
| *Where do I put `@EnableRetry`, the main class or a configuration class?* | Either. Put it **once** on any `@Configuration` class; `@SpringBootApplication` counts as one. It registers the post-processor that wraps every bean that has `@Retryable` methods in a proxy. You don't put it on each `@Service`. |
| *Can `retryFor` take multiple exception classes?* | Yes, it's an array. `noRetryFor` excludes types. `notRecoverable` lists exceptions that skip `@Recover`. (`retryFor`/`noRetryFor` replaced the older `include`/`exclude`, which are deprecated.) |
| *Defaults?* | `maxAttempts = 3`, **including the first call**. `@Backoff()` with no settings is a **fixed 1000 ms** delay. 📌 **Correction:** the `multiplier` default is **`0`** ("0 = ignored"), not 1. Either way the delay doesn't grow, so you only get exponential backoff by setting `multiplier > 1`. Add `maxDelay` to cap the growth, and `random = true` for jitter. |
| *Is `@Recover` called after a success on attempt 2 or 3?* | **No.** `@Recover` runs only when **every** attempt failed. If attempt 2 succeeds, its result is returned and `@Recover` never runs. |
| *Does one `@Recover` apply to all `@Retryable` methods in the class, or can each method have its own?* | It is matched **per method, by signature**. A `@Recover` method must be in the **same class**, have the **same return type**, take the exception as its **first** parameter, then (optionally) the same arguments in the same order. One `@Recover` can therefore serve several `@Retryable` methods if their signatures line up. When two candidates could match, pin one by name: `@Retryable(recover = "customRecoverMethod")`. |
| *Can some methods have a fallback and others not?* | Yes, with one trap. A `@Retryable` method with no matching `@Recover` normally just rethrows its last exception. ⚠️ But if the class contains **any** `@Recover` method and none matches this method's signature, Spring Retry throws `ExhaustedRetryException("Cannot locate recovery method")` instead (verified in `AnnotationAwareRetryOperationsInterceptor` and `RecoverAnnotationRecoveryHandler`). Keep retry methods that need no fallback in a class without `@Recover` methods, or list their exceptions in `notRecoverable`. |

### P2.3 How `@Retryable` works inside: the AOP chain [+]

> **Your notes:** *"AOP goes through the CGLIB proxy, which delegates to the RetryInterceptor. It intercepts the call and delegates to the RetryTemplate, which has the BackOffPolicy and RetryPolicy extracted from our annotation (or defaults), and loops until success or exhaustion, then calls Recover."*

That's the right model. Here are the actual class names:

```
caller ──► CGLIB proxy of PaymentClientService            (created because of @EnableRetry)
             │
             ▼
   AnnotationAwareRetryOperationsInterceptor   reads @Retryable on THIS method, builds (and caches) a delegate:
             │
             ▼
   RetryOperationsInterceptor ──► RetryTemplate.execute(callback, recoverer)
                                    │  RetryPolicy   : SimpleRetryPolicy(maxAttempts, retryFor/noRetryFor)
                                    │  BackOffPolicy : ExponentialBackOffPolicy(delay, multiplier, maxDelay) or fixed
                                    ▼
                      loop: invocation.proceed() ──► your real method
                            ├─ success        → return result (no @Recover)
                            ├─ retryable fail → backOff.sleep(), try again
                            └─ exhausted      → recoverer = your @Recover method (if one matches), else rethrow
```

⚠️ **It is blocking, and it runs on the caller's thread.** During the backoff the calling thread just waits (Spring Retry's default sleeper uses `Object.wait`). In Spring MVC that's a Tomcat worker sitting idle for 2 s + 4 s + 8 s. Keep `maxAttempts` × delay well below your own caller's timeout, or the retries outlive the request they serve.

### P2.4 Resilience4j retry, and how it differs from Spring Retry [+]

> **Your question:** *"`@Retryable` and `@Recover` run in a single thread and are blocking. In microservices we have better options like Resilience4j. Show me one example of using it for retry and how it differs from the built-in one."*

**Step 1 — configure in `application.yml`** (tunable per environment without recompiling; and if you use Spring Cloud Config, centrally — [§P4](#p4-externalized-configuration-at-scale-spring-cloud-config-and-runtime-refresh)):
```yaml
resilience4j:
  retry:
    instances:
      paymentServiceRetry:
        maxAttempts: 4                     # like Spring Retry: includes the first call
        waitDuration: 2s
        enableExponentialBackoff: true
        exponentialBackoffMultiplier: 2
        retryExceptions:
          - java.lang.RuntimeException
          - java.util.concurrent.TimeoutException
```

**Step 2 — annotate:**
```java
import io.github.resilience4j.retry.annotation.Retry;

@Service
public class PaymentClientService {

    @Retry(name = "paymentServiceRetry", fallbackMethod = "paymentFallback")
    public String processPayment(String orderId) {
        throw new RuntimeException("Payment service unavailable");   // call the downstream here
    }

    // Same signature + ONE extra exception parameter at the END. Same class.
    public String paymentFallback(String orderId, Throwable ex) {
        return "Fallback: payment could not be processed right now for order " + orderId;
    }
}
```
⚠️ **Mirror-image signatures:** Spring Retry's `@Recover` takes the exception **first**; Resilience4j's `fallbackMethod` takes it **last**.

| | Spring Retry | Resilience4j |
|---|---|---|
| Blocking? | Yes: waits on the calling thread | 📌 **Correction:** for a **synchronous** method Resilience4j blocks too (its default wait is `Thread.sleep`). It is non-blocking only when the method returns `CompletableFuture`/`CompletionStage` or a Reactor `Mono`/`Flux`. Picking Resilience4j doesn't make a blocking call non-blocking; the return type does |
| Configuration | Annotation attributes (property placeholders possible via `*Expression` attributes) | YAML per named instance; reloadable with config refresh |
| Scope | Retry (+ a basic `@CircuitBreaker`) | Retry, CircuitBreaker, RateLimiter, Bulkhead, TimeLimiter, Cache |
| Metrics | Manual `RetryListener` | Micrometer metrics + actuator endpoints out of the box |
| Maintenance | ⚠️ Archived; superseded by Framework 7 | Active |

### P2.5 Combining `@Retry` and `@CircuitBreaker`: why the order matters [+]

When a downstream is **completely down**, retrying 4 times on every request just adds latency and load. Retry handles short blips; the circuit breaker stops calling a service that's clearly down.

Stacked Resilience4j annotations wrap the method like an onion. The **default** order, from the Resilience4j docs, is:

```
Retry ( CircuitBreaker ( RateLimiter ( TimeLimiter ( Bulkhead ( yourMethod ) ) ) ) )
outermost ───────────────────────────────────────────────────────────► innermost
```

**With the default order (Retry outside):** each retry attempt passes through the breaker, so the breaker records **every attempt** as a call. Three failed attempts count as three failures, which opens the breaker faster. Once it is OPEN, the breaker throws `CallNotPermittedException`.
⚠️ **The trap:** if your retry config retries *all* exceptions, Retry keeps "retrying" against an open breaker, adding pointless waits. Add `io.github.resilience4j.circuitbreaker.CallNotPermittedException` to the retry instance's `ignoreExceptions`, or flip the order.

**To put the breaker outside** (so one logical call counts once, and an open breaker fails immediately with no retries), set aspect orders. **Higher value = higher priority = outer layer** (quoted from the docs):
```yaml
resilience4j:
  circuitbreaker:
    circuitBreakerAspectOrder: 2     # outer
    instances:
      paymentCB:
        slidingWindowSize: 10
        failureRateThreshold: 50
        waitDurationInOpenState: 10s
  retry:
    retryAspectOrder: 1              # inner
    instances:
      paymentRetry:
        maxAttempts: 3
        waitDuration: 1s
```
```java
@CircuitBreaker(name = "paymentCB", fallbackMethod = "paymentFallback")   // fallback on the OUTER layer
@Retry(name = "paymentRetry")                                            //   catches failures of both layers
public String processPayment(String orderId) { return restClient.post()...; }

public String paymentFallback(String orderId, Throwable ex) {
    return "Fallback: payment service is currently unavailable for order " + orderId;
}
```
Annotation order in the **source** doesn't matter; only the aspect-order properties do (the same rule as for any Spring annotations — [§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-)).

### P2.6 Spring Framework 7 / Boot 4: native `@Retryable`, `@EnableResilientMethods` and `@ConcurrencyLimit` [+]

Since **Framework 7.0** (Boot 4), retry is part of core Spring (`spring-context`). No extra dependency is needed. Everything below is verified against the Framework 7 reference, "Resilience Features".

```java
import org.springframework.resilience.annotation.EnableResilientMethods;
import org.springframework.resilience.annotation.Retryable;
import org.springframework.resilience.annotation.ConcurrencyLimit;

@SpringBootApplication
@EnableResilientMethods            // replaces @EnableRetry (or declare RetryAnnotationBeanPostProcessor /
public class OrderApplication { }  //  ConcurrencyLimitBeanPostProcessor beans individually)

@Service
public class PaymentClientService {

    @Retryable(
        includes = { RuntimeException.class, TimeoutException.class },   // `excludes` narrows; nested causes match too
        maxRetries = 3,      // ⚠️ RETRIES after the first call: up to 1 + 3 = 4 executions
        delay = 1000,        // ms before the first retry (default 1 s)
        multiplier = 2.0,    // 1s, 2s, 4s
        maxDelay = 5000,     // cap on the delay
        jitter = 200)        // random variation, against thundering herds
    public String processPayment(String orderId) { return restClient.post()...; }

    @ConcurrencyLimit(10)  // at most 10 threads inside this method at once; others block until a slot frees
    public Report heavyReport() { ... }
}
```

| | Spring Retry (old library) | Framework 7 core |
|---|---|---|
| Enable | `@EnableRetry` | `@EnableResilientMethods` |
| Exception filter | `retryFor` / `noRetryFor` | `includes` / `excludes` (+ `predicate`); `@Retryable(Foo.class)` is shorthand for `includes` |
| Count | `maxAttempts = 3` **includes** the first call | `maxRetries = 3` **excludes** it, so 4 total. ⚠️ Easy to get off by one when migrating |
| Default | 3 attempts, 1 s fixed | 3 retries, 1 s delay, any exception |
| After exhaustion | `@Recover` method | **No `@Recover`.** The **last original exception** propagates. Handle it with `try/catch` or `@RestControllerAdvice` ([§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling)) |
| Reactive | ❌ | ✅ a `Mono`/`Flux` return value is decorated with Reactor retry |
| Observability | `RetryListener` | a `MethodRetryEvent` is published for every exception (the caller only sees the last one) |
| Programmatic | `RetryTemplate` (spring-retry) | `org.springframework.core.retry.RetryTemplate` + `RetryPolicy.builder()` |

Programmatic form, for when a whole block (not a method) should retry:
```java
var retryTemplate = new RetryTemplate(RetryPolicy.builder()
        .includes(MessageDeliveryException.class)
        .maxRetries(4).delay(Duration.ofMillis(100)).multiplier(2).maxDelay(Duration.ofSeconds(1))
        .build());
retryTemplate.invoke(() -> client.send(...));   // invoke(): rethrows the last exception
                                                // execute(): throws checked RetryException with all attempts
```

**`@ConcurrencyLimit`** acts like a pool-size limit on a single method. It matters most with **virtual threads**, where there is no thread-pool limit to protect a fragile downstream ([§J6](01-java.md#j6-concurrency-and-multithreading-q2q9), [§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads)). `@ConcurrencyLimit(1)` effectively locks the bean method. Several attributes have `String` variants (`limitString`, and similar ones on `@Retryable`) for `${...}` placeholders.

**Combined with `@Async`:** the async advice is applied **outermost**, so all retry attempts run on the async executor's thread, not the caller's.

### P2.7 Which one should I use? [+]

| Situation | Choose |
|---|---|
| Boot 2.7, simple retry of one call | Spring Retry, or Resilience4j if circuit breaking is needed |
| Boot 4, simple retry / concurrency cap | Framework 7 `@Retryable` / `@ConcurrencyLimit` |
| Any version, calling a service that can be **down for minutes** | Resilience4j `@CircuitBreaker` (+ `@Retry`, breaker outside) |
| A gRPC client inside a service on an in-house platform framework | gRPC deadlines + the platform's client config first ([§P1](#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21)); annotation retries only for idempotent calls |

And always: **timeouts first**, retry only **idempotent** operations (or use an idempotency key), and cap the total retry time below your caller's deadline.

---


## P3. Background work: @Scheduled and @Async

Some work isn't triggered by an HTTP request: a nightly cleanup, a sync every 5 minutes, an email that shouldn't make the user wait. Spring has two annotations for this, and both are **AOP-style infrastructure enabled by an `@Enable…` switch** ([§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-)):

| | `@Scheduled` | `@Async` |
|---|---|---|
| Who triggers it | **A clock** (rate, delay, cron) | **Your code calls it**, and it returns immediately |
| Enable with | `@EnableScheduling` | `@EnableAsync` |
| Runs on | the **TaskScheduler** (Boot: 1 thread by default) | the **TaskExecutor** (Boot: 8-core-thread pool by default) |
| Arguments allowed | ❌ none | ✅ any |
| 🐍 / 🟨 equivalent | APScheduler / Celery beat; `node-cron` | `asyncio.create_task`/`BackgroundTasks`; fire-and-forget promise or a worker queue |

### P3.1 Enabling scheduling [+]

> **Your learning:** *"Spring Boot scheduling lets you run background tasks automatically at fixed intervals or specific times using `@EnableScheduling` and `@Scheduled`. It is built into the core `spring-boot-starter`, so no extra libraries are needed."*

Correct. The scheduling support lives in `spring-context`, which every starter brings in. Add `@EnableScheduling` once, on the main class or any `@Configuration` class. Without it, `@Scheduled` annotations are silently ignored.

```java
@SpringBootApplication
@EnableScheduling
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```

### P3.2 Writing scheduled tasks, and the four trigger types [+]

Annotate methods of a **Spring bean** (`@Component`, `@Service`, …) with `@Scheduled`. The method must take **no arguments**; it needs data, so inject collaborators into the bean ([§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13)). It is normally `void`. Since Framework 6.1 it may also return a reactive `Publisher` (Mono/Flux), whose emitted values are ignored. `@Scheduled` works on beans of any scope.

```java
@Component
public class ScheduledTasks {

    // Starts every 5 s, measured START to START
    @Scheduled(fixedRate = 5000)
    public void runAtFixedRate() {
        System.out.println("Fixed rate task executed");
    }

    // Waits 10 s after startup, then each run starts 5 s AFTER the previous one FINISHED
    @Scheduled(fixedDelay = 5000, initialDelay = 10000)
    public void runWithFixedDelay() {
        System.out.println("Fixed delay task executed after 10s initial wait");
    }

    // Every day at 10:30:00, Kolkata time
    @Scheduled(cron = "0 30 10 * * ?", zone = "Asia/Kolkata")
    public void runWithCron() {
        System.out.println("Cron task executed");
    }

    // Units other than ms (Framework 5.3.10+)
    @Scheduled(fixedRate = 5, timeUnit = TimeUnit.MINUTES)
    public void everyFiveMinutes() { ... }
}
```

```
fixedRate = 5s, task takes 2s          fixedDelay = 5s, task takes 2s
 |██|...|██|...|██|                     |██|.....|██|.....|██|
 0  2   5  7  10 12                     0  2     7  9    14 16
 start→start = 5s                       end→start = 5s

fixedRate = 5s, task takes 7s (default single-thread scheduler)
 |███████|███████|███████|     next run starts LATE, right after the previous ends — never overlaps
 0       7      14
```

| Trigger | Meaning |
|---|---|
| `fixedRate` | Interval measured between successive **start** times. 📌 **Correction:** the pasted note said slow runs "may queue up or overlap". With the default `ThreadPoolTaskScheduler`, the **same task never overlaps itself**. It is backed by `ScheduledExecutorService.scheduleAtFixedRate`, whose Javadoc says executions "may start late, but will not concurrently execute". Missed ticks start back-to-back once the slow run ends. ⚠️ Not true with virtual threads enabled; see the nuance below. |
| `fixedDelay` | Interval measured from the **completion** of the previous run to the next start. Never overlaps, even under load. Use it for "poll, process, then wait". |
| `initialDelay` | Wait before the **first** `fixedRate`/`fixedDelay` run (and for a one-time task with only `initialDelay`, Framework 6.1+). |
| `cron` | 6 fields, Spring style: `second minute hour day-of-month month day-of-week`. ⚠️ Unix cron has 5 fields with **no** seconds, so a pasted crontab line is off by one field. `?` = "no specific value" in day-of-month/day-of-week. Macros: `@hourly`, `@daily`/`@midnight`, `@weekly`, `@monthly`, `@yearly`. `zone` sets the time zone (default: the server's zone). |

⚠️ **Virtual-thread nuance:** with `spring.threads.virtual.enabled=true` (Boot 3.2+, Java 21+), Boot switches to `SimpleAsyncTaskScheduler`, which runs **each execution on a new virtual thread**. Its Javadoc says fixed-**delay** tasks are still serialized on the single scheduler thread. ✅ **A slow fixed-rate run *can* overlap the next one.** The Javadoc doesn't say so, but the Framework 7.0.9 source shows it. `scheduleAtFixedRate` gives the trigger executor a runnable, `scheduledTask(task)`, that only calls `execute(...)`. That hands the real work to a new thread and returns at once, so the single scheduler thread never waits for the task to finish. Concurrency is unlimited unless you set `spring.task.scheduling.simple.concurrency-limit`, which Boot passes to the builder. Use `fixedDelay` (or a concurrency limit, or a lock) when overlap would be harmful.

### P3.3 The scheduler thread pool, and why one slow task delays the rest [+]

> **Your learning:** *"By default Spring executes all `@Scheduled` tasks sequentially on a single thread. If one task hangs, other scheduled tasks will be delayed."*

True, and it's the #1 scheduling surprise. Boot auto-configures a `ThreadPoolTaskScheduler` with **one thread** when `@EnableScheduling` is present and you haven't defined your own scheduler. That is so on Boot 2.7, 3.x and 4.x unless virtual threads are on.

```
   scheduling-1:  [reportJob ███████████ hangs …]
   cleanupJob due at 10:00 → waits    syncJob due at 10:01 → waits      ← all share ONE thread
```

```properties
spring.task.scheduling.pool.size=5                  # 5 tasks can run at the same time
spring.task.scheduling.thread-name-prefix=sched-    # makes thread dumps readable
```
With virtual threads enabled, the scheduler is a `SimpleAsyncTaskScheduler` and **ignores the pool properties**.

### P3.4 Externalizing intervals [+]

Every attribute has a `String` twin that accepts `${...}` placeholders, so intervals live in configuration ([§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12)) instead of code:

```properties
app.sync.rate=5000
app.cleanup.cron=0 0 2 * * *
app.sync.initial=PT30S
```
```java
@Scheduled(fixedRateString = "${app.sync.rate}", initialDelayString = "${app.sync.initial}")
public void sync() { ... }

@Scheduled(cron = "${app.cleanup.cron}")       // `cron` is already a String
public void cleanup() { ... }
```
The `…String` attributes also accept `java.time.Duration` formats such as `PT30S`. Setting `cron = "-"` disables a task (handy as a per-environment off switch: `app.cleanup.cron=-`).

### P3.5 `@Async`: running any method on another thread [+]

> **Your question:** *"Does `@EnableAsync` only enable async processing for the event listeners, or is it applicable to other functions too, so they run in a separate thread without manually writing the logic?"*

📌 **It applies to every Spring bean method**, not just event listeners. `@EnableAsync` turns on a post-processor that wraps any bean having `@Async` methods in a proxy. Calling such a method **submits the call as a task to a `TaskExecutor` and returns to the caller immediately**. Event listeners are just one place you'll see it ([§C7](02-spring-core.md#c7-spring-application-events)).

```java
@Configuration
@EnableAsync
class AsyncConfig { }

@Service
public class ReportService {

    @Async                                             // fire-and-forget
    public void sendWelcomeEmail(String to) { ... }

    @Async                                             // the caller gets a future and can wait or compose
    public CompletableFuture<Report> build(long id) {
        return CompletableFuture.completedFuture(heavyWork(id));
    }

    @Async("reportExecutor")                           // a specific Executor bean (by name or qualifier)
    public void exportCsv() { ... }
}
```

**The rules (verified against the Framework reference):**

| Rule | Detail |
|---|---|
| Return types | `void`, or a `Future` type: `Future`, `CompletableFuture` (🔗 [§J7](01-java.md#j7-completablefuture-thenapply-thencompose-exceptionally-q)). Anything else can't carry the result back. |
| Exceptions | With `Future`, the exception surfaces when the caller calls `get()`/`join()`. With **`void` it can't reach the caller**: by default it is **only logged**. Register an `AsyncUncaughtExceptionHandler` (implement `AsyncConfigurer.getAsyncUncaughtExceptionHandler()`) to do more. ⚠️ `@RestControllerAdvice` never sees these exceptions: the HTTP request has usually already returned. |
| Self-invocation | Default advice mode is **proxy**, so `this.sendWelcomeEmail()` from the same class runs **synchronously** on the caller's thread. Call it from another bean, or switch to `mode = AdviceMode.ASPECTJ` with weaving ([§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)). |
| Lifecycle callbacks | ❌ Can't be combined with `@PostConstruct`. Call the async method from another bean once startup is done. |
| With `@Retryable` (Framework 7) | Async is applied outermost, so all retry attempts run on the executor thread. |

**Which executor runs it?** In Boot, if you haven't defined an `Executor` bean, Boot auto-configures `applicationTaskExecutor`:
- **Platform threads:** a `ThreadPoolTaskExecutor` with **8 core threads**. Tune it with `spring.task.execution.pool.max-size`, `queue-capacity` and `keep-alive`. ⚠️ With the default unbounded queue, the pool never grows beyond the core size, so set `queue-capacity` if you want `max-size` to mean anything.
- **Virtual threads** (`spring.threads.virtual.enabled=true`): a `SimpleAsyncTaskExecutor` that starts a new virtual thread per task, with no pool.

A bean named `taskExecutor`, a `@Primary` executor, or an `AsyncConfigurer` takes precedence.

🔗 **Request context doesn't follow the task.** `@Async` code runs on another thread, so `ThreadLocal`-based state is missing there: `SecurityContextHolder`, `RequestContextHolder`, the MDC log fields, and the current `@Transactional` transaction. See [§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder) and [§J6](01-java.md#j6-concurrency-and-multithreading-q2q9). Use a `TaskDecorator` to copy what you need. Boot applies any `TaskDecorator` bean to its auto-configured executor. On Boot 4.1+, `spring.task.execution.propagate-context=true` registers a `ContextPropagatingTaskDecorator` for you; it needs Micrometer `context-propagation`. See the tracing note in [§P5](#p5-production-grade-concerns-).

### P3.6 `@Scheduled` + `@Async`: allowing overlapping runs [+]

> **Your learning:** *"Combine `@EnableAsync` with `@Async` on the scheduled method if a single fixedRate job needs to run overlapping instances in parallel."*

Correct, and it's the **only** standard way to make a fixed-rate job overlap itself on the default scheduler. The scheduler thread only *submits* the call to the async executor, so each tick starts on time no matter how long the previous run takes:

```java
@Async
@Scheduled(fixedRate = 1000)
public void pollQueue() { ... }   // a 3s run no longer delays the next tick; up to ~3 run concurrently
```
⚠️ Overlap means the job must be **thread-safe and idempotent**, and the executor's queue can grow without bound if runs are consistently slower than the rate.

### P3.7 Production gotchas [+]

- ⚠️ **Every instance runs every schedule.** With 6 pods, a nightly `@Scheduled` job runs **6 times**. Spring has no cluster coordination. Use a lock (e.g. **ShedLock** with a DB/Redis lock table, or Quartz in clustered JDBC mode), leader election, or move the job to a single-instance worker / Kubernetes `CronJob`.
- ⚠️ **Exceptions don't stop the schedule.** An exception in a `@Scheduled` run is logged by the scheduler's `ErrorHandler` and the next tick runs normally. You **won't** notice unless you add logging/metrics; a silently failing job is common.
- **Shutdown:** by default in-flight tasks are interrupted. Set `spring.task.scheduling.shutdown.await-termination=true` (with `…await-termination-period`) if a job must finish. Boot's graceful shutdown covers the web server, not your jobs.
- **Observability:** Boot's actuator `/actuator/scheduledtasks` lists every scheduled task and its trigger.

---



## P4. Externalized configuration at scale: Spring Cloud Config and runtime refresh

🔗 Builds on [§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12), which covers `@Value`, `@ConfigurationProperties`, profiles and precedence inside **one** application. This chapter is about **many** services sharing configuration and changing it **without a redeploy**.

### P4.1 The problem it solves [+]

> **Your learning:** *"Suppose one service depends on the payment service, so the payment-service URL is in its `application.properties`/`application.yml`. If the payment service changes its URL, we need code changes and a redeploy of every service that uses it."*

```
 BEFORE: config baked into every JAR             AFTER: one source of truth
 ┌───────────┐ ┌───────────┐ ┌───────────┐       ┌──────────────┐    ┌───────────────┐    ┌────────────┐
 │ order-svc │ │ cart-svc  │ │ notif-svc │       │ order-svc    │──► │ Config Server │──► │ Git repo / │
 │ payment.  │ │ payment.  │ │ payment.  │       │ cart-svc     │──► │ (Spring Boot  │    │ Vault /    │
 │ url=...   │ │ url=...   │ │ url=...   │       │ notif-svc    │──► │  app, HTTP)   │    │ AWS SSM …  │
 └───────────┘ └───────────┘ └───────────┘       └──────────────┘    └───────────────┘    └────────────┘
  change URL → rebuild + redeploy ×3              change one file in Git → clients pick it up
```

Beyond URLs, it gives you:
- **One place per environment:** `payment-service-prod.yml` vs `-dev.yml`, selected by the client's active profile.
- **An audit trail:** with a Git backend, every change has a commit, an author and a revert.
- **Secrets kept out of the codebase:** use a Vault / AWS backend, or the server's `{cipher}` encryption.
- **Runtime refresh** without a restart ([§P4.3](#p43-the-stale-config-problem-and-actuatorrefresh-)).

💡 **For the specific "a service's URL changed" problem, service discovery is the better tool** (Kubernetes DNS/Services, Eureka, Consul, or a service mesh routing by service name). Clients address `payment-service` by **name** and discovery resolves where it lives. Spring Cloud Config is best for *settings*: timeouts, feature toggles, thresholds, pool sizes, credentials.

🐍/🟨 The closest analogy is a shared `.env` that every service fetches over HTTP at boot, plus a "reload now" button. Python/Node have no standard equivalent; teams usually use Consul/etcd or AWS SSM directly.

### P4.2 Config Server and Config Client [+]

> **Your learning:** *"It externalizes and centralizes the configuration. The services fetch config from an external service, but that external service doesn't store config in its own `application.properties` either (else we'd redeploy it); it fetches from a common place like GitHub. Two components: config server and config client."*

Exactly right: client → server → storage.

**The server** is a small, separate Spring Boot app:
```java
@SpringBootApplication
@EnableConfigServer                    // dependency: spring-cloud-config-server
public class ConfigServerApplication { ... }
```
```yaml
server.port: 8888                      # 8888 is the convention; clients default to http://localhost:8888
spring.cloud.config.server.git.uri: https://github.com/acme/config-repo
```
It serves `GET /{application}/{profile}[/{label}]`, e.g. `/payment-service/prod/main`, by merging `application.yml` + `payment-service.yml` + `payment-service-prod.yml` from the repo.

**The client** is every microservice (dependency `spring-cloud-starter-config`):
```yaml
spring:
  application.name: order-service        # selects order-service*.yml in the repo
  config.import: "optional:configserver:http://config-server:8888"
```
- `optional:` means: start anyway if the server is unreachable. Without `optional:` the client **fails fast** at startup. That's often what you want in production, combined with retry (`spring-retry` + AOP on the classpath; defaults: 6 attempts, 1 s initial, ×1.1).
- **Legacy (Spring Cloud before 2020.0 style):** a `bootstrap.yml` with `spring.cloud.config.uri`. This now only works if you add `spring-cloud-starter-bootstrap` or set `spring.cloud.bootstrap.enabled=true` (as a system property or env var). With `spring.config.import`, no bootstrap file is needed. You'll see `bootstrap.yml` in older codebases.

Startup flow:
```
order-service boots
  └─► Config Data loader sees spring.config.import=configserver:…
        └─► GET http://config-server:8888/order-service/prod
              └─► server reads Git (clones/pulls), returns property sources
  └─► properties added to the Environment ──► beans created with these values
```

### P4.3 The stale-config problem, and `/actuator/refresh` [+]

> **Your learning:** *"If we change the config in the common place, the server has the new value, but by default the client fetches only at startup, so it has stale data. For this we have actuator refresh: an API we call, which calls the config server and updates the client. Not all beans are refreshed — only `@RefreshScope` ones."*
>
> **Your questions:** *"Does it poll, or does the server use a webhook to keep clients updated? In actuator refresh we still need to make the API call — or is this automated?"*

**Answer:** out of the box it **neither polls nor pushes**. The config client fetches once at startup. Something must tell each instance to re-fetch: a human, a CI job, or the automation in [§P4.4](#p44-automating-refresh-spring-cloud-bus-and-the-monitor-webhook-).

**Enable the endpoint** (it isn't exposed over HTTP by default; needs `spring-boot-starter-actuator`):
```yaml
management.endpoints.web.exposure.include: refresh
```
```bash
curl -X POST http://order-service:8080/actuator/refresh     # returns the list of keys that changed
```

What a refresh does, without restarting the JVM:
1. Re-fetches the property sources from the config server and updates the `Environment`.
2. Publishes an `EnvironmentChangeEvent` with the changed keys. On that event, Spring Cloud **rebinds `@ConfigurationProperties` beans** and re-applies `logging.level.*`.
3. **Clears the `@RefreshScope` cache.** Those beans are lazy proxies, so the next method call builds a fresh instance with the new values.

📌 **Refining "only `@RefreshScope` beans are refreshed":**

| Bean style | Picks up new values on refresh? |
|---|---|
| Field/constructor with `@Value("${…}")` in a normal singleton | ❌ The value was copied once at creation. Put `@RefreshScope` on that bean. |
| `@RefreshScope` bean | ✅ Recreated on the next call after the refresh. |
| Mutable `@ConfigurationProperties` (setters) | ✅ **Even without `@RefreshScope`.** The same instance is rebound **in place**: reset to its class defaults, then re-bound. Anyone holding a reference sees the new values. |
| Immutable `@ConfigurationProperties` (constructor binding / **Java records**) | ❌ The Spring Cloud Commons docs: *"Objects using constructor binding including Java Records annotated with `@ConfigurationProperties` cannot be refreshed."* Use `@RefreshScope` on the bean or list it in `spring.cloud.refresh.extra-refreshable`. |
| `HikariDataSource` | ❌ In the default `spring.cloud.refresh.never-refreshable` list. Pool changes need a restart. |
| `server.port`, anything read only at startup | ❌ Restart. |

⚠️ An in-place rebind is **not atomic**: another thread can observe a half-updated bean during the refresh. If you need a consistent snapshot across several properties, use `@RefreshScope`. 🔗 See [§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12) for `@ConfigurationProperties` itself.

### P4.4 Automating refresh: Spring Cloud Bus and the `/monitor` webhook [+]

Calling `/actuator/refresh` on 40 pods by hand doesn't scale. There are three levels:

| Level | How it works | Good for |
|---|---|---|
| **1. Manual, per instance**: `POST /actuator/refresh` | You (or a script) call every instance | Local dev, 1–2 instances |
| **2. Broadcast**: `POST /actuator/busrefresh` | Config server **and** clients join **Spring Cloud Bus** over a broker (`spring-cloud-starter-bus-amqp` for RabbitMQ or `…-bus-kafka`). One call to `/actuator/busrefresh` on any member (expose `busrefresh`) broadcasts a refresh event; every instance clears its refresh scope and rebinds `@ConfigurationProperties` | Production, with a human or CI pressing one button |
| **3. Zero-touch**: Git webhook → `/monitor` | Add `spring-cloud-config-monitor` + the bus to the **config server**. Configure your Git host (GitHub, GitLab, Bitbucket, Gitea, Gitee, Gogs) to POST its push webhook to `/monitor`. The server works out which files changed and sends a `RefreshRemoteApplicationEvent` over the bus **only to the affected apps**: `payment-service.yml` targets `payment-service`; `application.yml` targets everyone | Fully hands-off pipelines |

```
dev: git push payment-service.yml
   └─► GitHub webhook ──POST /monitor──► Config Server ──RefreshRemoteApplicationEvent──► Kafka/RabbitMQ
                                                                                        ├─► payment-service #1 refresh
                                                                                        ├─► payment-service #2 refresh
                                                                                        └─► (other apps ignore it)
```
⚠️ Configure a webhook secret. Per the docs, with no secrets configured the `/monitor` endpoint **rejects all** webhook requests.

### P4.5 With AWS Parameter Store / Secrets Manager [+]

> **Your question:** *"How is actuator/refresh helpful when we use AWS Parameter Store / Secrets Manager?"*

There are two architectures:

**A. Directly from AWS with Spring Cloud AWS (no config server).** This is common in AWS-native shops.
```properties
spring.config.import=optional:aws-parameterstore:/config/order-service/;optional:aws-secretsmanager:/secrets/order-db
```
- The values are read at startup, like a config client. `/actuator/refresh` re-reads them and applies the same `@RefreshScope` / `@ConfigurationProperties` rules as in [§P4.3](#p43-the-stale-config-problem-and-actuatorrefresh-).
- Spring Cloud AWS 3.x also has **built-in polling reload**, disabled by default (needs `spring-boot-starter-actuator`, `spring-cloud-commons` and `spring-cloud-context`):
  ```properties
  spring.cloud.aws.secretsmanager.reload.strategy=refresh      # or restart_context (needs the restart endpoint exposed)
  spring.cloud.aws.secretsmanager.reload.period=1m
  spring.cloud.aws.parameterstore.reload.strategy=refresh
  spring.cloud.aws.parameterstore.reload.period=1m
  ```
  `refresh` reloads `@ConfigurationProperties` and `@RefreshScope` beans; `restart_context` gracefully restarts the whole context. (The 3.4 reference is inconsistent about the default period, `15s` in the table vs "1 minute" in the prose, so set it explicitly.)
- This is how **secret rotation** works without downtime. Secrets Manager rotates a DB password, the poller (or a Lambda calling `/actuator/refresh`) picks it up, and refreshable beans use the new value. ⚠️ The default `HikariDataSource` is **never-refreshable**, so a rotated DB password needs a pool that re-reads credentials, or a dual-credential rotation strategy plus a rolling restart. ✅ Verified facts:
- The Spring Cloud Commons docs say a `HikariDataSource` *"can not be refreshed"*. It is the default value of `spring.cloud.refresh.never-refreshable`.
- HikariCP itself can change credentials at runtime: `HikariConfigMXBean.setPassword`/`setUsername`, plus the atomic `setCredentials` since 6.0. The Javadoc says these apply **to new connections only**, and *"only work for DataSource-based connections, not Driver-class or JDBC URL-based connections"*.
- HikariCP **7.0** adds a `HikariCredentialsProvider`.
- Versions: Boot 2.7.18 manages HikariCP **4.0.3**, which has none of the 6.0/7.0 APIs. Boot 4.1.1 manages **7.0.2**.
- Which mechanism fits your DB and secret store is a design decision. Agree it with the DB team.

**B. A Config Server with an AWS backend.** The server reads SSM/Secrets Manager live on every client request, but **clients still cache** until refreshed. AWS has no Git-style push webhook into Spring, so teams wire **EventBridge** (it emits events on parameter/secret changes) → a small Lambda → `POST /actuator/busrefresh`.

⚠️ **Cost and limits:** polling every few seconds from hundreds of pods hits AWS API rate limits and costs money. Prefer a period of minutes, or event-driven refresh.

### P4.6 Summary [+]

```
change ──► where it lives        ──► how clients learn            ──► what actually changes in the JVM
          Git / Vault / AWS SSM      startup fetch (always)            Environment updated
                                     /actuator/refresh (manual)        @ConfigurationProperties (mutable) rebound in place
                                     /actuator/busrefresh (broadcast)  @RefreshScope beans recreated on next call
                                     /monitor webhook (automatic)      plain @Value singletons: NOT changed
                                     Spring Cloud AWS reload (polling) records / DataSource / server.port: restart
```

---


## P5. Production-grade concerns [+]

> **Nothing in this section came from your chats.** It is the set of things that separate a tutorial application from a service you can actually operate — and the things you'll be asked about in code review. Every item maps to a habit you already have from FastAPI or Express; the Java spelling is just different.

### P5.1 Project structure

```
src/main/java/com/example/orders/
├── OrdersApplication.java          ← @SpringBootApplication (the ROOT package — see §C1)
├── config/                         ← @Configuration classes, @ConfigurationProperties records
├── web/                            ← @RestController, @RestControllerAdvice
│   └── dto/                        ← request/response records — the API contract
├── service/                        ← business logic, @Transactional boundaries
├── domain/                         ← entities / aggregates, domain exceptions
├── repository/                     ← Spring Data interfaces
└── client/                         ← @HttpExchange interfaces, gRPC stubs, downstream DTOs
```
⚠️ **Every package must sit under the `@SpringBootApplication` class's package**, or component scanning won't find it ([§C1](02-spring-core.md#c1-the-spring-boot-mental-model-and-auto-configuration-q47-)). Putting the main class in `com.example` and a controller in `com.other` produces a silent 404 that takes an hour to diagnose.

💡 **Package by feature, not by layer, once the service grows past ~15 classes:** `orders/`, `payments/`, `pricing/` — each with its own `web`/`service`/`repository`. Related code changes together, and the compiler can enforce module boundaries. This is also the natural shape for hexagonal architecture ([§W3.9](03-spring-web.md#w39-hexagonal-architecture-ports-and-adapters-q49)).

### P5.2 DTOs vs entities — never expose your entities [+]

**This is the single highest-value habit in this document.** It has come up in [§W6.11](03-spring-web.md#w611--mass-assignment-the-vulnerability-initbinder-actually-defends-against), [§D5.8](04-spring-data.md#d58-projections-vs-dtos-q31) and [§S2.5](05-spring-security.md#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39) — here is the consolidated case.

```java
// ❌ NEVER do this
@RestController
public class UserController {
    @PostMapping("/users")
    public User create(@RequestBody User user) { return repo.save(user); }   // User is a JPA @Entity
}
```

**Six concrete failures, not stylistic objections:**

| # | Problem |
|---|---|
| 1 | **Mass assignment.** A client can `POST {"role":"ADMIN","credits":999999,"id":1}`. Every column is a settable property. |
| 2 | **Data leakage.** `passwordHash`, `internalNotes`, `deletedAt` are serialized to the client by default. |
| 3 | **Your DB schema becomes your public API.** Rename a column → every client breaks. There is no anti-corruption layer. |
| 4 | **Lazy-loading explosions.** Jackson touches a lazy association during serialization → `LazyInitializationException`, or an accidental N+1 that loads the whole object graph. |
| 5 | **Infinite recursion.** A bidirectional `@OneToMany`/`@ManyToOne` serializes forever → `StackOverflowError`. (`@JsonIgnore`/`@JsonManagedReference` patch it; a DTO removes the problem.) |
| 6 | **You cannot version the API** independently of the schema. |

```java
// ✅ Records as DTOs — immutable, no setters, nothing to mass-assign
public record CreateUserRequest(@NotBlank String email, @NotBlank String displayName) {}
public record UserResponse(Long id, String email, String displayName, Instant createdAt) {
    static UserResponse from(User e) {
        return new UserResponse(e.getId(), e.getEmail(), e.getDisplayName(), e.getCreatedAt());
    }
}

@PostMapping("/users")
@ResponseStatus(HttpStatus.CREATED)
public UserResponse create(@Valid @RequestBody CreateUserRequest req) {
    return UserResponse.from(service.create(req));
}
```
💡 **Mapping options:** a static factory like `from()` (explicit, zero dependencies, ✅ fine up to a few dozen DTOs), **MapStruct** (compile-time generated, fast, type-safe, ✅ the standard at scale), or **ModelMapper** (⚠️ reflection-based, silently mismaps on rename — avoid).

🐍🟨 The exact same discipline as *"never return your SQLAlchemy model — return a Pydantic response model"* and *"never `res.json(mongooseDoc)`."* You already have this instinct; Java just makes the failure modes worse because serialization is automatic and reflective.

### P5.3 Testing [+]

| Annotation | Loads | Speed | For |
|---|---|---|---|
| *(none)* + Mockito | nothing | ⚡ ms | pure unit tests of services |
| `@WebMvcTest(OrderController.class)` | the web layer only — controller, converters, validation, security | fast | controller tests, with `@MockitoBean` services |
| `@DataJpaTest` | JPA + an embedded/Testcontainers DB | medium | repository and query tests |
| `@SpringBootTest` | **the whole context** | slow | end-to-end / component tests |

```java
// Unit test — no Spring at all. Should be the overwhelming majority.
@ExtendWith(MockitoExtension.class)
class OrderServiceTest {
    @Mock OrderRepository repo;
    @InjectMocks OrderService service;

    @Test
    void rejectsEmptyCart() {
        assertThatThrownBy(() -> service.create(new CreateOrderRequest("c-1", List.of())))
            .isInstanceOf(EmptyCartException.class);
    }
}
```
```java
// Web-layer test — real JSON serialization, real validation, real status codes, mocked service
@WebMvcTest(OrderController.class)
class OrderControllerTest {
    @Autowired MockMvc mvc;
    @MockitoBean OrderService service;              // ⚠️ @MockBean is DEPRECATED since Boot 3.4 (on Boot 2.7, @MockBean is still the one to use)

    @Test
    void returns400WhenCustomerIdBlank() throws Exception {
        mvc.perform(post("/api/v1/orders").contentType(APPLICATION_JSON)
                .content("""
                    {"customerId":"", "items":[{"sku":"A","qty":1}]}
                    """))                           // ← text blocks make JSON fixtures readable
           .andExpect(status().isBadRequest())
           .andExpect(jsonPath("$.errors.customerId").exists());
    }
}
```
```java
// Integration test with a REAL database via Testcontainers — ✅ the modern standard
@SpringBootTest(webEnvironment = RANDOM_PORT)
@Testcontainers
class OrderIntegrationTest {
    @Container @ServiceConnection                   // ✅ Boot 3.1+ wires the datasource automatically
    static PostgreSQLContainer<?> db = new PostgreSQLContainer<>("postgres:16");

    @Autowired TestRestTemplate rest;
}
```
💡 **`@ServiceConnection` removed the worst part of Testcontainers** — no more `@DynamicPropertySource` boilerplate to inject the JDBC URL. Use a **real Postgres** rather than H2: H2 accepts SQL that Postgres rejects, so H2-green/prod-red is a real and common failure.

⚠️ **Every distinct `@SpringBootTest` configuration starts a new application context** (~2–10s each). Spring caches contexts keyed by configuration, so keeping them identical across test classes is the difference between a 30-second and a 12-minute suite.

🟨🐍 `MockMvc` ↔ `supertest` ↔ FastAPI's `TestClient`. Testcontainers ↔ `docker-compose` in CI, but managed from the test itself.

### P5.4 Actuator: health, metrics [+]

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>
```
```properties
management.endpoints.web.exposure.include=health,info,metrics,prometheus
management.endpoint.health.show-details=when-authorized
management.endpoint.health.probes.enabled=true       # /health/liveness and /health/readiness
management.metrics.tags.application=${spring.application.name}
management.endpoints.web.base-path=/actuator
```
⚠️ **By default only `/health` is exposed over HTTP** (Boot 2.5+; before 2.5, `/info` was exposed too) — that is deliberate. Never expose `env`, `configprops`, `heapdump`, `threaddump` or `loggers` publicly: they leak configuration, secrets and memory contents. Put actuator on a **separate port** (`management.server.port=9090`) that your ingress doesn't route.

| Endpoint | Use |
|---|---|
| `/actuator/health` | ✅ load balancer / Kubernetes probe |
| `/actuator/health/liveness` | K8s **liveness** — "restart me" |
| `/actuator/health/readiness` | K8s **readiness** — "send me traffic" |
| `/actuator/metrics` | Micrometer metrics |
| `/actuator/prometheus` | ✅ Prometheus scrape endpoint |
| `/actuator/mappings` | ✅ **every registered route** — the answer to "which controller serves this URL?" ([§W4.16](03-spring-web.md#w416-debugging-cheatsheet-where-to-put-a-breakpoint)) |
| `/actuator/beans` | every bean, with dependencies |
| `/actuator/conditions` | the auto-configuration report ([§C1](02-spring-core.md#c1-the-spring-boot-mental-model-and-auto-configuration-q47-)) |
| `/actuator/loggers` | ✅ **change a log level at runtime, no restart** |
| `/actuator/threaddump` | diagnose a deadlock or thread-pool exhaustion ([§J6](01-java.md#j6-concurrency-and-multithreading-q2q9)) |

```bash
# Turn on security debug logging in a live pod without redeploying — genuinely valuable at 3am
curl -X POST localhost:9090/actuator/loggers/org.springframework.security \
     -H 'Content-Type: application/json' -d '{"configuredLevel":"DEBUG"}'
```
```java
// A custom health indicator — contributes to /actuator/health automatically
@Component
public class PaymentServiceHealth implements HealthIndicator {
    @Override public Health health() {
        return client.ping()
            ? Health.up().withDetail("latencyMs", lastLatency).build()
            : Health.down().withDetail("reason", "payment-service unreachable").build();
    }
}
```
⚠️ **Don't put downstream checks in the liveness probe.** If `/health` goes DOWN because a *downstream* is unhealthy, Kubernetes restarts **your** pod — which fixes nothing and removes capacity during exactly the wrong incident. Downstream checks belong in **readiness** at most, and often in neither.

**Custom metrics** with Micrometer (the Prometheus client for the JVM):
```java
@Service @RequiredArgsConstructor
public class OrderService {
    private final MeterRegistry registry;

    public Order create(CreateOrderRequest r) {
        return registry.timer("orders.create", "channel", r.channel())
                       .record(() -> doCreate(r));
    }
}
```

### P5.5 Observability: structured logging and tracing [+]

```xml
<dependency>
    <groupId>io.micrometer</groupId>
    <artifactId>micrometer-tracing-bridge-otel</artifactId>
</dependency>
```
```properties
# Boot 3.4+ can emit JSON logs with no logback.xml at all
logging.structured.format.console=ecs          # or logstash / gelf
management.tracing.sampling.probability=0.1    # sample 10% in production
logging.pattern.level=%5p [${spring.application.name},%X{traceId:-},%X{spanId:-}]
```
💡 **Micrometer Tracing auto-instruments `RestClient`, `WebClient`, `RestTemplate` (when built from Boot's auto-configured builders) and Spring MVC**, so `traceId`/`spanId` propagate to downstream services and appear in every log line — for free. That is the Java equivalent of OpenTelemetry auto-instrumentation in Python/Node, and it's considerably more complete. ⚠️ Crossing a thread boundary (`@Async`, your own executors) needs context propagation, e.g. a `ContextPropagatingTaskDecorator` bean (Framework 6.1+, with `io.micrometer:context-propagation`); ✅ Verified in Boot source:
- **Boot 4.1+** registers one when you set `spring.task.execution.propagate-context=true`. The default is `false`, and it needs `io.micrometer:context-propagation` on the classpath. This property doesn't exist in 4.0.x.
- **Earlier versions (2.7–4.0)** have no automatic decorator. Declare a `ContextPropagatingTaskDecorator` (Framework 6.1+) or your own `TaskDecorator` as a bean. Boot applies any `TaskDecorator` bean to the auto-configured `applicationTaskExecutor`, and does in 2.7.18 as well.
- Executors you build yourself must have the decorator set by hand.

See [§P3](#p3-background-work-scheduled-and-async).

⚠️ **`MDC` is a `ThreadLocal`.** Anything you put there must be cleared in a `finally` ([§W4.6](03-spring-web.md#w46-the-filter-chain)) — worker threads are pooled and reused, so a stale correlation ID will attach itself to an unrelated user's request. This is a real privacy bug, not just noise.

### P5.6 The deployment shape [+]

```dockerfile
# Multi-stage, layered. The JRE base is ~180MB vs ~450MB for the full JDK.
FROM eclipse-temurin:21-jdk-alpine AS build
WORKDIR /app
COPY .mvn/ .mvn/
COPY mvnw pom.xml ./
RUN ./mvnw -B dependency:go-offline        # ← cached layer: dependencies change rarely
COPY src ./src
RUN ./mvnw -B clean package -DskipTests

FROM eclipse-temurin:21-jre-alpine
WORKDIR /app
RUN addgroup -S app && adduser -S app -G app     # ⚠️ never run as root
USER app
COPY --from=build /app/target/*.jar app.jar
EXPOSE 8080
ENTRYPOINT ["java", "-XX:MaxRAMPercentage=75.0", "-jar", "app.jar"]
```
⚠️ **Set `-XX:MaxRAMPercentage` in a container.** Modern JVMs (JDK 10+, 8u191+) are container-aware and size the heap from the **cgroup limit**, but the default max heap is only **25%** of it. That wastes most of the pod's memory, or tempts people into a fixed `-Xmx` that's too close to the limit. Then heap + metaspace + thread stacks + direct buffers exceed the limit, and the kernel OOM-kills the pod with **no Java stack trace**, just exit code 137. 75% leaves headroom for that off-heap memory. (Very old JVMs without container support really did read the *host's* memory — another reason to stay on a current JDK.)

💡 **`./mvnw spring-boot:build-image`** produces an optimized, layered OCI image via Cloud Native Buildpacks with no Dockerfile at all, including a correctly tuned JVM. Often the better default.

### P5.7 The production checklist

| ☐ | Item | Where |
|---|---|---|
| ☐ | Timeouts on EVERY downstream call (connect + read) ← the #1 omission | [§P2.1](#p21--resilience-timeouts-retries-circuit-breakers) |
| ☐ | DTOs at the API boundary, never entities | [§P5.2](#p52-dtos-vs-entities--never-expose-your-entities-) |
| ☐ | Global `@RestControllerAdvice` returning `ProblemDetail` | [§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling) |
| ☐ | Bean Validation on every inbound DTO (+ the starter!) | [§W7](03-spring-web.md#w7-validation-q55) |
| ☐ | Actuator health/liveness/readiness, on a separate port | [§P5.4](#p54-actuator-health-metrics-) |
| ☐ | Structured JSON logs with traceId | [§P5.5](#p55-observability-structured-logging-and-tracing-) |
| ☐ | No secrets in `application.yml`: env vars or a secret store | [§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12), [§P4.5](#p45-with-aws-parameter-store--secrets-manager-) |
| ☐ | springdoc DISABLED in prod | [§W12](03-spring-web.md#w12-api-documentation-openapi-and-swagger-q32-q33) |
| ☐ | CSRF decision made deliberately, not copy-pasted | [§S6](05-spring-security.md#s6-csrf-and-cors) |
| ☐ | Connection pool sized, and no network I/O inside `@Transactional` | [§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production) |
| ☐ | N+1 checked on every list endpoint | [§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production) |
| ☐ | Container memory flags set | [§P5.6](#p56-the-deployment-shape-) |
| ☐ | Graceful shutdown: `server.shutdown=graceful`. ✅ It is the default since Boot 3.4 (release notes: *"Graceful shutdown of the embedded web server … is now enabled by default"*), so Boot 4.1 has it on. **On Boot 2.7 you must set it yourself** | — |
| ☐ | Scheduled jobs: a cluster lock if they must run once, and failures alerted | [§P3](#p3-background-work-scheduled-and-async) |
| ☐ | Retries only on idempotent calls, with total time < the caller's deadline | [§P2](#p2-resilience-retries-recovery-and-circuit-breakers) |
| ☐ | Log levels: root=INFO, your package=DEBUG only in non-prod | [§S7](05-spring-security.md#s7-configuration-debugging-grpc-and-docs-endpoints) |

---



---

[⬅ 05-spring-security.md](05-spring-security.md) · [🏠 Start here](00-start-here.md)
