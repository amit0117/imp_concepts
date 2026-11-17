# Spring Core — Container, Configuration, Proxies, AOP and Events

[⬅ 01-java.md](01-java.md) · [🏠 Start here](00-start-here.md) · [03-spring-web.md ➡](03-spring-web.md)

> Part of the Java & Spring Boot learning set. Section labels in this file start with **C**. The legend, version landscape, quick revision sheet and glossary live in [00-start-here.md](00-start-here.md).

## Contents

- [C1. The Spring Boot mental model and auto-configuration [Q47, +]](#c1-the-spring-boot-mental-model-and-auto-configuration-q47-)
  - [C1.1 Spring vs Spring Boot](#c11-spring-vs-spring-boot)
  - [C1.2 `@SpringBootApplication` expanded](#c12-springbootapplication-expanded)
  - [C1.3 How auto-configuration actually works [Q47]](#c13-how-auto-configuration-actually-works-q47)
  - [C1.4 Starters are just POMs [+]](#c14-starters-are-just-poms-)
  - [C1.5 How to see what Boot decided [Q47]](#c15-how-to-see-what-boot-decided-q47)
- [C2. Inversion of Control and Dependency Injection [Q13]](#c2-inversion-of-control-and-dependency-injection-q13)
  - [C2.1 The principle [Q13]](#c21-the-principle-q13)
  - [C2.2 The Hollywood Principle [Q13]](#c22-the-hollywood-principle-q13)
  - [C2.3 IoC vs Dependency Injection [Q13]](#c23-ioc-vs-dependency-injection-q13)
  - [C2.4 The container [Q13]](#c24-the-container-q13)
  - [C2.5 How beans get defined](#c25-how-beans-get-defined)
  - [C2.6 Which stereotype goes on which class — and what each one actually adds](#c26-which-stereotype-goes-on-which-class--and-what-each-one-actually-adds)
  - [C2.7 Injection styles — and why constructor injection wins](#c27-injection-styles--and-why-constructor-injection-wins)
  - [C2.8 Why field injection hurts — your `OrderService` example, worked through](#c28-why-field-injection-hurts--your-orderservice-example-worked-through)
  - [C2.9 Scopes and the bean lifecycle](#c29-scopes-and-the-bean-lifecycle)
  - [C2.10 A prototype inside a singleton: `ObjectProvider`, scoped proxies and `@Lookup`](#c210-a-prototype-inside-a-singleton-objectprovider-scoped-proxies-and-lookup)
  - [C2.11 Resolving ambiguity](#c211-resolving-ambiguity)
  - [C2.12 Circular dependencies](#c212-circular-dependencies)
  - [C2.13 What actually happens at startup (the mechanism)](#c213-what-actually-happens-at-startup-the-mechanism)
  - [C2.14 Running code once at startup: `CommandLineRunner` and `ApplicationRunner`](#c214-running-code-once-at-startup-commandlinerunner-and-applicationrunner)
  - [C2.15 Comparison with your frameworks [Q13]](#c215-comparison-with-your-frameworks-q13)
  - [C2.16 The benefits table [Q13]](#c216-the-benefits-table-q13)
- [C3. Configuration and environment variables — the `.env` equivalent [Q12]](#c3-configuration-and-environment-variables--the-env-equivalent-q12)
  - [C3.1 The short answer [Q12]](#c31-the-short-answer-q12)
  - [C3.2 Referencing real OS environment variables [Q12]](#c32-referencing-real-os-environment-variables-q12)
  - [C3.3 Profiles [+]](#c33-profiles-)
  - [C3.4 The full precedence order [+]](#c34-the-full-precedence-order-)
  - [C3.5 Relaxed binding: env var to property name [+]](#c35-relaxed-binding-env-var-to-property-name-)
  - [C3.6 `@Value` vs `@ConfigurationProperties` [+]](#c36-value-vs-configurationproperties-)
  - [C3.7 Why `@ConfigurationProperties` exists — the problems with many `@Value`s](#c37-why-configurationproperties-exists--the-problems-with-many-values)
  - [C3.8 Binding rules: names, nesting, collections](#c38-binding-rules-names-nesting-collections)
  - [C3.9 Validating configuration at startup](#c39-validating-configuration-at-startup)
  - [C3.10 Immutable properties with Java records](#c310-immutable-properties-with-java-records)
  - [C3.11 Runtime refresh: which properties update, and which don't](#c311-runtime-refresh-which-properties-update-and-which-dont)
  - [C3.12 Actually reading a `.env` file [Q12]](#c312-actually-reading-a-env-file-q12)
  - [C3.13 Secrets — what not to do [+]](#c313-secrets--what-not-to-do-)
  - [C3.14 Side-by-side summary [+]](#c314-side-by-side-summary-)
- [C4. Conditional beans and auto-configuration ordering](#c4-conditional-beans-and-auto-configuration-ordering)
  - [C4.1 `@ConditionalOnProperty` — pick an implementation from config](#c41-conditionalonproperty--pick-an-implementation-from-config)
  - [C4.2 `@ConditionalOnMissingBean` — a fallback when nothing else exists](#c42-conditionalonmissingbean--a-fallback-when-nothing-else-exists)
  - [C4.3 `@ConditionalOnBean` — only if another bean exists](#c43-conditionalonbean--only-if-another-bean-exists)
  - [C4.4 `@ConditionalOnClass` — only if a library is on the classpath](#c44-conditionalonclass--only-if-a-library-is-on-the-classpath)
  - [C4.5 Custom conditions — `Condition` + `@Conditional`](#c45-custom-conditions--condition--conditional)
  - [C4.6 `@ConditionalOnExpression` and `@Profile`](#c46-conditionalonexpression-and-profile)
  - [C4.7 Auto-configuration ordering — why `OnBean` conditions are only safe there](#c47-auto-configuration-ordering--why-onbean-conditions-are-only-safe-there)
  - [C4.8 Cheat sheet: the `@Conditional…` family](#c48-cheat-sheet-the-conditional-family)
- [C5. Proxies: JDK dynamic proxies, CGLIB, and @Configuration full vs lite mode](#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)
  - [C5.1 What a proxy is](#c51-what-a-proxy-is)
  - [C5.2 JDK dynamic proxies in 15 lines](#c52-jdk-dynamic-proxies-in-15-lines)
  - [C5.3 CGLIB: what it is and how it works](#c53-cglib-what-it-is-and-how-it-works)
  - [C5.4 `@Configuration` full mode vs lite mode](#c54-configuration-full-mode-vs-lite-mode)
  - [C5.5 Seeing the proxy for yourself](#c55-seeing-the-proxy-for-yourself)
- [C6. Aspect-Oriented Programming (AOP) [+]](#c6-aspect-oriented-programming-aop-)
  - [C6.1 The problem AOP solves [+]](#c61-the-problem-aop-solves-)
  - [C6.2 Why not just the Decorator pattern? [+]](#c62-why-not-just-the-decorator-pattern-)
  - [C6.3 The architecture, drawn [+]](#c63-the-architecture-drawn-)
  - [C6.4 Terminology, in plain words [+]](#c64-terminology-in-plain-words-)
  - [C6.5 The five advice types [+]](#c65-the-five-advice-types-)
  - [C6.6 Pointcut expressions in full [+]](#c66-pointcut-expressions-in-full-)
  - [C6.7 `@Around`: total control [+]](#c67-around-total-control-)
  - [C6.8 Weaving: Spring AOP vs AspectJ [+]](#c68-weaving-spring-aop-vs-aspectj-)
  - [C6.9 The gotchas that will actually bite you [+]](#c69-the-gotchas-that-will-actually-bite-you-)
  - [C6.10 The Python/FastAPI translation [+]](#c610-the-pythonfastapi-translation-)
  - [C6.11 The dependency, and why it works without `@EnableAspectJAutoProxy` [+]](#c611-the-dependency-and-why-it-works-without-enableaspectjautoproxy-)
  - [C6.12 Checklist [+]](#c612-checklist-)
- [C7. Spring application events](#c7-spring-application-events)
  - [C7.1 The three pieces, and your order example](#c71-the-three-pieces-and-your-order-example)
  - [C7.2 How routing works: the multicaster and the listener parameter](#c72-how-routing-works-the-multicaster-and-the-listener-parameter)
  - [C7.3 Synchronous by default — what that implies](#c73-synchronous-by-default--what-that-implies)
  - [C7.4 Spring events vs Kafka / RabbitMQ](#c74-spring-events-vs-kafka--rabbitmq)
  - [C7.5 `@TransactionalEventListener` — react only after the commit](#c75-transactionaleventlistener--react-only-after-the-commit)
  - [C7.6 Ordering, async listeners, and `@EnableAsync`](#c76-ordering-async-listeners-and-enableasync)
  - [C7.7 Returning events: chaining](#c77-returning-events-chaining)
  - [C7.8 Conditional listeners (SpEL)](#c78-conditional-listeners-spel)
  - [C7.9 Handling listener exceptions globally](#c79-handling-listener-exceptions-globally)
  - [C7.10 Summary](#c710-summary)

---

## C1. The Spring Boot mental model and auto-configuration [Q47, +]

Before any specific feature, understand the one idea that explains *all* of Spring Boot's "magic". Otherwise everything in the Spring docs (02–06) looks arbitrary.

### C1.1 Spring vs Spring Boot

| | **Spring Framework** | **Spring Boot** |
|---|---|---|
| What it is | The core library: IoC container, AOP, MVC, transactions | An **opinionated layer on top** of Spring |
| Configuration | You write it all (XML, then Java config) | **Auto-configured** from what's on the classpath |
| Server | You deploy a `.war` into an external Tomcat | **Tomcat is embedded in your jar** |
| Dependency versions | You pick and reconcile every one | **Starters + BOM** pin a tested set |
| Startup | `web.xml` or `WebApplicationInitializer` | `public static void main` |

**Spring Boot adds no new programming model.** `@Controller`, `@Service`, `@Autowired` are all plain Spring Framework. Boot only removes configuration.

### C1.2 `@SpringBootApplication` expanded

```java
@SpringBootApplication          // = the three annotations below, combined
public class MyApp {
    public static void main(String[] args) {
        SpringApplication.run(MyApp.class, args);
    }
}
```

| It expands to | Which does |
|---|---|
| `@SpringBootConfiguration` | marks this as a `@Configuration` class (a source of bean definitions) |
| `@EnableAutoConfiguration` | **the magic** — see below |
| `@ComponentScan` | scans **this class's package and everything below it** for `@Component`/`@Service`/`@Repository`/`@Controller` |

⚠️ **The most common beginner bug in all of Spring Boot:** your `@RestController` lives in a *sibling* package, not under the `@SpringBootApplication` class's package. Component scan never sees it, no bean is created, and every request 404s with no error message at all.

```
com.example.app
├── MyApp.java              ← @SpringBootApplication — scanning starts HERE
├── controller/OrderController.java   ✅ found
└── service/OrderService.java         ✅ found

com.other.stuff
└── PaymentController.java            ❌ NEVER FOUND — silent 404
```

### C1.3 How auto-configuration actually works [Q47]

This is the mechanism behind *"I didn't write any of this and it works"*.

```
  @EnableAutoConfiguration
            │
            ▼
  AutoConfigurationImportSelector
            │
            ▼  reads, from EVERY jar on the classpath:
  META-INF/spring/org.springframework.boot.autoconfigure.AutoConfiguration.imports
  (Spring Boot 2.7+/3.x — it was META-INF/spring.factories before)
            │
            ▼  ~150 candidate @Configuration classes
  Each one is guarded by @Conditional annotations
            │
            ▼
  Only the ones whose conditions pass create beans
```

The conditions:

| Annotation | Fires when |
|---|---|
| `@ConditionalOnClass(X.class)` | `X` is on the classpath |
| `@ConditionalOnMissingClass` | it isn't |
| **`@ConditionalOnMissingBean`** | **you haven't defined that bean yourself** ← "your bean always wins" |
| `@ConditionalOnBean` | some other bean exists |
| `@ConditionalOnProperty(name=…, havingValue=…)` | a config property is set |
| `@ConditionalOnWebApplication` | it's a web app |
| `@ConditionalOnResource` | a file exists |

Worked example — this is literally why the `DispatcherServlet` exists without you writing it [Q47]:

```java
@AutoConfiguration
@ConditionalOnWebApplication(type = SERVLET)
@ConditionalOnClass(DispatcherServlet.class)     // ← true because spring-boot-starter-web
class DispatcherServletAutoConfiguration {       //   put spring-webmvc on the classpath
    @Bean
    @ConditionalOnMissingBean                    // ← unless YOU declared one
    DispatcherServlet dispatcherServlet(...) { return new DispatcherServlet(); }
}
```

Other examples you benefit from constantly:
- `JacksonAutoConfiguration` — creates an `ObjectMapper` if you didn't.
- `DataSourceAutoConfiguration` — creates a HikariCP pool if a JDBC driver + `spring.datasource.url` are present.
- `ErrorMvcAutoConfiguration` — creates the `/error` endpoint.
- `SecurityAutoConfiguration` — locks down every endpoint and prints a generated password ([§S2.1](05-spring-security.md#s21-enablewebsecurity-and-the-securityfilterchain-bean-q35)).

### C1.4 Starters are just POMs [+]

A "starter" contains **no code** — it's a `pom.xml` that pulls a curated dependency set.

`spring-boot-starter-web` brings in:
```
spring-boot-starter            (core, logging, autoconfigure)
spring-boot-starter-json       → jackson-databind, jackson-datatype-jdk8,
                                 jackson-datatype-jsr310, jackson-module-parameter-names
spring-boot-starter-tomcat     → embedded Tomcat
spring-web                     → RestTemplate, HTTP abstractions
spring-webmvc                  → DispatcherServlet, @Controller, HandlerMapping…
```

📌 **Boot 4 renames:** `spring-boot-starter-web` is now **`spring-boot-starter-webmvc`** (the old name still resolves but is deprecated), and the JSON starter brings **Jackson 3** (`tools.jackson.*`) instead of the Jackson 2 modules listed above. The list above is the Boot 2.7/3.x picture.

⚠️ **`spring-boot-starter-validation` is NOT included** — it was split out in Spring Boot 2.3. If `@Valid` silently does nothing, this is why. Add it explicitly ([§W7](03-spring-web.md#w7-validation-q55)).

### C1.5 How to see what Boot decided [Q47]

Stop guessing — make it tell you:

```bash
mvn spring-boot:run -Dspring-boot.run.arguments=--debug
```
prints a **CONDITIONS EVALUATION REPORT**:
```
Positive matches:
-----------------
   DispatcherServletAutoConfiguration matched:
      - @ConditionalOnClass found required class
        'org.springframework.web.servlet.DispatcherServlet' (OnClassCondition)

Negative matches:
-----------------
   MongoAutoConfiguration:
      Did not match:
         - @ConditionalOnClass did not find required class 'com.mongodb.client.MongoClient'
```

Or, with actuator on the classpath: `GET /actuator/conditions`, `GET /actuator/beans`, `GET /actuator/configprops`, `GET /actuator/mappings`.

And in your startup logs you can see the `DispatcherServlet` being created [Q47]:
```
o.s.b.w.embedded.tomcat.TomcatWebServer  : Tomcat initialized with port(s): 8080 (http)
o.a.c.c.C.[Tomcat].[localhost].[/]       : Initializing Spring embedded WebApplicationContext
o.s.web.servlet.DispatcherServlet        : Initializing Servlet 'dispatcherServlet'
o.s.web.servlet.DispatcherServlet        : Completed initialization in 12 ms
```

---

## C2. Inversion of Control and Dependency Injection [Q13]

> **Your question:** *"inversion of control in spring and this principle?"*

### C2.1 The principle [Q13]

**Inversion of Control (IoC)** is a design principle where **control of object creation, lifecycle management, and dependency wiring is transferred from your application code to an external framework.**

In traditional Java, *your* code controls the flow — if a `Car` needs an `Engine`, you write `Engine eng = new Engine()`. With IoC this is **inverted**: the framework instantiates and plugs components together, leaving you to write only business logic.

```
WITHOUT IoC — the class creates its own dependencies
┌──────────────────────────────────────┐
│ class OrderService {                 │
│   private final PaymentClient c =    │
│       new StripePaymentClient();     │  ◄── hardcoded. Can't swap. Can't mock.
│ }                                    │      Can't test without hitting Stripe.
└──────────────────────────────────────┘

WITH IoC — the class DECLARES what it needs; the container supplies it
┌──────────────────────────────────────┐       ┌─────────────────────┐
│ class OrderService {                 │       │  Spring IoC         │
│   private final PaymentClient c;     │◄──────┤  Container          │
│   OrderService(PaymentClient c) {    │ injects│                     │
│     this.c = c;                      │       │  decides WHICH impl │
│   }                                  │       │  and WHEN to build  │
│ }                                    │       └─────────────────────┘
└──────────────────────────────────────┘
```

### C2.2 The Hollywood Principle [Q13]

The philosophy behind IoC is often explained as the **Hollywood Principle**: *"Don't call us, we'll call you."*

In a traditional application, **your code calls library routines** to do work. In an IoC architecture like Spring, **the framework calls your code** when it needs to. Like an audition: instead of the actor constantly calling the studio to ask about the part, the studio says *"Don't call us, we'll call you."*

**Spring is the studio.** You register your classes as Beans, and Spring calls, instantiates, and manages them whenever the application requires.

💡 **This is broader than DI, and you already know several examples:**

| Framework | The IoC | Who calls whom |
|---|---|---|
| Express | `app.use(fn)` | the framework calls your middleware |
| React | `render()` | React calls your component, you never call `render` |
| FastAPI | `@app.get("/x")` | Uvicorn→FastAPI calls your function |
| JUnit | `@Test` | the runner calls your test methods |
| Spring | **DI + `@GetMapping` + lifecycle callbacks** | the container calls everything |

So **IoC is the umbrella**; DI is one specific technique under it.

### C2.3 IoC vs Dependency Injection [Q13]

People use these interchangeably. They are not the same:

| | **Inversion of Control (IoC)** | **Dependency Injection (DI)** |
|---|---|---|
| What it is | The broad, high-level **design principle** — moving control away from application code to a container | The concrete **implementation pattern** used to achieve IoC |
| Scope | Includes callbacks, template methods, event loops, middleware | Specifically: *how* components **receive** their required resources |
| Forms | many | **Constructor**, **Setter**, **Field** injection |

> **One-liner:** IoC is *what* (the framework is in charge); DI is *how* (dependencies are handed to you rather than constructed by you).

### C2.4 The container [Q13]

Spring implements IoC via a specialised engine — the **IoC Container** — which orchestrates your components (called **Beans**).

Its lifecycle follows a clear sequence [Q13]:
1. **Reads metadata** — from Java annotations (`@Component`, `@Configuration`), XML files, or Java code.
2. **Instantiates beans** — creates the classes defined by that metadata.
3. **Injects dependencies** — wires dependent objects together so they're ready for execution.

Two interfaces:

| Interface | What it offers |
|---|---|
| `BeanFactory` | the basic container: bean instantiation + wiring |
| **`ApplicationContext`** | extends `BeanFactory` with enterprise features — event publishing, i18n, resource loading, AOP integration, auto bean post-processing. **This is what you actually use.** |

In a Spring Boot web app the concrete type is `AnnotationConfigServletWebServerApplicationContext`.

### C2.5 How beans get defined

**Two mechanisms** you'll use daily:

```java
// 1. STEREOTYPE ANNOTATIONS + component scan — for YOUR classes
@Service     class OrderService {}       // business logic
@Repository  class OrderRepository {}    // data access (+ SQLException → DataAccessException translation)
@Controller  class OrderController {}    // web handler
@Component   class OrderMapper {}        // generic — the others are all specialisations of this

// 2. @Bean METHODS in a @Configuration class — for THIRD-PARTY classes you can't annotate
@Configuration
class HttpConfig {
    @Bean
    RestClient stripeClient(StripeProperties props) {      // params are injected too
        return RestClient.builder().baseUrl(props.baseUrl()).build();
    }
}
```

`@Service`, `@Repository`, `@Controller` are all **meta-annotated with `@Component`** — functionally near-identical, but the specific one documents intent and, for `@Repository`, activates exception translation. Use the specific one.

### C2.6 Which stereotype goes on which class — and what each one actually adds

> **Your note:** *"@Service is an alias for @Component and nothing different, this is the same for @Repository and @RestController (RestController is just a Component + @ResponseBody). We should use @Service for business-logic classes and @Component for core or low-level implementation. @Configuration is used to create beans using some function. When to give a class what annotation? Controller level → @RestController/@Controller; business logic → @Service; persistence → @Repository; any other class we want as a bean → @Component."*

Your placement rule is exactly right. Two parts of the note need sharpening, because "alias" hides real behaviour:

| Annotation | Is a `@Component`? | What it adds **beyond** "make this a bean" | Put it on |
|---|---|---|---|
| `@Component` | itself | nothing — the generic stereotype | helpers, mappers, clients, anything else you want managed |
| `@Service` | ✅ meta-annotated | **nothing functional today** — pure documentation of intent | business-logic classes |
| `@Repository` | ✅ | **exception translation**: raw persistence exceptions (`SQLException`, Hibernate/JPA exceptions) become Spring's unchecked `DataAccessException` hierarchy. Done by `PersistenceExceptionTranslationPostProcessor`, which Boot auto-configures | DAO / persistence classes you write yourself |
| `@Controller` | ✅ | **handler detection**: `RequestMappingHandlerMapping` scans `@Controller` beans for `@RequestMapping` methods | web controllers returning views |
| `@RestController` | ✅ (via `@Controller`) | `@Controller` **+ `@ResponseBody`** on every method | JSON/REST controllers ([§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling)) |
| `@Configuration` | ✅ | **holds `@Bean` methods**, and by default is CGLIB-proxied so `@Bean` methods calling each other return the *same* singleton ("full mode", [§C5](#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)) | config classes that build beans from code you don't own |

📌 **Correction:** `@RestController` is **`@Controller` + `@ResponseBody`**, not `@Component` + `@ResponseBody`. The difference matters: since **Spring Framework 6.0**, a class is detected as a web handler **only** if it carries `@Controller` (a plain `@Component` with a type-level `@RequestMapping` is no longer picked up). So `@Component @ResponseBody @RequestMapping("/x")` gives you a bean with **zero endpoints**.

📌 **Correction (small):** `@Repository` is not "just an alias" — it opts the class into exception translation. On a **Spring Data interface** (`interface UserRepo extends JpaRepository<…>`) the annotation is optional, because Spring Data creates the proxy itself and applies translation anyway ([§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-)).

`@Configuration` vs `@Component` for `@Bean` methods, in one line: both work, but only `@Configuration` (full mode) intercepts `beanA()` calling `beanB()` and returns the container's singleton; in a `@Component` ("lite mode") that call is a plain Java call that builds a **second** object. Details in [§C5.4](#c54-configuration-full-mode-vs-lite-mode).

### C2.7 Injection styles — and why constructor injection wins

```java
// ✅ CONSTRUCTOR INJECTION — use this, essentially always
@Service
public class OrderService {
    private final PaymentClient payments;      // FINAL — immutable
    private final OrderRepository repo;

    // Spring 4.3+: a SINGLE constructor needs no @Autowired at all
    public OrderService(PaymentClient payments, OrderRepository repo) {
        this.payments = payments;
        this.repo = repo;
    }
}

// ⚠️ SETTER INJECTION — only for genuinely optional dependencies
@Autowired(required = false)
public void setMetrics(MetricsClient m) { this.metrics = m; }

// ❌ FIELD INJECTION — concise, and wrong
@Autowired private PaymentClient payments;
```

| | Constructor | Setter | Field |
|---|---|---|---|
| Fields can be `final` (immutable, thread-safe) | ✅ | ❌ | ❌ |
| Fails at **startup** if the dependency is missing | ✅ | ❌ (NPE later) | ❌ (NPE later) |
| Unit-testable without Spring or reflection | ✅ `new OrderService(mock, mock)` | ⚠️ | ❌ needs reflection or `@InjectMocks` |
| Circular dependencies surface as an error | ✅ always | ⚠️ only because Boot 2.6+ forbids cycles by default | ⚠️ same — set `allow-circular-references=true` and it silently "works" |
| Makes bloat visible | ✅ a 12-arg constructor **screams** | ❌ | ❌ 12 fields look fine |

That last row is the underrated one: **field injection hides design problems.** A class with twelve `@Autowired` fields looks tidy; a twelve-parameter constructor tells you immediately that the class does too much.

💡 With Lombok, constructor injection costs nothing:
```java
@Service
@RequiredArgsConstructor        // generates a constructor for all `final` fields
public class OrderService {
    private final PaymentClient payments;
    private final OrderRepository repo;
}
```

### C2.8 Why field injection hurts — your `OrderService` example, worked through

> **Your note (cleaned up):** *"Field injection allows creating the class without its dependency. If someone creates `OrderService` with `new`, Spring Boot still allows it, but it fails with an NPE when we call `processPayment`. Field injection makes unit testing hard — with `new` the field is null, so we need Mockito. And a field-injected dependency can't be `final`; for `final` we need constructor injection."*

```java
@Service
public class OrderService {
    @Autowired
    private PaymentService paymentService;          // ← set by reflection AFTER construction

    public List<Order> processOrders(List<Order> orders) {
        paymentService.processPayment(orders.get(0)); // 💥 NPE if this object came from `new`
        return orders.stream().map(this::enrichOrder).toList();
    }
}
```

All three points are correct. Precisely:

1. **`new OrderService()` compiles and runs** — Spring is not involved at all, so nobody sets the field. The object is "half-built" and the failure is an NPE at the *first call*, far from the bug. (📌 Small correction: it isn't that "Spring allows it" — `new` bypasses Spring entirely. There is also no constructor that *could* take a `PaymentService`, so you can't even pass one.)
2. **Testing**: with field injection a plain unit test must either use reflection (`ReflectionTestUtils.setField`) or Mockito's `@InjectMocks`. With a constructor it is just `new OrderService(mockPayment)` — no framework.
3. **`final` is impossible** with field injection, because a `final` field must be assigned in the constructor and Spring injects fields *after* the constructor finished. Without `final`, nothing stops someone from reassigning it later, and you lose the "safely published after construction" guarantee of the Java Memory Model ([§J6](01-java.md#j6-concurrency-and-multithreading-q2q9)).

Two more reasons from the table above, worth remembering because interviewers ask them: constructor injection **exposes cycles** and **makes bloat visible**.

🐍 This is the same reason FastAPI pushes you to `Depends()` parameters instead of module-level globals: dependencies that are *visible in the signature* can be overridden in tests.

### C2.9 Scopes and the bean lifecycle

| Scope | Instances | Use |
|---|---|---|
| **`singleton`** (default) | **one per container** | ✅ virtually everything — services, repos, controllers |
| `prototype` | a new one per injection/lookup | stateful helpers |
| `request` | one per HTTP request | web only |
| `session` | one per HTTP session | web only |
| `application` | one per `ServletContext` | web only |

⚠️ **Singleton means one per *container*, not one per JVM** — and, critically, **it means shared across all ~200 request threads**. Spring singletons **must be stateless**. This is the same rule as [§W1.5](03-spring-web.md#w15-one-servlet-many-threads--the-concurrency-model-q44), and it is the one that catches people from FastAPI, where `Depends` typically resolves per request.

```
BEAN LIFECYCLE
  instantiate (constructor)
        ▼
  populate properties (setter/field injection)
        ▼
  *Aware callbacks (BeanNameAware, ApplicationContextAware…)
        ▼
  BeanPostProcessor.postProcessBeforeInitialization()
        ▼
  @PostConstruct
        ▼
  InitializingBean.afterPropertiesSet()  /  @Bean(initMethod=…)
        ▼
  BeanPostProcessor.postProcessAfterInitialization()   ◄── AOP PROXIES ARE CREATED HERE
        ▼
  ===== bean is in use =====
        ▼
  @PreDestroy  →  DisposableBean.destroy()  →  @Bean(destroyMethod=…)
```

⚠️ **The proxy self-invocation trap — a top-5 real-world Spring bug.** Because AOP wraps your bean in a proxy at that marked step, `@Transactional`, `@Cacheable`, `@Async`, `@PreAuthorize` **only work when called through the proxy — i.e. from outside the bean.**

```java
@Service
public class OrderService {
    public void process(Order o) {
        this.saveInTransaction(o);      // ❌ `this` is the RAW object — NO transaction!
    }
    @Transactional
    public void saveInTransaction(Order o) { ... }
}
```
It compiles, runs, logs nothing, and silently has no transaction. Fixes: move the annotated method into another bean, self-inject with `@Lazy`, or use `TransactionTemplate` programmatically.

### C2.10 A prototype inside a singleton: `ObjectProvider`, scoped proxies and `@Lookup`

> **Your problem statement:** *"We have two beans, one singleton and one prototype, and we inject the prototype into the singleton, which is used from a controller. The controller always gets the same singleton, and because the prototype was injected into it, every time we get the same prototype instance — which violates the principle of a prototype bean. ObjectProvider, scoped proxy and @Lookup are the three solutions."*

Exactly right, and the reference docs say it the same way: *"dependencies are resolved at instantiation time… The prototype instance is the sole instance that is ever supplied to the singleton-scoped bean."* Injection happens **once**, when the singleton is built. "Prototype" means *a new instance per request **to the container***, not per method call — and after startup nobody asks the container again.

```
WITHOUT a fix                                  WITH a fix
Controller ─► SingletonService                 Controller ─► SingletonService
                 │ field: PrototypeBean#1                       │ asks the container EACH time
                 └─► always #1                                  ├─► PrototypeBean#1
                                                                ├─► PrototypeBean#2
                                                                └─► PrototypeBean#3
```

All three solutions do the same thing underneath — **they defer the `beanFactory.getBean(...)` call from startup to the moment you need the object.** They differ only in *where* that call is hidden.

#### 1. `ObjectProvider<T>` — you call the container explicitly

> **Your question:** *"Do we need to call `provider.getObject()`, or is wrapping the prototype in an `ObjectProvider` sufficient?"*

**You must call `getObject()`** (or `getIfAvailable()` / `getIfUnique()`) **each time you want an instance.** Injecting `ObjectProvider<PrototypeBean>` injects only a lightweight handle; no `PrototypeBean` exists yet.

```java
@Service
public class SingletonService {
    private final ObjectProvider<PrototypeBean> prototypeProvider;

    public SingletonService(ObjectProvider<PrototypeBean> prototypeProvider) {
        this.prototypeProvider = prototypeProvider;
    }

    public void process() {
        PrototypeBean fresh = prototypeProvider.getObject();   // ← NEW instance created here
        fresh.doWork();
    }
}
```

📌 **Correction to your mental model:** the provider does **not** itself check "is this prototype? then create, else return cached". It simply calls the `BeanFactory`, and the **bean factory** applies the scope rule — for a singleton it returns the cached instance, for a prototype it builds a new one. The provider is scope-agnostic.

`ObjectProvider` (Spring 4.3+) extends the older `ObjectFactory`; the standard `jakarta.inject.Provider` works too. 🐍 It's like injecting a *factory function* (`get_db`) instead of a value.

#### 2. Scoped proxy — the container hides the call behind a proxy

```java
@Component
@Scope(value = ConfigurableBeanFactory.SCOPE_PROTOTYPE, proxyMode = ScopedProxyMode.TARGET_CLASS)
public class PrototypeBean { … }
```

The singleton is unchanged (`private final PrototypeBean bean;` via constructor). What gets injected is **not** a `PrototypeBean` but a **CGLIB subclass of it** — a stand-in. Every method call on the stand-in asks the bean factory for the real target and forwards the call. From the docs: *"every method call on the shared proxy leads to the creation of a new target instance to which the call is then being forwarded."*

> **Your question:** *"What is a scoped proxy and how is it different from the other AOP proxies?"*

| | AOP proxy (`@Transactional`, `@Async`, `@Retryable`) | Scoped proxy |
|---|---|---|
| Wraps | **one fixed target** created at startup | **no fixed target** |
| On each call | runs advice, then calls the *same* target | **looks up the target** in the scope (prototype → new; request → this request's; session → this session's), then forwards |
| Purpose | add behaviour around a call | let a long-lived bean hold a reference to a short-lived one |

Both are usually CGLIB subclasses — the same technology ([§C5](#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)), different job.

> **Your question:** *"Why `TARGET_CLASS`? What are the other values?"*

| `ScopedProxyMode` | Proxy created | Use when |
|---|---|---|
| `DEFAULT` | whatever the component-scan default is — normally `NO` | — |
| `NO` | none — the raw bean is injected (the bug you described) | singleton/prototype with no lookup need |
| `INTERFACES` | JDK dynamic proxy implementing the bean's interfaces | the bean implements an interface **and every injection point uses the interface type** |
| `TARGET_CLASS` | CGLIB subclass of the concrete class | no interface, or you inject the concrete class — the common choice |

> **Your question:** *"Does the call always go to the BeanFactory, even for singleton or other scopes, regardless of proxyMode?"*

No. **Without** a scoped proxy, the bean factory is consulted **once** — at injection time — and afterwards your field holds a plain object reference; method calls never touch the container. **With** a scoped proxy, the proxy consults the factory **on every method call**. (You *can* put a scoped proxy on a singleton — the factory then just returns the cached singleton each time — but it buys nothing except overhead.)

⚠️ **The scoped-proxy-on-prototype trap:** `bean.setName("x"); bean.getName();` are **two calls → two different instances** — the second call sees `null`. That's why scoped proxies are really meant for **`request` and `session` scope** ([§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder)), where "the current instance" is stable for a whole request. For prototypes, prefer `ObjectProvider`.

#### 3. `@Lookup` — the container overrides one of your methods

> **Your questions:** *"Where do we write the overridden method — in the SingletonBean or in the PrototypeBean? Why return null? How does Spring know which bean to inject without any field or constructor injection — does it use the return type?"*

- **Where:** in the **singleton** — the class that *needs* fresh instances.
- **Why `return null`:** Java requires a body for a non-abstract method so the file compiles. At startup Spring generates a **CGLIB subclass of `SingletonService`** that **overrides** this method with "return `beanFactory.getBean(...)`". Your `null` is never executed. You may instead declare the method (and class) `abstract`.
- **Which bean:** yes — **by the method's return type** (`getBean(PrototypeBean.class)`), or by name with `@Lookup("myBeanName")`.

```java
@Service
public class SingletonService {
    public void process() {
        PrototypeBean fresh = createPrototypeBean();   // calls Spring's override → new instance
        fresh.doWork();
    }

    @Lookup
    protected PrototypeBean createPrototypeBean() {
        return null;                                   // never runs
    }
}
```

📌 **Correction:** it is the **`SingletonService`** that gets subclassed, so the *singleton* is what's proxied — not the controller, and not the prototype. The controller is injected with that subclass instance like any other bean.

Rules, from the reference docs:
- the class **and** the method must not be `final` (CGLIB must subclass/override); signature is `<public|protected> [abstract] ReturnType name()` — **no arguments**;
- ⚠️ *"lookup methods do not work with factory methods and in particular not with `@Bean` methods in configuration classes"* — the container must create the instance itself to subclass it, so `@Lookup` works only on component-scanned classes;
- unit tests that `new SingletonService()` get the real `null`-returning method.

#### Which one?

| | `ObjectProvider` | Scoped proxy | `@Lookup` |
|---|---|---|---|
| Change needed in | the singleton (inject provider, call `getObject()`) | the prototype (`proxyMode`) | the singleton (lookup method) |
| Magic | none — explicit | high — calls look normal | medium — CGLIB subclass |
| New instance per | `getObject()` call | **every method call** | lookup-method call |
| Works with `@Bean`-created beans / `final` classes | ✅ | ⚠️ target class not final | ❌ |
| Verdict | ✅ **default choice** | ✅ for `request`/`session` scope | legacy-but-valid |

### C2.11 Resolving ambiguity

```java
interface PaymentClient {}
@Component class StripeClient  implements PaymentClient {}
@Component class PaypalClient  implements PaymentClient {}

@Service class Checkout {
    Checkout(PaymentClient c) {}        // 💥 NoUniqueBeanDefinitionException at STARTUP
}
```

Four fixes:
```java
@Primary @Component class StripeClient implements PaymentClient {}        // 1. default winner
Checkout(@Qualifier("paypalClient") PaymentClient c) {}                   // 2. pick by bean name
Checkout(List<PaymentClient> all) {}                                      // 3. inject ALL of them
Checkout(Map<String, PaymentClient> byName) {}                            // 4. name → impl
```

Options 3 and 4 are the idiomatic **Strategy pattern** in Spring — add a new `@Component` implementing the interface and it joins the map automatically, with no registration code anywhere.

### C2.12 Circular dependencies

```java
@Service class A { A(B b) {} }
@Service class B { B(A a) {} }     // 💥 startup failure
```
**Spring Boot 2.6+ disallows these by default.** The escape hatch `spring.main.allow-circular-references=true` exists, but the real fix is to extract the shared logic into a third bean, or break the cycle with `@Lazy` on one side. Note that **field injection hides this** — another reason to use constructors.

📌 Precise version of that last sentence: with **constructor** injection a cycle can *never* be resolved (neither object can be built first) → `BeanCurrentlyInCreationException`, always. With **field/setter** injection Spring *can* resolve it (build A, expose an early reference, build B with it, finish A) — so it only fails because Boot 2.6+ turned that resolution off by default. Flip the property and field-injected cycles silently work again.

#### Breaking a cycle with `@PostConstruct`

> **Your question:** *"How is @PostConstruct used to resolve a cyclic dependency in Spring Boot?"*

The trick is that **only one direction is injected by Spring**; the other direction is wired by hand after construction:

```java
import jakarta.annotation.PostConstruct;   // Boot 2.7: javax.annotation.PostConstruct

@Component
public class BeanA {
    private final BeanB beanB;
    public BeanA(BeanB beanB) { this.beanB = beanB; }   // A → B is a normal dependency

    @PostConstruct
    void init() { beanB.setBeanA(this); }              // B → A wired manually, after A is built
}

@Component
public class BeanB {
    private BeanA beanA;                                // NOT injected by Spring
    public void setBeanA(BeanA beanA) { this.beanA = beanA; }
}
```

```
1. Spring builds BeanB          (no dependencies)
2. Spring builds BeanA(beanB)   (B already exists)
3. @PostConstruct on A runs  →  beanB.setBeanA(this)
```

From the container's point of view **there is no cycle at all** — Spring only sees A → B. That's why it works even with circular references disallowed.

Caveats:
- `BeanB` is unusable (its `beanA` is `null`) until step 3 has run — don't call `beanA` from B's own `@PostConstruct`.
- `beanB.setBeanA` only *stores* a reference; don't do real work across the two beans inside `@PostConstruct`.
- It's a workaround. `@Lazy` on one constructor parameter does the same with less code (Spring injects a lazy-resolving proxy), and **extracting the shared logic into a third bean** removes the cycle, which is the real fix — a cycle means two classes are one responsibility split badly.

### C2.13 What actually happens at startup (the mechanism)

```
SpringApplication.run(App.class, args)
        │
        ▼  create the ApplicationContext
        │
        ▼  ConfigurationClassPostProcessor (a BeanFactoryPostProcessor)
        │     • scans for @Component/@Configuration under the base package
        │     • processes @Bean methods, @Import, @ComponentScan
        │     • pulls in ~150 auto-configuration classes and evaluates @Conditional
        │     ⇒ produces a registry of BeanDefinitions  (metadata — NOT objects yet)
        │
        ▼  finishBeanFactoryInitialization()
        │     • for EVERY non-lazy singleton: getBean(name)
        │     • resolve constructor args RECURSIVELY (depth-first through the graph)
        │     • run BeanPostProcessors → create AOP proxies
        │
        ▼  refresh complete → embedded Tomcat starts accepting connections
```

**Two consequences worth holding on to:**
1. **Beans are created eagerly at startup.** A missing/ambiguous dependency is a **startup crash with a clear message**, not a 3 a.m. 500. This is a real reliability advantage over runtime DI.
2. **The graph is built once.** At request time there is *no* DI work — the object references are already wired. This is why Spring's DI costs nothing per request, unlike FastAPI's `Depends`, which resolves on every call.

### C2.14 Running code once at startup: `CommandLineRunner` and `ApplicationRunner`

> **Your questions:** *"What is CommandLineRunner, how and when to use it? Will this run automatically because the class is a bean, or do we need to add something in the main class?"*

`CommandLineRunner` is a functional interface with one method, `void run(String... args)`. **Every bean of that type is called automatically by Spring Boot** just before `SpringApplication.run(...)` returns. You add nothing to `main`.

```java
@Component
public class CacheWarmer implements CommandLineRunner {        // style 1: a class
    private final ProductRepository repo;
    public CacheWarmer(ProductRepository repo) { this.repo = repo; }

    @Override
    public void run(String... args) { repo.findAllActive(); }
}

@Configuration
class SeedConfig {
    @Bean
    CommandLineRunner seedAdmin(UserRepository repo, PasswordEncoder enc) {   // style 2: a @Bean lambda
        return args -> { if (repo.findByUsername("admin").isEmpty()) { /* save admin */ } };
    }
}
```

`ApplicationRunner` is identical except `run(ApplicationArguments args)` gives you parsed `--name=value` options. Order several runners with `@Order` / `Ordered`.

**When exactly does it run?** From the Spring Boot reference, in order:

```
context refresh
   ├─ … beans created, @PostConstruct methods run
   └─ WebServerInitializedEvent        ← embedded Tomcat is ALREADY LISTENING on its port
ApplicationStartedEvent
AvailabilityChangeEvent  LivenessState.CORRECT
   ► CommandLineRunner / ApplicationRunner beans run here ◄
ApplicationReadyEvent
AvailabilityChangeEvent  ReadinessState.ACCEPTING_TRAFFIC   ← readiness probe flips to "ready"
```

📌 **"Before it accepts traffic" needs care.** The docs call runners *"well suited for tasks that should run after application startup but before it starts accepting traffic"* — that is true at the **readiness** level (Kubernetes won't route to the pod until runners finish). But the **socket is already open**: a request sent straight to the port during a slow runner *will* be served. Long work in a runner also delays readiness — and an exception in a runner fails startup.

The docs also recommend runners over `@PostConstruct` for startup tasks: `@PostConstruct` runs while the context is still being built, so other beans may not be ready.

> **Your question:** *"@Bean inside a @Component — does it run?"* Yes. A `@Bean` method in a `@Component` class is still processed ("lite mode", [§C5.4](#c54-configuration-full-mode-vs-lite-mode)), so the returned `CommandLineRunner` is a bean and runs. Convention is `@Bean` methods in `@Configuration`, or a `@Component` that implements the interface directly — mixing the two styles works but reads oddly.

Typical uses: seeding a dev admin user ([§S2](05-spring-security.md#s2-authentication-who-are-you)), warming a cache, verifying a downstream connection. 🐍 FastAPI's `@app.on_event("startup")` / lifespan handler; 🟨 the code you run before `app.listen()` — except that in Spring the port is already open.

### C2.15 Comparison with your frameworks [Q13]

| | **Spring** | **FastAPI** | **Express** | **NestJS** |
|---|---|---|---|---|
| DI built in? | ✅ full container | ✅ `Depends()` | ❌ none | ✅ full container |
| Declaration | `@Service` + constructor | `def f(db = Depends(get_db))` | manual `new` | `@Injectable()` + constructor |
| Default lifetime | **singleton** (whole app) | **per request** | n/a | **singleton** |
| Wiring resolved | **at startup** | **at request time** | by hand | at startup |
| Missing dependency | **startup crash** | runtime error on that route | `undefined` at runtime | startup crash |
| Swap impl for tests | `@MockBean` / pass a mock | `app.dependency_overrides` | manual | `overrideProvider` |
| Interface → impl binding | ✅ by type | ❌ by function reference | n/a | ✅ by token |

🐍 **The closest FastAPI analogy:** `Depends()` *is* DI, but it's **function-scoped and per-request**, with no container of long-lived objects. The `@lru_cache` trick on a settings provider is the community's way of faking a singleton. Spring's container is that idea made first-class and applied to the whole application graph.

🟨 **Express has nothing built in.** You hand-wire a composition root in `index.js`, or reach for Awilix / InversifyJS / tsyringe. **NestJS** was explicitly modelled on Angular and Spring — `@Injectable()`, modules, providers, constructor injection, singleton scope. If you ever used Nest, Spring's DI will feel like coming home.

### C2.16 The benefits table [Q13]

| Feature | **Traditional (no IoC)** | **Spring (with IoC)** |
|---|---|---|
| Object creation | manually instantiated (`new Car()`) | automatically managed by the container |
| Coupling | **High.** Modifying a class forces downstream code changes. | **Low.** Objects rely on abstractions (interfaces). |
| Testability | **Hard.** Difficult to isolate components. | **Easy.** Dependencies mocked or swapped trivially. |
| Configuration | scattered through constructors | centralised in the container |
| Lifecycle | you manage it | container manages init/destroy |
| Cross-cutting concerns | copy-pasted everywhere | AOP proxies applied uniformly |

---

## C3. Configuration and environment variables — the `.env` equivalent [Q12]

> **Your question:** *"for environment variable in js and python we have .env file so what is it's equivalent in java spring boot?"*

### C3.1 The short answer [Q12]

**The native equivalent is `application.properties` or `application.yml`.**

Unlike Node.js or Python, which typically rely on a raw `.env` file at the project root, **Spring Boot has a far more sophisticated built-in system** for configuration, secrets, and environment profiles. Spring Boot looks for these files in `src/main/resources/` by default.

```properties
# src/main/resources/application.properties
server.port=8080
spring.datasource.url=jdbc:mysql://localhost:3306/mydb
spring.datasource.username=root
```
```yaml
# src/main/resources/application.yml — same thing, nested
server:
  port: 8080
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/mydb
    username: root
```

Both formats work. **YAML is preferred** for anything non-trivial: it's less repetitive, supports lists naturally, and allows multiple profile documents in one file. ⚠️ If both exist in the same location, `.properties` wins.

### C3.2 Referencing real OS environment variables [Q12]

**Never hardcode passwords or API keys in `application.properties`** if the file goes into a repository.

Spring Boot lets you inject actual OS environment variables (from Docker, Kubernetes, or your shell) with **`${VARIABLE_NAME:fallback_value}`** syntax:

```properties
# If DB_PASSWORD is in the environment, use it. Otherwise fall back.
spring.datasource.password=${DB_PASSWORD:default_pass}

# No fallback → the app FAILS TO START if the variable is missing. Often what you want in prod.
stripe.api-key=${STRIPE_API_KEY}
```

🐍 This is `os.getenv("DB_PASSWORD", "default_pass")`. 🟨 This is `process.env.DB_PASSWORD ?? "default_pass"`. The difference is that Spring resolves it **at startup, declaratively**, so a missing required variable crashes the boot rather than blowing up on the first request that needs it.

### C3.3 Profiles [+]

```
src/main/resources/
├── application.yml          ← shared defaults, always loaded
├── application-local.yml    ← only when the "local" profile is active
├── application-dev.yml
└── application-prod.yml
```

```bash
java -jar app.jar --spring.profiles.active=prod
SPRING_PROFILES_ACTIVE=prod java -jar app.jar
```
```yaml
spring:
  config:
    activate:
      on-profile: prod        # multi-document YAML: one file, several profiles
```
```java
@Bean
@Profile("!prod")             // every profile EXCEPT prod
DataSource h2() { ... }
```

🐍 Roughly `.env.development` / `.env.production`, but Spring's version is first-class: profiles also gate **beans**, not just values — you can swap an entire fake payment gateway for the real one with one annotation.

### C3.4 The full precedence order [+]

This is the thing that actually saves you at 2 a.m. when a value isn't what you expect. From the Spring Boot reference: **later sources override earlier ones.**

| Rank (low → high) | Source |
|---|---|
| 1 | Default properties (`SpringApplication.setDefaultProperties`) |
| 2 | `@PropertySource` on `@Configuration` classes |
| 3 | **Config data** — `application.properties` / `.yml` (see the sub-order below) |
| 4 | `RandomValuePropertySource` (`random.*`) |
| 5 | **OS environment variables** |
| 6 | **Java system properties** (`-Dkey=value`) |
| 7 | JNDI attributes (`java:comp/env`) |
| 8 | `ServletContext` init parameters |
| 9 | `ServletConfig` init parameters |
| 10 | `SPRING_APPLICATION_JSON` |
| 11 | **Command-line arguments** (`--key=value`) |
| 12 | `properties` attribute on `@SpringBootTest` |
| 13 | `@DynamicPropertySource` (tests) |
| 14 | `@TestPropertySource` (tests) |
| 15 | Devtools global settings (`$HOME/.config/spring-boot`) |

**Memorise the practical slice:**
> **command line > system properties (`-D`) > OS env vars > `application-{profile}.yml` > `application.yml` > defaults**

And within config data (later wins):
```
1. classpath:application.yml                  (inside the jar)
2. classpath:application-{profile}.yml
3. classpath:/config/application.yml
4. classpath:/config/application-{profile}.yml
5. file:./application.yml                     (next to the jar — OUTSIDE it)
6. file:./application-{profile}.yml
7. file:./config/application.yml
8. file:./config/application-{profile}.yml    ← highest
```
**Profile-specific always beats non-specific at the same location, and outside-the-jar always beats inside.** That last rule is how you override config on a deployed server without rebuilding.

*Source: [Spring Boot — Externalized Configuration](https://docs.spring.io/spring-boot/reference/features/external-config.html)*

### C3.5 Relaxed binding: env var to property name [+]

Environment variable names can't contain dots or dashes, so Spring defines a canonical mapping. **The rule: uppercase everything, replace `.` with `_`, and DELETE `-`.**

| Property | Environment variable |
|---|---|
| `server.port` | `SERVER_PORT` |
| `spring.datasource.url` | `SPRING_DATASOURCE_URL` |
| `app.payments.api-key` | **`APP_PAYMENTS_APIKEY`** ← the dash is **removed**, not converted |
| `my.app[0].name` | `MY_APP_0_NAME` |

⚠️ `APP_PAYMENTS_API_KEY` (with the underscore) will **not** bind to `app.payments.api-key`. It binds to `app.payments.api.key`. This silently yields a null and costs people an afternoon.

**This is how you configure a Spring Boot app in Kubernetes or Docker** — no file needed:
```yaml
env:
  - name: SPRING_DATASOURCE_URL
    value: jdbc:postgresql://db:5432/orders
  - name: SPRING_PROFILES_ACTIVE
    value: prod
```

### C3.6 `@Value` vs `@ConfigurationProperties` [+]

```java
// @Value — fine for one or two scalars
@Service
class MailService {
    @Value("${app.mail.from}")                 private String from;
    @Value("${app.mail.retries:3}")            private int retries;      // :3 = default
    @Value("${app.mail.admins}")               private List<String> admins;  // comma-separated
}
```

```java
// @ConfigurationProperties — the right tool for a group. Type-safe, validated, IDE-completable.
@ConfigurationProperties(prefix = "app.payments")
@Validated
public record PaymentProperties(
        @NotBlank String apiKey,
        @NotNull  URI baseUrl,
        @Positive Duration timeout,           // "5s" / "PT5S" parsed automatically
        boolean sandbox) {}
```
```yaml
app:
  payments:
    api-key: ${STRIPE_API_KEY}
    base-url: https://api.stripe.com
    timeout: 5s
    sandbox: false
```
Register it with `@EnableConfigurationProperties(PaymentProperties.class)` or put `@ConfigurationPropertiesScan` on your app class. Then just inject `PaymentProperties` anywhere.

| | `@Value` | `@ConfigurationProperties` |
|---|---|---|
| Type safety | string-templated | ✅ real types, `Duration`, `DataSize`, enums, nested objects |
| Validation | ❌ | ✅ `@Validated` + Bean Validation — **fails at startup** |
| Relaxed binding | ⚠️ limited — works only if the placeholder uses the canonical kebab-case form (`${demo.item-price}` also finds `demo.itemPrice` and `DEMO_ITEMPRICE`) | ✅ full relaxed binding |
| SpEL (`#{...}`) | ✅ | ❌ |
| IDE autocomplete in YAML | ❌ | ✅ (with `spring-boot-configuration-processor`) |
| Records supported | n/a | ✅ constructor binding — records implicitly in Boot 2.7 (verified in 2.7.18 source); any single-constructor class implicitly in Boot 3+ |
| Best for | one-off values | **any group of related settings** |

🐍 **`@ConfigurationProperties` + a record + `@Validated` is Spring's `pydantic-settings`** — typed, validated, fail-fast configuration objects. That's the mental mapping to keep.

### C3.7 Why `@ConfigurationProperties` exists — the problems with many `@Value`s

> **Your notes, with your objections:** *"When we start using too many @Value: (1) env values get scattered among services; (2) we can't group related settings — [but don't we group them when we use application.yml?]; (3) it's harder to keep environments consistent — [can't we simply use profiles to solve this?]; (4) no type safety — everything is a String and we typecast in the codebase. ConfigurationProperties turns configuration into a strongly typed POJO: instead of injecting one property at a time we inject the whole configuration bean."*

Your summary is right; your two objections are fair and deserve exact answers:

| Problem with many `@Value`s | Your objection | The real answer |
|---|---|---|
| Settings are scattered | — | Ten `@Value("${notification.email.host}")` strings spread over ten classes; renaming a key means a text search. One `NotificationProperties` class is the single Java-side source of truth. |
| No grouping | "YAML already groups them" | ✅ YAML groups them **in the file**. `@Value` throws that grouping away **in Java** — each key is read independently. `@ConfigurationProperties` maps the YAML *tree* onto an object *tree*, so the grouping survives into the code. |
| Environment consistency | "Profiles solve this" | Profiles choose **which file** supplies values — they still work, and you still use them. What they don't do is **check** the values. With `@ConfigurationProperties` + `@Validated`, a missing or malformed key in `application-prod.yml` **fails startup** instead of failing the first request that touches it. Profiles + typed properties are complementary. |
| No type safety | — | 📌 Small correction: `@Value` does convert types (`@Value("${x}") int port` works, so does `Duration`). The weakness is that it's per-field, has no validation, no nested objects, no IDE metadata. |

> **Your note:** *"To use ConfigurationProperties we must have application.properties or application.yml to populate the fields; the class only makes using those values smooth."*

Mostly right — with one widening: the class binds from **the whole `Environment`**, not only those files. Env vars, `-D` system properties, command-line args, config-server values all bind into the same object, following the precedence in [§C3.4](#c34-the-full-precedence-order-). A class with defaults and no file at all also works.

**Registering the class** — pick one:

| How | Note |
|---|---|
| `@ConfigurationPropertiesScan` on the main class | scans from that package down — the usual choice |
| `@EnableConfigurationProperties(NotificationProperties.class)` on any `@Configuration` | explicit list |
| `@Component` on a JavaBean-style (setter) class | works, but ⚠️ **not** for constructor-bound classes/records (the docs: constructor binding is unavailable for `@Component`/`@Bean`/`@Import` beans) |

📌 **Correction:** `@ConfigurationPropertiesScan` isn't the only way — and it doesn't *create* the beans from nothing; it registers each annotated class found as a bean, exactly like component scanning does for `@Component`.

### C3.8 Binding rules: names, nesting, collections

> **Your question:** *"The names in the class should match the property names. Can we use application.properties as well or only application.yml? I think case sensitivity and hyphens don't matter. What rules should we follow?"*

- **Both `.properties` and `.yml` work identically** — both become entries in the `Environment` before binding.
- **Relaxed binding** (from the Spring Boot reference) — all of these bind to the Java field `firstName` under prefix `my.main-project.person`:

| Form | Example | Where recommended |
|---|---|---|
| kebab case | `my.main-project.person.first-name` | ✅ `.properties` / YAML — **recommended** |
| camel case | `my.main-project.person.firstName` | works |
| underscore | `my.main-project.person.first_name` | works in `.properties` / YAML |
| upper case | `MY_MAINPROJECT_PERSON_FIRSTNAME` | **environment variables** |

- **Env-var rule:** replace `.` with `_`, **remove** `-`, uppercase. So `notification.max-retry-count` → **`NOTIFICATION_MAXRETRYCOUNT`**. ⚠️ `NOTIFICATION_MAX_RETRY_COUNT` means `notification.max.retry.count` — a *nested* property — and won't bind to `maxRetryCount` ([§C3.5](#c35-relaxed-binding-env-var-to-property-name-)).
- **The `prefix` itself must be canonical**: lowercase kebab-case, e.g. `@ConfigurationProperties("notification.sms")`. `prefix="notificationSms"` is rejected at startup.

**Nesting** — matched by **field name**, not class name:

```yaml
notification:
  email:
    host: smtp.example.com
    port: 587
  sms:
    provider: twilio
    api-key: ${SMS_API_KEY}
```

```java
@ConfigurationProperties(prefix = "notification")
public class NotificationProperties {
    private Email email = new Email();   // field name "email" ↔ notification.email.*
    private Sms sms = new Sms();         // field name "sms"   ↔ notification.sms.*
    // getters + setters for email & sms

    public static class Email { private String host; private int port; /* getters/setters */ }
    public static class Sms   { private String provider; private String apiKey; /* getters/setters */ }
}
```

> **Your question:** *"Can we create the nested ConfigurationProperties classes separately and compose them in the parent, or do we have to nest them?"*

Both work. The child classes can be **static nested classes** or **separate top-level files** (`EmailProperties.java`); either way they need **no** `@ConfigurationProperties` of their own — the binder treats them as plain POJOs reached through the parent's field. Give a child its own `@ConfigurationProperties("notification.email")` only if you also want to inject it *on its own* as a separate bean.

**Collections:**

```yaml
notification:
  allowed-channels: [EMAIL, SMS, PUSH]   # List<String> / Set<String> / List<Channel enum>
  templates:                             # Map<String, String>
    welcome: "Welcome to our app!"
    otp: "Your code is {0}"
```
```properties
notification.allowed-channels[0]=EMAIL
notification.allowed-channels[1]=SMS
notification.allowed-channels=EMAIL,SMS          # comma-separated also works
notification.templates.welcome=Welcome to our app!
```
```bash
NOTIFICATION_ALLOWEDCHANNELS_0=EMAIL             # list index as its own _-separated segment (docs: my.service[0].other → MY_SERVICE_0_OTHER)
```

- `Set` de-duplicates; enums convert by name.
- ⚠️ **Map keys**: characters other than alphanumerics, `-` and `.` are **stripped** unless you bracket the key: `my.map[/key1]=v` (in YAML quote it: `"[/key1]": v`). Map keys bound from env vars are always lowercase.
- A `List` from a higher-precedence source **replaces** the whole list; lists are not merged across sources.

### C3.9 Validating configuration at startup

> **Your question:** *"How to start validation? Using spring-boot-starter-validation — is it the same library we use for request bodies and query params? We add validation rules in the class and it validates the values in application.yml."*

Yes — **the same Jakarta Bean Validation** (`@NotBlank`, `@Min`, `@Email`, …) and the same starter as `@Valid @RequestBody` ([§W7](03-spring-web.md#w7-validation-q55)). Three rules:

1. Put **`@Validated`** on the properties class (Spring's annotation — this is what triggers it).
2. Constraint annotations on the fields.
3. ⚠️ **`@Valid` on every nested object field**, or the nested object's constraints are skipped (the docs: *"To cascade validation to nested properties the associated field must be annotated with `@Valid`"*).

```java
@ConfigurationProperties(prefix = "notification")
@Validated
public class NotificationProperties {
    @Valid                                  // ← without this, Email's rules never run
    private Email email = new Email();

    @NotEmpty(message = "At least one channel must be configured")
    private List<String> allowedChannels;

    public static class Email {
        @NotBlank private String host;
        @Min(1) @Max(65535) private int port;
    }
}
```

If `host` is blank, the app **refuses to start** and prints which property failed (`Binding to target … failed`). That is the whole point: a typo in prod config is a failed deploy, not a 3 a.m. NPE.

### C3.10 Immutable properties with Java records

```java
@ConfigurationProperties(prefix = "notification")
@Validated
public record NotificationProperties(
        @DefaultValue("true")         boolean enabled,
        @DefaultValue({"EMAIL","SMS"}) List<String> allowedChannels,
        @Valid @DefaultValue          Email email,        // empty @DefaultValue → never null
        @Valid                        Sms sms) {          // absent from config → null

    public record Email(@NotBlank String host,
                        @DefaultValue("587") @Min(1) @Max(65535) int port) {}
    public record Sms(@NotBlank String provider, @NotBlank String apiKey) {}
}
```

- **Constructor binding** is used: the values go in through the canonical constructor, so the object is immutable and thread-safe. No setters.
- Defaults use `@DefaultValue` (a record component can't have `= value`). Without it, a missing nested group gives `null`; an **empty** `@DefaultValue` gives an instance with its own defaults.
- Register with `@ConfigurationPropertiesScan` / `@EnableConfigurationProperties` — **not** `@Component`.
- Must be compiled with `-parameters` (Boot's build plugins do this).
- **Versions:** Boot 3+ treats any class with a single parameterized constructor as constructor-bound (records included; `@ConstructorBinding` only to pick among several constructors). **Boot 2.7** treats **records** as implicitly constructor-bound (verified in the 2.7.18 source), but a normal class needs `@ConstructorBinding` (from the `org.springframework.boot.context.properties` package — it moved to `…properties.bind` in Boot 3).

Record vs mutable class is the usual trade-off ([§J5](01-java.md#j5-data-carriers-records-vs-lombok)): immutability by default, at the cost of one property you'll care about next — refresh.

### C3.11 Runtime refresh: which properties update, and which don't

> **The claim in your chat:** *"@ConfigurationProperties refreshes without @RefreshScope (ConfigurationPropertiesRebinder); a record gets a brand-new instance in the container."*

With Spring Cloud on the classpath (`spring-cloud-context`), a refresh (`POST /actuator/refresh`, the bus, etc. — mechanics in [§P4](06-spring-production.md#p4-externalized-configuration-at-scale-spring-cloud-config-and-runtime-refresh)) publishes an `EnvironmentChangeEvent`, and Spring Cloud then **re-binds `@ConfigurationProperties` beans**. What the Spring Cloud Commons reference says precisely:

- Re-binding **mutates the existing bean in place** — *"destroying and re-initializing the same instance rather than swapping it out for a new one."* Properties are first reset to class defaults (only if the class's sole constructor is no-arg), so removed keys don't linger.
- ⚠️ *"Objects using constructor binding including Java Records annotated with `@ConfigurationProperties` **cannot be refreshed**."*
- ⚠️ A concurrent reader may see a **half-updated** object during the rebind; if you need a consistent snapshot, use `@RefreshScope`.

| Setup | Picks up a refreshed value? |
|---|---|
| `@Value("${…}")` in a normal singleton | ❌ — frozen at startup. Needs `@RefreshScope` on the consuming bean |
| Mutable (setter) `@ConfigurationProperties` | ✅ in place, **no `@RefreshScope` needed** — every holder sees the new values |
| Record / constructor-bound `@ConfigurationProperties` | ❌ **not refreshed** — put `@RefreshScope` on it (or list it in `spring.cloud.refresh.extra-refreshable`) |
| `HikariDataSource` | ❌ listed in `spring.cloud.refresh.never-refreshable` by default — restart |

📌 **Correction:** the "new record instance" claim is wrong — the docs say records are not refreshed at all. If you need hot-reloadable config, use a **mutable** properties class, or annotate the record bean with `@RefreshScope`.

🔗 Related: [§C4](#c4-conditional-beans-and-auto-configuration-ordering) uses these same properties to decide **which beans exist**; [§P4](06-spring-production.md#p4-externalized-configuration-at-scale-spring-cloud-config-and-runtime-refresh) covers where the values come from at scale.

### C3.12 Actually reading a `.env` file [Q12]

Spring Boot won't read `.env` automatically, but you have three clean options.

#### 1. The modern native approach (Spring Boot 2.4+) — recommended

```properties
# add this to the top of application.properties
spring.config.import=optional:file:.env[.properties]
```

Breaking it down [Q12]:
- **`optional:`** — without this, **Spring Boot fails to start when the file is missing**. With it, the app still runs using env vars from your IDE, shell, container, or platform. Essential, since `.env` is gitignored and won't exist in prod.
- **`file:`** — read from the filesystem, relative to the working directory the app was started from.
- **`[.properties]`** — tells Spring to parse a file *without* a `.properties` extension using Java properties syntax.

You can import several; the **last one wins**.

⚠️ The values land as ordinary config properties, at **config-data** precedence (rank 3) — so real OS environment variables **override** your `.env` file. That's the right behaviour, and the opposite of how `dotenv` in Node behaves by default.

#### 2. The dependency approach (closest to `dotenv`) [Q12]

The maintained Spring integration is **`me.paulschwarz:spring-dotenv`**:

```xml
<dependency>
    <groupId>me.paulschwarz</groupId>
    <artifactId>spring-dotenv</artifactId>
    <version>5.1.0</version>
</dependency>
```
It registers a `Dotenv` **property source** into Spring's `Environment`, so `${MY_VAR}` in `application.properties` resolves from `.env`. It wraps `io.github.cdimascio:dotenv-java`, which is a plain Java library with **no** Spring integration of its own — so depend on `spring-dotenv`, not on `dotenv-java` directly. There's a `springboot4-dotenv` artifact under the same group for Spring Boot 4.

*Source: [github.com/paulschwarz/spring-dotenv](https://github.com/paulschwarz/spring-dotenv), [Maven Central](https://central.sonatype.com/artifact/me.paulschwarz/spring-dotenv)*

#### 3. IDE / local launch configuration [Q12]

Most Java developers inject `.env` locally via the IDE so production code stays untouched:
- **IntelliJ IDEA** — install the *EnvFile* plugin, edit your Run/Debug configuration, tick **Enable EnvFile**.
- **VS Code** — in `.vscode/launch.json`, add `"envFile": "${workspaceFolder}/.env"`.

### C3.13 Secrets — what not to do [+]

| ❌ Don't | ✅ Do |
|---|---|
| commit real secrets in `application-prod.yml` | inject via env vars from a secret manager |
| `password=hunter2` | `password=${DB_PASSWORD}` |
| bake secrets into the Docker image | mount them at runtime |
| log the whole `Environment` | scrub secrets; actuator masks by key name |

Kubernetes-native pattern — mount secrets as files and use a **config tree**:
```properties
spring.config.import=optional:configtree:/etc/secrets/
```
Each file under `/etc/secrets/` becomes a property named after its path. This is the cleanest way to consume K8s `Secret` volumes.

Other options: **Spring Cloud Config Server** (centralised, versioned config with refresh), **Spring Cloud Vault**, **AWS Secrets Manager**, and Jasypt for encrypted property values.

### C3.14 Side-by-side summary [+]

| | Python/FastAPI | Node/Express | Spring Boot |
|---|---|---|---|
| File | `.env` | `.env` | **`application.yml`** |
| Loader | `python-dotenv` | `dotenv` | **built in** |
| Typed config object | `pydantic-settings` | manual / `zod` | **`@ConfigurationProperties` + record** |
| Access a value | `settings.db_url` | `process.env.DB_URL` | `props.dbUrl()` or `@Value("${db.url}")` |
| Environments | `.env.production` | `NODE_ENV` | **profiles** (`application-prod.yml`) |
| Validation on boot | `pydantic` | none | **`@Validated`** |
| Missing required value | runtime error | `undefined` | **startup crash** ✅ |

---


## C4. Conditional beans and auto-configuration ordering

[§C1.3](#c13-how-auto-configuration-actually-works-q47) showed that Spring Boot's "magic" is just a pile of `@Conditional…` annotations on auto-configuration classes. This chapter puts the same tools in **your** hands: *create this bean only if…*

```
           startup, BEFORE any bean object exists
┌──────────────────────────────────────────────────────────┐
│ for each candidate bean definition:                      │
│    evaluate its @Conditional… annotations                │
│    ├─ all true  → register the definition                │
│    └─ any false → skip it — the bean never exists        │
└──────────────────────────────────────────────────────────┘
                         ▼
        beans are instantiated from the registered definitions
```

📌 **Key fact for every annotation below:** conditions are evaluated **once, at startup**, while bean *definitions* are being registered — not on each request, and not after beans are created. They decide *whether a bean exists*, not *which bean a caller gets per call*.

### C4.1 `@ConditionalOnProperty` — pick an implementation from config

> **Your scenario:** *"I have payment processing with two implementations, Stripe and PayPal, but I want only one of them created and injected at startup. If we autowire both we get 'expected single matching bean but found 2' — which @Primary could solve — but we want only one bean initialized."*

```java
public interface PaymentService { void pay(Order o); }

@Service
@ConditionalOnProperty(name = "payment.provider", havingValue = "paypal", matchIfMissing = true)
public class PayPalPaymentService implements PaymentService { … }

@Service
@ConditionalOnProperty(name = "payment.provider", havingValue = "stripe")
public class StripePaymentService implements PaymentService { … }
```
```yaml
payment:
  provider: stripe     # → only StripePaymentService is registered
```

| Attribute | Meaning |
|---|---|
| `name` (+ optional `prefix`) | the property key; several names → **all** must pass |
| `havingValue` | the value required. Compared **case-insensitively** (`"payPal"` matches `paypal` — verified in Boot's `OnPropertyCondition` source). If omitted: matches any value except `false` |
| `matchIfMissing` | `true` → the bean is created when the property is **absent** (this makes PayPal the default) |

> **Your questions:** *"Can I use application.yml, or only application.properties? Does it only initialize the bean conditionally, or inject it too? How to use @Primary and @ConditionalOnProperty together?"*

- **Any property source works** — `.yml`, `.properties`, env vars (`PAYMENT_PROVIDER=stripe`), `-D`, command line. The condition reads the `Environment`.
- **It controls registration only.** Injection is unchanged: when `Checkout(PaymentService p)` is built, Spring looks for beans of type `PaymentService`, finds exactly **one** (the other was never registered), and injects it. No `NoUniqueBeanDefinitionException`, no `@Primary` needed.
- **With `@Primary`:** you need it only when the conditions are *not* mutually exclusive. E.g. a `@Primary` always-on default plus an optional extra enabled by a feature flag; single-injection points get the primary, `List<PaymentService>` gets both.

🔗 Boot 3.5+ also has `@ConditionalOnBooleanProperty("feature.x.enabled")` for plain on/off flags. Your properties stay typed if you use [§C3.7](#c37-why-configurationproperties-exists--the-problems-with-many-values) for the values themselves.

### C4.2 `@ConditionalOnMissingBean` — a fallback when nothing else exists

> **Your scenario:** *"We have a NotificationService and an SNSNotificationService, but if for some reason that bean isn't initialized, I want a DefaultNotificationService — iff the SNS bean is not in the context."*

```java
@Configuration
public class NotificationConfig {
    @Bean
    @ConditionalOnMissingBean(NotificationService.class)   // checks by TYPE (an interface is fine)
    public NotificationService defaultNotificationService() {
        return new DefaultNotificationService();
    }
}
```
(With no argument, `@ConditionalOnMissingBean` on a `@Bean` method checks the method's return type.)

> **Your question:** *"Can we use @ConditionalOnMissingBean on the class directly, or only in a configuration class?"*

**Both compile and both run** — on a `@Component` class or on a `@Bean` method. The real issue is **ordering**, and here the Spring Boot reference is explicit:

> *"these conditions are evaluated based on what has been processed so far. For this reason, we recommend using only `@ConditionalOnBean` and `@ConditionalOnMissingBean` annotations on auto-configuration classes (since these are guaranteed to load after any user-defined bean definitions have been added)."*

📌 **Correction to the Gemini answer:** moving the condition from a `@Component` to a `@Bean` method in your own `@Configuration` class does **not** make it reliable. Your `@Configuration` classes are processed in the **same** component-scan phase as your `@Service`s; if `NotificationConfig` happens to be processed before `SnsNotificationService` is registered, the condition sees "no bean" and creates the default anyway — and you get two. Only **auto-configuration classes** ([§C4.7](#c47-auto-configuration-ordering--why-onbean-conditions-are-only-safe-there)) are guaranteed to run after all user definitions.

For your own application code, prefer conditions that don't depend on other beans:
```java
@Service @ConditionalOnProperty(name = "notification.provider", havingValue = "sns")
class SnsNotificationService implements NotificationService { … }

@Service @ConditionalOnProperty(name = "notification.provider", havingValue = "default", matchIfMissing = true)
class DefaultNotificationService implements NotificationService { … }
```
…or register both unconditionally and mark the real one `@Primary`. Save `@ConditionalOnMissingBean` for library/auto-config code where "back off if the user defined their own" is the goal.

### C4.3 `@ConditionalOnBean` — only if another bean exists

> **Your questions:** *"We want NotificationLogger only if some NotificationService bean exists. Can we require a particular type — only if SNSNotificationService is there, not if none or only DefaultNotificationService exists? Do we have to use a configuration class, or can we use it on a normal class-level bean?"*

```java
@Bean
@ConditionalOnBean(SnsNotificationService.class)    // a SPECIFIC implementation class
public NotificationLogger snsNotificationLogger() { return new NotificationLogger(); }
```

- **Yes, a specific type works.** `@ConditionalOnBean(SnsNotificationService.class)` matches only when a bean whose type is (or extends) `SnsNotificationService` is registered; with only `DefaultNotificationService`, or none, it's skipped. Use `@ConditionalOnBean(NotificationService.class)` for "any implementation". You can also match by `name = "snsNotificationService"` or by an annotation on the bean.
- **Class level or `@Bean` method** — both work, with exactly the same ordering caveat as §C4.2: the docs' recommendation applies to `@ConditionalOnBean` too.

📌 **Correction:** Gemini suggested `@DependsOn` to fix the ordering. `@DependsOn` controls the order beans are **instantiated**; conditions are evaluated earlier, during **definition registration**, so `@DependsOn` has no effect on them. (The Boot docs say the same about auto-config ordering: it affects registration order, not creation order.)

### C4.4 `@ConditionalOnClass` — only if a library is on the classpath

> **Your scenario:** *"Initialize RedisCacheManager iff RedisTemplate is on the classpath — which it is only when spring-boot-starter-data-redis is a dependency."*

```java
@Configuration
@ConditionalOnClass(name = "org.springframework.data.redis.core.RedisTemplate")
public class RedisCacheConfig {
    @Bean RedisCacheManager cacheManager(RedisConnectionFactory f) { return RedisCacheManager.create(f); }
}
```

📌 Small fix: the annotation takes a `Class` (`value = RedisTemplate.class`) **or** a `String` (`name = "…"`), not a bare string as the first argument. At **class level** the `value=` form is safe even when the class is missing, because Boot reads annotation metadata with ASM without loading the class. On a **`@Bean` method** it isn't — the JVM may load the return type first — so the docs recommend isolating it in a separate `@Configuration` class, or using `name=`.

> **Your question:** *"Does @ConditionalOnClass(SNSNotificationService.class) check whether that bean was initialized?"*

**No.** It checks only that the **`.class` file exists on the classpath** — not whether Spring created a bean from it. Your own `SnsNotificationService` is compiled into your jar, so it is *always* on the classpath, and the condition is *always* true — even if the bean was skipped by `@ConditionalOnProperty`. Rule of thumb:

| Question you're asking | Annotation |
|---|---|
| "Is this **library** a dependency?" | `@ConditionalOnClass` / `@ConditionalOnMissingClass` |
| "Did the container **create this bean**?" | `@ConditionalOnBean` / `@ConditionalOnMissingBean` |

### C4.5 Custom conditions — `Condition` + `@Conditional`

> **Your scenario:** *"Inject WeekendService only if today is Saturday or Sunday."*

```java
public class OnWeekendCondition implements Condition {     // org.springframework.context.annotation.Condition
    @Override
    public boolean matches(ConditionContext context, AnnotatedTypeMetadata metadata) {
        DayOfWeek today = LocalDate.now().getDayOfWeek();
        return today == DayOfWeek.SATURDAY || today == DayOfWeek.SUNDAY;
    }
}

@Service
@Conditional(OnWeekendCondition.class)      // or on a @Bean method in a @Configuration class
public class WeekendService { … }
```
(Fixes to the snippet in your notes: `LocalDate.now().getDayOfWeek()`, and the enum constants are upper-case `SATURDAY`/`SUNDAY`.)

⚠️ **Evaluated once at startup.** Start the app on Friday and `WeekendService` never exists for the life of that process, even on Saturday. For per-request decisions ("is it the weekend *now*?") use plain `if` logic or a strategy map ([§C2.11](#c211-resolving-ambiguity)), not a condition.

`ConditionContext` gives access to the `Environment`, the `BeanFactory`, the `ClassLoader` and the `ResourceLoader`, so a custom condition can check properties, files, OS, anything. Every built-in `@ConditionalOn…` is just a pre-written `Condition` of this shape.

### C4.6 `@ConditionalOnExpression` and `@Profile`

**`@ConditionalOnExpression`** — a SpEL boolean, for combinations `@ConditionalOnProperty` can't express:

```java
@Service
@ConditionalOnExpression(
    "${notification.enabled:true} and '${notification.provider:none}'.equalsIgnoreCase('sns')")
public class SnsNotificationLogger { … }
```
- `${…}` placeholders are resolved first, then the SpEL is evaluated; use `and`/`or`/`not` (or `&&`/`||`/`!`), comparisons, and `T(com.acme.Constants).LIMIT` for static constants.
- ⚠️ Always give placeholders a default (`:none`): an unresolvable placeholder is a startup error, not `false`.
- It's the most flexible and the least readable; prefer `@ConditionalOnProperty` when it suffices.

**`@Profile`**

> **Your question:** *"Profile means the environment our application is running in. Can we use profiles to create beans conditionally?"*

Yes — that is exactly what it does. `@Profile` *is* a condition: it is meta-annotated `@Conditional(ProfileCondition.class)`.

```java
@Service @Profile("prod")
public class SnsNotificationService implements NotificationService { … }    // real AWS in prod

@Service @Profile("!prod")
public class MockNotificationService implements NotificationService { … }   // console logging elsewhere
```
| Expression | Active when |
|---|---|
| `@Profile("prod")` | `prod` is active |
| `@Profile({"dev","staging"})` | `dev` **or** `staging` |
| `@Profile("prod & aws")` | both (Spring 5.1+ expression syntax) |
| `@Profile("!prod")` | `prod` is **not** active |

Activate with `spring.profiles.active=prod` (or `SPRING_PROFILES_ACTIVE=prod`) — [§C3.3](#c33-profiles-). `@Profile` works on `@Component` classes, `@Configuration` classes and `@Bean` methods.

### C4.7 Auto-configuration ordering — why `OnBean` conditions are only safe there

Boot solves the ordering problem from §C4.2 in two steps:

```
1. ALL user configuration is parsed first
   (@Component, @Service, your @Configuration classes, component scan)
        │   ← @EnableAutoConfiguration uses a *deferred* import selector,
        │     so auto-configs are processed only after this step
        ▼
2. Auto-configuration classes, SORTED, then evaluated one by one
   sort keys: @AutoConfiguration(after/before) · @AutoConfigureAfter/Before · @AutoConfigureOrder
```

So in an auto-configuration, `@ConditionalOnMissingBean(NotificationService.class)` **reliably** sees your own `NotificationService` and backs off — that's the "your bean always wins" rule.

```java
// Registered in META-INF/spring/org.springframework.boot.autoconfigure.AutoConfiguration.imports
@AutoConfiguration
public class NotificationAutoConfiguration {
    @Bean @ConditionalOnMissingBean(NotificationService.class)
    NotificationService defaultNotificationService() { return new DefaultNotificationService(); }
}

@AutoConfiguration(after = NotificationAutoConfiguration.class)    // evaluated AFTER the one above
public class NotificationMetricsAutoConfiguration {
    @Bean @ConditionalOnBean(NotificationService.class)
    NotificationMetrics notificationMetrics(NotificationService s) { return new NotificationMetrics(s); }
}
```

Rules (Spring Boot reference, "Creating Your Own Auto-configuration"):
- Auto-configurations are loaded **only** by being listed in the `.imports` file; they must **never** be picked up by component scan (put them outside your app's base package). `after`/`before` are **ignored** on ordinary `@Configuration` classes.
- `@AutoConfiguration` and the `.imports` file exist since **Boot 2.7**; Boot 2.x also still read `META-INF/spring.factories`, which Boot 3 dropped for auto-config.
- Ordering affects **registration** only — bean creation order still follows dependencies and `@DependsOn`.

This is mostly what you write when building a shared library/starter (in-house platform frameworks are built exactly this way). In ordinary application code, prefer §C4.1-style property/profile conditions.

### C4.8 Cheat sheet: the `@Conditional…` family

All in `org.springframework.boot.autoconfigure.condition` unless noted. Debug any of them with `--debug` / `GET /actuator/conditions` ([§C1.5](#c15-how-to-see-what-boot-decided-q47)), which prints each positive and negative match with the reason.

| Annotation | Matches when | Typical use |
|---|---|---|
| `@Conditional(MyCondition.class)` *(Spring Framework)* | your `Condition.matches()` returns true | anything custom |
| `@Profile("prod")` *(Spring Framework)* | the profile expression matches | real vs mock integrations |
| `@ConditionalOnProperty` | property present / equals `havingValue` (case-insensitive) | feature flags, choosing a provider |
| `@ConditionalOnBooleanProperty` | boolean property is true (Boot **3.5+**) | on/off flags |
| `@ConditionalOnExpression` | a SpEL expression is true | multi-property logic |
| `@ConditionalOnClass` / `@ConditionalOnMissingClass` | class is / isn't on the classpath | enable Redis config only with the Redis library |
| `@ConditionalOnBean` / `@ConditionalOnMissingBean` | bean of type/name is / isn't registered *(auto-config only, see §C4.2)* | back-off defaults |
| `@ConditionalOnSingleCandidate` | exactly one bean of the type, or one `@Primary` | auto-wire a `JdbcTemplate` to the single `DataSource` |
| `@ConditionalOnResource` | a resource exists (`classpath:keystore.jks`) | SSL setup only when the file is bundled |
| `@ConditionalOnWebApplication(type = SERVLET\|REACTIVE\|ANY)` / `@ConditionalOnNotWebApplication` | it is / isn't a web app | register filters only in web apps |
| `@ConditionalOnWarDeployment` / `@ConditionalOnNotWarDeployment` | deployed as a WAR / not | container-specific config |
| `@ConditionalOnJava(JavaVersion.TWENTY_ONE)` | JVM version (range) | Java-21-only features |
| `@ConditionalOnThreading(Threading.VIRTUAL)` | virtual threads enabled via `spring.threads.virtual.enabled` (Boot **3.2+**) | pick executor type |
| `@ConditionalOnCloudPlatform(CloudPlatform.KUBERNETES)` | detected platform: `KUBERNETES`, `CLOUD_FOUNDRY`, `HEROKU`, `SAP`, `NOMAD`, `AZURE_APP_SERVICE`, `AWS_ECS` (newer Boot) | platform-specific beans |

📌 **Correction to the Gemini cheat sheet:** `CloudPlatform` has no generic `AWS`, `AZURE` or `GCP` values — the list above is the actual enum (Boot `main` source). `AWS_ECS` exists only in recent versions.

🔗 Where you've seen these: Boot's own `DispatcherServletAutoConfiguration` ([§C1.3](#c13-how-auto-configuration-actually-works-q47)), `AopAutoConfiguration` ([§C6.11](#c611-the-dependency-and-why-it-works-without-enableaspectjautoproxy-)), and the security default chain that backs off when you declare your own ([§S2](05-spring-security.md#s2-authentication-who-are-you)).


## C5. Proxies: JDK dynamic proxies, CGLIB, and @Configuration full vs lite mode

Half of Spring's features — `@Transactional`, `@Async`, `@Cacheable`, `@Retryable`, `@PreAuthorize`, scoped beans, `@Lookup`, `@Configuration` — work by **handing you a different object than the one you wrote**. This chapter is about that object. Read it before AOP ([§C6](#c6-aspect-oriented-programming-aop-)); AOP is the main *user* of it.

### C5.1 What a proxy is

A **proxy** is a stand-in object with the same type as your bean. Callers hold the proxy; the proxy does something extra, then (usually) calls your real object.

```
 caller ──► PROXY (same type as OrderService) ──► real OrderService
              │ start transaction / check auth / retry / look up scoped target
              └─ after the call: commit / record metric …
```

Spring creates proxies in one of two ways:

| | **JDK dynamic proxy** | **CGLIB proxy** |
|---|---|---|
| Technology | `java.lang.reflect.Proxy` — built into the JDK | bytecode generation — CGLIB, **repackaged inside `spring-core`** (`org.springframework.cglib`) so you add no dependency |
| What it generates | a new class that **implements your interfaces** | a new **subclass of your class** |
| Needs an interface? | ✅ yes | ❌ no |
| Inject by concrete class (`OrderServiceImpl`)? | ❌ the proxy isn't one | ✅ it *is* a subclass |
| Can't intercept | anything not on the interface | `final` classes, `final`/`private`/`static` methods |
| Spring Boot default | only if `spring.aop.proxy-target-class=false` | ✅ **default since Boot 2.0** — even for beans that do implement interfaces ([§C6.11](#c611-the-dependency-and-why-it-works-without-enableaspectjautoproxy-)) |

### C5.2 JDK dynamic proxies in 15 lines

```java
interface Greeter { String greet(String name); }
class RealGreeter implements Greeter { public String greet(String n) { return "Hi " + n; } }

Greeter real = new RealGreeter();
Greeter proxy = (Greeter) Proxy.newProxyInstance(
        Greeter.class.getClassLoader(),
        new Class<?>[]{ Greeter.class },                 // the interfaces to implement
        (p, method, args) -> {                           // InvocationHandler — runs on EVERY call
            System.out.println("before " + method.getName());
            Object result = method.invoke(real, args);   // delegate to the real object
            System.out.println("after");
            return result;
        });
proxy.greet("Ana");     // before greet / after → "Hi Ana"
```

That's the whole mechanism: one handler sees every interface method. 🐍 Comparable to a class with `__getattr__` that forwards to a wrapped object; 🟨 a JavaScript `Proxy` with a `get` trap.

### C5.3 CGLIB: what it is and how it works

> **Your question:** *"What is CGLIB proxy?"*

**CGLIB (Code Generation Library)** writes a new class's bytecode **at runtime, in memory**, as a **subclass** of your class, and loads it. Spring uses it whenever a bean has no interface — which, with Boot's default, means nearly always.

```java
// What Spring effectively generates for a @Transactional OrderService (conceptually):
class OrderService$$SpringCGLIB$$0 extends OrderService {
    @Override
    public void placeOrder(Order o) {
        // run the interceptor chain: begin tx …
        target.placeOrder(o);          // the REAL OrderService instance
        // … commit / rollback
    }
}
```
(Class names look like `OrderService$$SpringCGLIB$$0` in Spring 6+, `OrderService$$EnhancerBySpringCGLIB$$1a2b3c` in Spring 5 / Boot 2.7 — you'll see them in stack traces and `getClass()`.)

Rules that follow directly from "it's a subclass":

| Rule | Why | Symptom if broken |
|---|---|---|
| The class must not be `final` | can't extend a final class | startup error: *Cannot subclass final class* |
| `final` methods are not intercepted | can't override them | advice silently skipped — and ⚠️ the final method runs **on the proxy instance**, whose fields are `null` → NPE on injected fields |
| `private` methods are not intercepted | not visible to subclasses | `@Transactional private void x()` silently non-transactional |
| `static` methods are not intercepted | not instance dispatch | silently skipped |
| **Self-invocation bypasses it** | `this.methodB()` inside the target calls the real object, never the subclass override | the #1 Spring bug — [§C6.9](#c69-the-gotchas-that-will-actually-bite-you-) |

Two internals worth knowing:
- **Constructors don't run twice.** Since Spring 4, CGLIB proxy instances are created through **Objenesis**, which allocates the object without calling a constructor. Your constructor runs once — for the real target.
- **Records and Kotlin classes are `final`** — records can't be CGLIB-proxied at all; Kotlin needs the `kotlin-spring` (all-open) plugin.

🔗 The same subclass trick powers scoped proxies and `@Lookup` ([§C2.10](#c210-a-prototype-inside-a-singleton-objectprovider-scoped-proxies-and-lookup)), AOP ([§C6](#c6-aspect-oriented-programming-aop-)), Spring Retry and Resilience4j annotations ([§P2](06-spring-production.md#p2-resilience-retries-recovery-and-circuit-breakers)), and method security ([§S4](05-spring-security.md#s4-authorization-what-are-you-allowed-to-do)).

### C5.4 `@Configuration` full mode vs lite mode

```java
@Configuration                                   // FULL mode (proxyBeanMethods = true, the default)
public class AppConfig {
    @Bean public Clock clock() { return Clock.systemUTC(); }

    @Bean public OrderService orderService() {
        return new OrderService(clock());        // ← intercepted! returns THE singleton Clock bean
    }
    @Bean public InvoiceService invoiceService() {
        return new InvoiceService(clock());      // ← same Clock instance again
    }
}
```

In **full mode** Spring CGLIB-subclasses the `@Configuration` class itself. The subclass overrides every `@Bean` method: "if this bean already exists in the container, return it; otherwise call `super` and register the result." So calling `clock()` from another `@Bean` method respects singleton scope.

In **lite mode** there is no subclass — `clock()` is an ordinary Java call and builds a **new** `Clock` each time:

| | Full mode | Lite mode |
|---|---|---|
| Declared by | `@Configuration` (default) | `@Configuration(proxyBeanMethods = false)`, or `@Bean` methods in a `@Component` / plain class |
| Config class is CGLIB-proxied | ✅ | ❌ |
| `@Bean` calling `@Bean` | returns the container's singleton | ⚠️ plain call → **duplicate object** |
| Startup cost | slightly higher | lower — that's why Boot's own auto-configs use `proxyBeanMethods = false` |
| Safe style | either | **take dependencies as `@Bean` method parameters** instead of calling other `@Bean` methods |

```java
@Configuration(proxyBeanMethods = false)
public class AppConfig {
    @Bean Clock clock() { return Clock.systemUTC(); }
    @Bean OrderService orderService(Clock clock) { return new OrderService(clock); }   // ✅ injected, no call
}
```

📌 This parameter style works in both modes and is what you should write by default. It also explains [§C2.14](#c214-running-code-once-at-startup-commandlinerunner-and-applicationrunner)'s answer: a `@Bean` in a `@Component` still registers a bean — it just runs in lite mode.

### C5.5 Seeing the proxy for yourself

```java
@Autowired OrderService orderService;
System.out.println(orderService.getClass().getName());     // com.acme.OrderService$$SpringCGLIB$$0
System.out.println(AopUtils.isAopProxy(orderService));     // true (if any advice applies)
System.out.println(AopUtils.getTargetClass(orderService)); // class com.acme.OrderService
```

If a bean has no `@Transactional`/`@Async`/aspect applying to it, **no proxy is created** and `getClass()` is your class — proxies are added only when something needs them (in `postProcessAfterInitialization`, [§C2.9](#c29-scopes-and-the-bean-lifecycle)).

## C6. Aspect-Oriented Programming (AOP) [+]

You already met AOP without being told. `@Transactional` ([§D4.1](04-spring-data.md#d41-transactions-)), `@Cacheable`, `@Async`, and Spring Security's method security ([§S4.5](05-spring-security.md#s45-programmatic--method-level-security-q34-q40)) are all AOP. This section explains the machinery underneath, because once you can see it you can both use it deliberately and debug it when it silently does nothing.

**Verified against** Spring Framework 7.0 reference documentation and the `AopAutoConfiguration` source in Spring Boot's `main` branch.

---

### C6.1 The problem AOP solves [+]

Two words name the pain, and they are worth learning because they are how the literature talks about it:

- **Code scattering** — one concern (say, timing) spread across 50 methods.
- **Code tangling** — one method containing several concerns (business logic *and* timing *and* transactions *and* auth).

Here is tangling, concretely. The business logic is four lines; the file is thirty:

```java
@Service
public class OrderService {
    @Autowired private OrderRepository repository;
    @Autowired private PlatformTransactionManager txManager;

    public void processOrder(Order order) {
        long start = System.currentTimeMillis();                              // timing
        log.info("Starting processOrder for {}", order.getCustomerId());      // logging
        TransactionStatus status =                                            // transaction
            txManager.getTransaction(new DefaultTransactionDefinition());
        try {
            repository.save(order);          // ← the only two lines that are the point
            repository.updateInventory(order);
            txManager.commit(status);                                         // transaction
        } catch (Exception e) {
            txManager.rollback(status);                                       // transaction
            log.error("Failed to process order", e);                          // logging
            throw e;
        } finally {
            log.info("Finished in {}ms", System.currentTimeMillis() - start); // timing
        }
    }
}
```

And here it is untangled:

```java
@Service
public class OrderService {
    private final OrderRepository repository;

    @Transactional          // ← AOP supplies the transaction
    @LogExecutionTime       // ← your own aspect supplies timing + logging
    public void processOrder(Order order) {
        repository.save(order);
        repository.updateInventory(order);
    }
}
```

📌 **Why a DAO/repository layer does not solve this.** A repository isolates *data access*. It does nothing about timing, auth or transactions — in fact a repository that also logs and checks permissions has exactly the tangling problem, one layer down. The two patterns are orthogonal: the repository answers *"where does data live?"*, AOP answers *"what must happen around every call?"*

---

### C6.2 Why not just the Decorator pattern? [+]

You are right that the Decorator pattern solves the same *logical* problem. It fails on **scale and coupling**:

| | Decorator | Spring AOP |
|---|---|---|
| To cover 100 services | write 100 wrapper classes | write 1 aspect + 1 pointcut |
| A service has 10 methods | override all 10 in the wrapper | automatic |
| You add an 11th method | you must remember to update the wrapper | automatic |
| Wiring | manual, per class | done by the container |
| Turning it off | delete/rewire every wrapper | delete one annotation |

**So why is AOP a *proxy* rather than a decorator?** The two patterns are structurally near-identical — both wrap an object and implement its interface. The difference is who writes the wrapper and when:

- A **Decorator** is a class *you* write at compile time, wrapping an object *you* pass in.
- A **Proxy** here is a class the framework *generates at runtime*, and the container substitutes it for the real bean everywhere it is injected. Nobody in your codebase knows the swap happened.

That substitution is the whole trick, and it is also the source of every AOP gotcha in [§C6.9](#c69-the-gotchas-that-will-actually-bite-you-).

📌 **This is not "AOP vs. Decorator", it is "generated Decorator vs. hand-written Decorator".** If you understand `functools.wraps` in Python you already understand the shape; see [§C6.10](#c610-the-pythonfastapi-translation-).

---

### C6.3 The architecture, drawn [+]

Your sketch was close. One correction: a **DTO is never the target**. A DTO is a passive data holder with no behaviour to intercept. AOP targets *behavioural* beans — services, repositories, components.

**Startup — how the swap happens:**

```
  ┌─────────────────────────────────────────────────────────────────┐
  │ APPLICATION STARTUP                                             │
  │                                                                 │
  │  1. Component scan finds  @Service OrderService                 │
  │  2. Component scan finds  @Aspect @Component LoggingAspect      │
  │  3. AnnotationAwareAspectJAutoProxyCreator (a BeanPostProcessor)│
  │     asks: "does any pointcut match any method of OrderService?" │
  │  4. YES →  generate a proxy class at runtime (CGLIB subclass)   │
  │  5. Register the PROXY in the context under name "orderService" │
  │     The real OrderService instance is kept INSIDE the proxy.    │
  └─────────────────────────────────────────────────────────────────┘
```

⚠️ Step 5 is the one to remember: **what gets injected everywhere is the proxy, not your object.**

**Runtime — what one call looks like:**

```
   OrderController
        │  orderService.processOrder(order)
        ▼
 ┌──────────────────────────────────────────────────────────────┐
 │  PROXY  (class OrderService$$SpringCGLIB$$0 extends OrderService)
 │                                                              │
 │   interceptor chain, ordered by @Order:                      │
 │   ┌────────────────────────────────────────────────────┐     │
 │   │ SecurityAspect     @Order(1)   ── before ──┐       │     │
 │   │  ┌─────────────────────────────────────────▼────┐  │     │
 │   │  │ TxInterceptor   @Order(2)  ── begin tx ──┐   │  │     │
 │   │  │  ┌───────────────────────────────────────▼─┐ │  │     │
 │   │  │  │ LoggingAspect @Order(3) ── start timer ─┼─┼──┼─────┼──┐
 │   │  │  │                                         │ │  │     │  │
 │   │  │  │   ◄── return value ──────────────────┐  │ │  │     │  │
 │   │  │  │ LoggingAspect          ── log time ──┘  │ │  │     │  │
 │   │  │  └─────────────────────────────────────────┘ │  │     │  │
 │   │  │ TxInterceptor              ── commit ────────┘  │     │  │
 │   │  └────────────────────────────────────────────────┘      │  │
 │   │ SecurityAspect              ── (nothing after) ──────────┘  │
 │   └─────────────────────────────────────────────────────────┐   │
 └──────────────────────────────────────────────────────────────┘  │
                                                                   ▼
                                              ┌─────────────────────────────┐
                                              │ TARGET: the real            │
                                              │ OrderService instance       │
                                              │  repository.save(order)     │
                                              └─────────────────────────────┘
```

📌 Note the **nesting**, not a flat list. Highest precedence is *outermost*: it runs first going in and last coming out — exactly like middleware in Express or FastAPI.

---

### C6.4 Terminology, in plain words [+]

The airport-security analogy is a good one, so let's keep it precise:

| Term | Plain meaning | Airport | In code |
|---|---|---|---|
| **Join point** | a place where advice *could* run | every gate, desk and corridor | ⚠️ **in Spring AOP: a method execution on a Spring bean, and nothing else** |
| **Pointcut** | a rule selecting *which* join points | "only international departures at Gate B" | `execution(* com.acme.service.*.*(..))` |
| **Advice** | the code that runs, and when | "check passports, before boarding" | the `@Before`-annotated method |
| **Aspect** | the module bundling pointcuts + advice | the Security Checkpoint department | the `@Aspect` class |
| **Target** | the object being advised | the passenger | your `OrderService` |
| **Weaving** | linking aspects to targets | installing the checkpoints | [§C6.8](#c68-weaving-spring-aop-vs-aspectj-) |
| **Introduction** | adding new methods/interfaces to a type | — | `@DeclareParents` (rare) |

---

### C6.5 The five advice types [+]

| Advice | Runs | Can see return value? | Can see exception? | Can change outcome? |
|---|---|---|---|---|
| `@Before` | before the method | ❌ | ❌ | ❌ (only by throwing) |
| `@AfterReturning` | after **successful** return | ✅ | ❌ | ❌ (can mutate the object, not replace it) |
| `@AfterThrowing` | after an exception | ❌ | ✅ | ❌ — **cannot suppress it** |
| `@After` | always ("after finally") | ❌ | ❌ | ❌ |
| `@Around` | wraps everything | ✅ | ✅ | ✅ **everything** |

```java
@Aspect
@Component
public class DemoAspect {

    @Before("execution(* com.acme.service.*.*(..))")
    public void before(JoinPoint jp) {
        System.out.println("before " + jp.getSignature().getName());
    }

    @AfterReturning(pointcut = "execution(* com.acme.service.*.find*(..))", returning = "result")
    public void afterReturning(JoinPoint jp, List<Account> result) {
        System.out.println("returned " + result.size() + " accounts");
    }

    @AfterThrowing(pointcut = "execution(* com.acme.service.*.*(..))", throwing = "ex")
    public void afterThrowing(JoinPoint jp, Throwable ex) {
        System.out.println("failed: " + ex.getMessage());   // logs, then the exception continues
    }

    @After("execution(* com.acme.service.*.*(..))")
    public void afterFinally(JoinPoint jp) {
        System.out.println("always runs — success or failure");
    }

    @Around("execution(* com.acme.service.*.*(..))")
    public Object around(ProceedingJoinPoint pjp) throws Throwable {
        long t0 = System.nanoTime();
        try {
            return pjp.proceed();                       // ← the target actually runs here
        } finally {
            System.out.println((System.nanoTime() - t0) / 1_000_000 + "ms");
        }
    }
}
```

#### The `returning` / `throwing` attributes — two rules, not one

You asked whether the names must match. **Yes**, and there is a second rule nobody mentions:

**Rule 1 — the name binds the value.** The string in `returning = "result"` must equal a parameter name in the advice method. Spring injects the returned object into that parameter. The variable name *inside the target method* is irrelevant — Spring binds by the annotation string, not by source-level names.

**Rule 2 — ⚠️ the declared type also filters the pointcut.** From the Spring documentation: *"A `returning` clause also restricts matching to only those method executions that return a value of the specified type."* The same is true of `throwing`.

```java
// This does NOT advise every find* method — only those returning List<Account>.
// A find* method returning Optional<Account> is silently skipped.
@AfterReturning(pointcut = "execution(* ...find*(..))", returning = "result")
public void advice(JoinPoint jp, List<Account> result) { }

// Use Object to match everything:
@AfterReturning(pointcut = "execution(* ...find*(..))", returning = "result")
public void advice(JoinPoint jp, Object result) { }
```

📌 "My advice isn't firing" is very often this: the declared parameter type quietly narrowed the pointcut.

#### ⚠️ `@AfterThrowing` cannot swallow an exception

It is an **observer**. It logs, alerts, increments a metric — then the exception continues propagating exactly as before. The docs add a subtlety worth knowing: *"an `@AfterThrowing` advice method is only supposed to receive exceptions from the join point (user-declared target method) itself but not from an accompanying `@After`/`@AfterReturning` method."*

**To stop an exception you must use `@Around`** — see [§C6.7](#c67-around-total-control-).

#### Choosing an advice type

| You want to… | Use |
|---|---|
| validate inputs, log entry | `@Before` |
| log or audit a successful result | `@AfterReturning` |
| alert/metric on failure, without changing behaviour | `@AfterThrowing` |
| release a resource regardless of outcome | `@After` |
| time it, cache it, retry it, change args, change result, swallow errors | `@Around` |

📌 **Real-world ratio.** In a large production codebase I checked, `@Around` appeared in about **100** files, `@Pointcut` in about 20, and `@Before` in **3**. When teams reach for AOP they almost always want full control. Start with `@Around` unless a narrower advice clearly suffices — but see the `@Around` + `CompletableFuture` trap in [§C6.9](#c69-the-gotchas-that-will-actually-bite-you-).

---
### C6.6 Pointcut expressions in full [+]

Spring AOP borrows AspectJ's **expression language** (not its weaver — see [§C6.8](#c68-weaving-spring-aop-vs-aspectj-)).

#### The `execution()` signature

The official grammar, with the optional parts marked:

```
execution( modifiers-pattern?  ret-type-pattern  declaring-type-pattern? name-pattern(param-pattern)  throws-pattern? )
```

*"All parts except the returning type pattern, the name pattern, and the parameters pattern are optional."*

```
              any modifier   any return type    package + any sub-package
                    │              │                      │
   execution(    public            *       com.acme..*.AccountDAO.add*(..)  )
                                                            │        │   │
                          class named AccountDAO ───────────┘        │   │
                          method name starting "add" ────────────────┘   │
                          any number of args of any type ────────────────┘
```

#### Every wildcard

| Token | Meaning |
|---|---|
| `*` | exactly one element — one return type, one name part, one package level, one argument |
| `..` | in a **package** position: this package *and all sub-packages*. In an **argument** position: zero or more arguments of any type |
| `+` | "this type **or any subtype**" — e.g. `within(com.acme.BaseDao+)` |

**On the dot, since you asked specifically:** `.` is always a separator, never a prefix.

- `com.acme.dao.*` → classes **directly inside** `com.acme.dao`, not in sub-packages.
- `com.acme.dao..*` → `com.acme.dao` **and everything nested below it**.
- `com.acme.dao.*.get*(..)` → parses as `com.acme.dao.*` (any class in that package) `.` `get*` (any method starting with `get`).

#### Argument patterns

| Pattern | Matches |
|---|---|
| `()` | no arguments |
| `(..)` | any number of arguments, any types |
| `(*)` | exactly one argument, any type |
| `(*, String)` | exactly two; second must be `String` |
| `(com.acme.Account, ..)` | first is an `Account`, then anything |

#### All ten designators Spring AOP supports

| Designator | Selects by | Example |
|---|---|---|
| `execution` | method signature — **the workhorse** | `execution(* com.acme.service.*.*(..))` |
| `within` | the declaring **type/package** | `within(com.acme.dao..*)` |
| `this` | the **proxy** is an instance of a type | `this(com.acme.AccountService)` |
| `target` | the **target object** is an instance of a type | `target(com.acme.AccountService)` |
| `args` | **runtime argument types** | `args(java.io.Serializable)` |
| `@annotation` | an annotation **on the method** | `@annotation(com.acme.Audited)` |
| `@target` | an annotation **on the target's class** | `@target(org.springframework.stereotype.Repository)` |
| `@within` | declared in a type carrying an annotation | `@within(com.acme.Audited)` |
| `@args` | runtime arg types carry an annotation | `@args(com.acme.Validated)` |
| `bean` | **Spring bean name** (Spring-only extension) | `bean(*Service)` |

⚠️ **Designators AspectJ has that Spring AOP does not**: `call`, `get`, `set`, `preinitialization`, `staticinitialization`, `initialization`, `handler`, `adviceexecution`, `withincode`, `cflow`, `cflowbelow`, `if`, `@this`, `@withincode`. *"Use of these pointcut designators in pointcut expressions interpreted by Spring AOP results in an `IllegalArgumentException` being thrown."* Note `get`/`set` in that list — **that is why Spring AOP cannot intercept field access.**

📌 **`this` vs `target`** exists because of the proxy: *"Spring AOP is a proxy-based system and differentiates between the proxy object itself (which is bound to `this`) and the target object behind the proxy (which is bound to `target`)."*

#### Can an aspect apply to a whole class, or to fields?

- **Classes:** yes, indirectly. `within(com.acme.AccountService)` or `@within(...)` means "every matched method execution *declared in* that class." There is no "class-level join point" — it expands to its methods.
- **Fields:** ❌ not in Spring AOP (`get`/`set` are unsupported). Only full AspectJ can do this.
- **Constructors:** ❌ not in Spring AOP. Only AspectJ.

> **Is AOP like Python's `Protocol` (structural subtyping)?** No — they solve unrelated problems. `Protocol` is a *static type-checking* feature describing a shape an object must have. AOP is *runtime behaviour injection*. Python's real analogue to AOP is the decorator (see [§C6.10](#c610-the-pythonfastapi-translation-)).

#### Named pointcuts — the "variable" for expressions

Declare once, reuse everywhere. The method must return `void` and its body is empty — it exists only to carry the name.

```java
@Aspect
@Component
public class CommonPointcuts {

    @Pointcut("execution(* com.acme.demo.dao.*.*(..))")
    public void allDaoMethods() {}

    @Pointcut("execution(* com.acme.demo.dao.*.get*(..))")
    public void getters() {}

    @Pointcut("execution(* com.acme.demo.dao.*.set*(..))")
    public void setters() {}
}
```

Benefits, exactly as you listed: reuse, one place to update, and composability.

#### Combining with `&&`, `||`, `!`

```java
@Before("com.acme.demo.CommonPointcuts.allDaoMethods() "
      + "&& !(com.acme.demo.CommonPointcuts.getters() "
      + "|| com.acme.demo.CommonPointcuts.setters())")
public void logMutatingOperations(JoinPoint jp) { … }
```

Your intuition was right — they are ordinary boolean operators, and the advice runs only where the combined expression is true. Normal Java visibility applies when referencing a pointcut from another class (`private` pointcuts are visible only within the same type).

#### ⚠️ Narrow your pointcuts

A wildcard like `execution(* *.add*(..))` will happily match methods in libraries added to your classpath next quarter. The industry rule is to anchor every pointcut to your own root package:

```java
@Before("execution(* com.acme.demo.dao.*.add*(..))")   // ✅ anchored
@Before("execution(* add*(..))")                       // ❌ matches the world
```

#### Why pointcut strings need fully-qualified class names

Your reasoning was right, and here is the mechanism: **the pointcut is a `String`**. It is parsed by AspectJ's expression parser at runtime, which has no access to your file's `import` statements — those are a *compile-time* convenience that the compiler erases. The parser only ever sees the characters between the quotes.

```java
import com.acme.demo.model.Account;                    // ← invisible to the pointcut parser

@Before("execution(* com.acme.demo.dao.AccountDAO.addAccount(com.acme.demo.model.Account, ..))")
//                                                            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ required
```

Inside ordinary Java code the import makes `Account` sufficient. Inside a pointcut string it never is. (`java.lang` types like `String` are the practical exception.)

#### Reading arguments at runtime

Two ways. The blunt one:

```java
@Before("execution(* com.acme.demo.dao.AccountDAO.addAccount(..))")
public void logArgs(JoinPoint jp) {
    for (Object arg : jp.getArgs()) {              // Object[] — see below
        if (arg instanceof Account account) {      // Java 16+ pattern matching; no explicit cast
            System.out.println("name=" + account.getName() + " level=" + account.getLevel());
        }
    }
}
```

**Why the downcast?** `getArgs()` returns `Object[]` because one advice method can intercept thousands of different signatures — `(String, int)` here, `(Account, boolean)` there. There is no single static type that could describe them all, so the API erases to `Object`. You recover the type with `instanceof` (and modern Java folds the cast into the pattern, so you no longer write `(Account) arg`).

📌 **The better way — bind the argument in the pointcut.** Then Spring hands you a typed parameter and *also* narrows matching to methods with that signature:

```java
@Before("execution(* com.acme.demo.dao.AccountDAO.addAccount(..)) && args(account, isNew)")
public void logArgs(Account account, boolean isNew) {      // typed, no cast, no instanceof
    System.out.println("name=" + account.getName() + " isNew=" + isNew);
}
```

`JoinPoint` also gives you `getSignature()`, `getTarget()` (the real object) and `getThis()` (the proxy).

---

### C6.7 `@Around`: total control [+]

#### What it can do that `@Before` + `@After` cannot

This is the key question, and the answer is four things:

1. **Skip the target entirely** — return a cached value without calling `proceed()`.
2. **Change the arguments** — `pjp.proceed(newArgs)`.
3. **Change the return value** — return something other than what `proceed()` produced.
4. **Swallow or translate exceptions** — catch and return a fallback.

`@Before` and `@After` can only observe and throw. `@Around` *is* the call.

#### How it knows "before" from "after"

There is no flag. **`proceed()` is the boundary**: everything above it is "before", everything below is "after". That is all.

```java
@Around("@annotation(com.acme.Timed)")
public Object around(ProceedingJoinPoint pjp) throws Throwable {
    // ── everything here is "before" ──
    Object result = pjp.proceed();        // ← the target method runs, right here
    // ── everything here is "after" ──
    return result;
}
```

#### The rules (from the reference docs)

- The first parameter **must** be `ProceedingJoinPoint`.
- The return type **should be `Object`**: *"If you declare the return type of your around advice method as `void`, `null` will always be returned to the caller, effectively ignoring the result of any invocation of `proceed()`."*
- *"`proceed` may be invoked once, many times, or not at all within the body of the around advice. All of these are legal."* (Many times = a retry aspect. Not at all = a cache or a circuit breaker.)

#### Worked example: a custom annotation + centralised 4xx handling

**1. The marker annotation**

```java
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)   // ⚠️ MUST be RUNTIME or Spring cannot see it
public @interface SmartInterceptor {}
```

⚠️ `RetentionPolicy.RUNTIME` is not optional. The default is `CLASS`, which means the annotation is discarded before the JVM loads it, and your pointcut silently matches nothing.

**2. The aspect**

```java
@Aspect
@Component
public class ExecutionMonitoringAspect {

    @Around("@annotation(smartInterceptor)")          // binds the annotation instance as a parameter
    public Object processLifecycle(ProceedingJoinPoint pjp, SmartInterceptor smartInterceptor)
            throws Throwable {

        long start = System.currentTimeMillis();
        String method = pjp.getSignature().toShortString();

        try {
            Object output = pjp.proceed();
            log.info("{} completed in {}ms", method, System.currentTimeMillis() - start);
            return output;

        } catch (IllegalArgumentException clientError) {
            // 4xx-class: translate to a safe fallback instead of a 500
            log.warn("client error in {}: {}", method, clientError.getMessage());
            return List.of();

        } catch (Throwable systemError) {
            log.error("system failure in {}", method, systemError);
            throw systemError;                         // ← preserves the original stack trace
        }
    }
}
```

📌 **On centralised exception handling generally:** you *can* do it in an aspect, but for a web application `@RestControllerAdvice` + `@ExceptionHandler` ([§W8.8](03-spring-web.md#w88-global-exception-handling-with-problemdetail-)) is the right tool — it knows about HTTP status codes, content negotiation and `ProblemDetail`, which an aspect does not. Use an aspect when the concern is not HTTP-shaped: retries, fallbacks, bulkheads.

#### Rethrowing and stack traces

| Pattern | Stack trace | Verdict |
|---|---|---|
| `catch (Throwable ex) { throw ex; }` | fully preserved, original origin intact | ✅ |
| `throw new DomainException("…", ex)` | new frame added, original kept under `Caused by:` | ✅ when you deliberately translate |
| `throw new DomainException("…")` | ⚠️ **original lost forever** | ❌ never do this |
| `return fallback;` (swallow) | caller never learns anything went wrong | ⚠️ only with a *meaningful* fallback |

**Is swallowing bad?** Only when done blindly. It is legitimate for: returning stale cache when a dependency is down, degrading a non-essential feature, or converting a raw infrastructure exception into a clean domain result. It is harmful when the caller then proceeds on empty data believing it is real — the classic follow-on `NullPointerException`. The rule: **swallow only when you can return something the caller can correctly act on**, and always record a metric so the failure stays visible.

---

### C6.8 Weaving: Spring AOP vs AspectJ [+]

**Weaving** = linking aspects into target code to produce advised objects. *When* it happens is the whole difference between the two frameworks.

| Weaving | When | How | Cost |
|---|---|---|---|
| **Compile-time (CTW)** | at build | the AspectJ compiler `ajc` writes the advice into the `.class` files | fastest at runtime; needs `ajc` in the build |
| **Post-compile (binary)** | after build | `ajc` weaves already-compiled jars | for third-party code you cannot recompile |
| **Load-time (LTW)** | at class load | a JVM agent rewrites bytecode as the `ClassLoader` reads it | needs `-javaagent`; near-CTW speed afterwards |
| **Runtime (proxy)** | at container startup | Spring generates proxy subclasses | no build changes; per-call indirection |

#### The comparison

| | Spring AOP | AspectJ |
|---|---|---|
| Join points | **method execution only** | method, constructor, **field get/set**, static init, exception handler |
| Applies to | **Spring beans only** | any object, including `new Account()` |
| Weaving | runtime proxies | compile-time / post-compile / load-time |
| `private` / `final` methods | ❌ cannot advise | ✅ can |
| Self-invocation ([§C6.9](#c69-the-gotchas-that-will-actually-bite-you-)) | ❌ **broken** | ✅ works |
| Setup | zero — a starter | build plugin or `-javaagent` + `aop.xml` |
| Per-call overhead | small but real | essentially none |

#### Which to use

**Use Spring AOP** for ~90% of applications: transactions, caching, security, method logging on Spring beans. Zero build configuration.

**Use AspectJ** when you need any of: field interception, constructor interception, advising `private` methods, advising objects Spring did not create, self-invocation to work, or the absolute minimum overhead.

📌 The two are not exclusive: Spring AOP *uses AspectJ's annotations and pointcut parser* while doing its own proxy-based weaving. When people say "Spring AOP", they mean the proxy runtime, not the annotation syntax.

---
### C6.9 The gotchas that will actually bite you [+]

#### ⚠️ 1. Self-invocation — the number one AOP bug

```java
@Service
public class OrderService {

    public void processAll(List<Order> orders) {
        for (Order o : orders) {
            processOne(o);          // ⚠️ @Transactional DOES NOT APPLY
        }
    }

    @Transactional
    public void processOne(Order order) { … }
}
```

**Why:** the caller holds the *proxy*, but once execution is inside the target object, `processOne(o)` is really `this.processOne(o)` — a plain call on the raw object. The proxy is not in that path, so no advice runs. The reference documentation is blunt about it:

> *"any method calls that it may make on itself … are going to be invoked against the `this` reference, and not the proxy. … It means that self invocation is not going to result in the advice associated with a method invocation getting a chance to run."*

```
   caller ──► PROXY ──► target.processAll()
                             │
                             └── this.processOne()   ← never re-enters the proxy
```

**Fixes, in the order Spring recommends them:**

1. **Refactor** so the call crosses a bean boundary (move `processOne` to another bean). *"The best approach … is to refactor your code such that the self invocation does not happen."*
2. **Self-injection** — inject the bean into itself and call through that reference.
   ```java
   @Autowired @Lazy private OrderService self;
   // …
   self.processOne(o);     // goes through the proxy
   ```
3. **`AopContext.currentProxy()`** — requires `exposeProxy = true`. The docs say this is *"highly discouraged."*

#### ⚠️ 2. `private` and `final` cannot be advised

Straight from the docs, for CGLIB proxies:

- *"`final` classes cannot be proxied, because they cannot be extended."*
- *"`final` methods cannot be advised, because they cannot be overridden."*
- *"`private` methods cannot be advised, because they cannot be overridden."*
- package-private methods in a parent class from a different package are *"effectively private"* and also cannot be advised.

So `@Transactional private void save()` compiles, runs, and does nothing transactional. Silently.

#### ⚠️ 3. `@Around` + `CompletableFuture` measures the wrong thing

This one is subtle and extremely common in async services:

```java
@Around("@annotation(Timed)")
public Object time(ProceedingJoinPoint pjp) throws Throwable {
    long t0 = System.currentTimeMillis();
    try {
        return pjp.proceed();
    } finally {
        log.info("took {}ms", System.currentTimeMillis() - t0);   // ⚠️ WRONG for async
    }
}
```

If the target returns `CompletableFuture<T>`, `proceed()` returns **the moment the future is created**, not when it completes. You have measured how long it took to *start* the work — usually under a millisecond — and the log line fires long before the result exists.

**The fix is to attach to the future** ([§J7.5](01-java.md#j75-error-handling-exceptionally-vs-handle-vs-whencomplete)):

```java
@Around("@annotation(Timed)")
public Object time(ProceedingJoinPoint pjp) throws Throwable {
    long t0 = System.currentTimeMillis();
    Object result = pjp.proceed();

    if (result instanceof CompletableFuture<?> future) {
        return future.whenComplete((value, error) ->      // fires on real completion
            log.info("took {}ms, failed={}", System.currentTimeMillis() - t0, error != null));
    }
    log.info("took {}ms", System.currentTimeMillis() - t0);   // synchronous path
    return result;
}
```

📌 This is exactly what production logging aspects do. Note also that an exception from an async method arrives wrapped in `CompletionException` ([§J7.6](01-java.md#j76-the-completionexception-wrapping-gotcha)), so you must unwrap before logging or every error reads `CompletionException`.

#### ⚠️ 4. Advice ordering has two completely different rule sets

> ⚠️ **MYTH: "if you don't set `@Order`, advice order is undefined."**
> Only half true, and the half that is false is the half you will debug at 2 a.m. *Between* aspects, yes. *Within* one aspect, the order is **fully determined by advice type** and `@Order` cannot change it.

**Between aspects** — use `@Order` (or implement `Ordered`) **on the `@Aspect` class**, never on an advice method:

> *"the aspect returning the lower value from `Ordered.getOrder()` (or the annotation value) has the higher precedence."*
> *"The highest precedence advice runs first 'on the way in' … 'On the way out' from a join point, the highest precedence advice runs last."*

- Values need not be consecutive; any `int` works, negatives included (`Ordered.HIGHEST_PRECEDENCE` is `Integer.MIN_VALUE`).
- **Equal values, or no `@Order` at all → the relative order is undefined.**

**Within one aspect** — ⚠️ **`@Order` has no effect**; precedence is fixed **by advice type**:

> *"`@Around`, `@Before`, `@After`, `@AfterReturning`, `@AfterThrowing`"* — highest to lowest. *"Note, however, that an `@After` advice method will effectively be invoked after any `@AfterReturning` or `@AfterThrowing` advice methods in the same aspect, following AspectJ's 'after finally advice' semantics."*

📌 **This is not a theoretical hazard.** A real-world metrics aspect with six `@Around` methods, two of whose pointcuts overlap, ends up advising the same method **twice** under the AspectJ weaver, emitting duplicate metrics.

And for two advices *of the same type* in the same aspect:

> *"the ordering is undefined (since there is no way to retrieve the source code declaration order through reflection for javac-compiled classes). Consider collapsing such advice methods into one advice method per join point in each `@Aspect` class or refactor the pieces of advice into separate `@Aspect` classes."*

**The complete rule, from the Spring reference documentation, in four sentences:**

1. *"The highest precedence advice runs first 'on the way in' … 'On the way out' from a join point, the highest precedence advice runs last."*
2. *"When two pieces of advice defined in different aspects both need to run at the same join point, unless you specify otherwise, the order of execution is undefined."* → control it with `Ordered` or `@Order` **on the aspect class**; *"the aspect returning the lower value … has the higher precedence."*
3. *"Advice methods defined in the same `@Aspect` class that need to run at the same join point are assigned precedence based on their advice type in the following order, from highest to lowest precedence: `@Around`, `@Before`, `@After`, `@AfterReturning`, `@AfterThrowing`."*
4. *"When two pieces of the same type of advice … defined in the same `@Aspect` class both need to run at the same join point, the ordering is undefined."*

⚠️ Note the precise scope of rule 2: the docs say *"in different aspects."* Two aspects carrying the **same** `@Order` value have specified nothing that distinguishes them, so rule 2 still applies — treat equal values as undefined.

#### What the order actually looks like, traced

Two aspects on one method — `@Order(1) SecurityAspect` and `@Order(2) LoggingAspect`, each with `@Around` + `@Before` + `@AfterReturning` + `@After`:

```
  caller
    │
    ├─► SecurityAspect  @Around  (before proceed)        ◄── @Order(1) = higher precedence
    │     ├─► SecurityAspect  @Before
    │     │
    │     ├─► LoggingAspect   @Around  (before proceed)  ◄── @Order(2) = lower precedence
    │     │     ├─► LoggingAspect   @Before
    │     │     │
    │     │     ├─────────►  ★ TARGET METHOD RUNS ★
    │     │     │
    │     │     ├─◄ LoggingAspect   @AfterReturning
    │     │     ├─◄ LoggingAspect   @After              ← "after finally": runs AFTER @AfterReturning
    │     │     └─◄ LoggingAspect   @Around  (after proceed)
    │     │
    │     ├─◄ SecurityAspect  @AfterReturning
    │     ├─◄ SecurityAspect  @After
    │     └─◄ SecurityAspect  @Around  (after proceed)   ← highest precedence runs LAST on the way out
    │
    ▼ result
```

Read the two rules off the picture:
- **Lower `@Order` value = outermost.** It runs first going in and last coming out — like the outer layer of an onion, or the first `Filter` registered in a servlet chain ([§S1.2](05-spring-security.md#s12-the-architecture-the-servlet-filter-chain-q34)).
- **Inside each aspect**, the sequence is `@Around`(pre) → `@Before` → *target* → `@AfterReturning`/`@AfterThrowing` → `@After` → `@Around`(post) — regardless of the order you wrote the methods in the file.

⚠️ **The `@After` position is the counter-intuitive one.** The type-precedence list ranks `@After` *above* `@AfterReturning`, but the docs immediately qualify it: *"an `@After` advice method will effectively be invoked after any `@AfterReturning` or `@AfterThrowing` advice methods in the same aspect, following AspectJ's 'after finally advice' semantics for `@After`."* Think of `@After` as the `finally` block — it is last, because that is what `finally` means.

📌 **The practical consequence.** If you need two things to happen in a guaranteed order, they must be in **two aspects with different `@Order` values**. Two `@Before` methods in the same aspect will run in *some* order, and it may change between builds — reflection does not preserve source order for javac-compiled classes. Spring's own advice: *"Consider collapsing such advice methods into one advice method per join point … or refactor the pieces of advice into separate `@Aspect` classes that you can order at the aspect level."*

💡 **The FastAPI parallel:** stacked decorators in Python have a guaranteed order — bottom-up at decoration time, so the topmost decorator is outermost at call time. Java gives you no such guarantee from source position, which is why `@Order` exists at all. Where Python reads the order off the page, Java makes you declare it.

#### ⚠️ 5. Only Spring-managed beans are advised

`new OrderService()` gets you a bare object with no proxy and no advice. If you need advice on objects you create yourself, that is an AspectJ job (`@Configurable` + load-time weaving).

#### ⚠️ 6. `@Aspect` alone does not register the aspect

`@Aspect` marks the class as an aspect; it does **not** make it a bean. You need `@Component` (or a `@Bean` method) as well:

```java
@Aspect          // ← tells Spring this class contains advice
@Component       // ← tells Spring to instantiate it at all
public class LoggingAspect { }
```

---

### C6.10 The Python/FastAPI translation [+]

Python does natively what Java has to synthesise. A decorator *is* the proxy, written explicitly:

```python
from functools import wraps
import time

def log_execution_time(func):              # ← this is the Aspect
    @wraps(func)                           # ← preserves __name__/__doc__ (Java needs no equivalent)
    def wrapper(*args, **kwargs):          # ← this is the @Around advice
        start = time.time()
        print(f"[before] {func.__name__}")
        try:
            return func(*args, **kwargs)   # ← this is pjp.proceed()
        except Exception as e:
            print(f"[after throwing] {e}")
            raise
        finally:
            print(f"[after finally] {time.time() - start:.3f}s")
    return wrapper

@app.post("/users")
@log_execution_time                        # ← applied ONE function at a time
def create_user(name: str):
    return {"message": f"User {name} created"}
```

| Concept | Java / Spring AOP | Python |
|---|---|---|
| The wrapper | generated proxy class (CGLIB/JDK) | the closure returned by the decorator |
| "run the real thing" | `pjp.proceed()` | `func(*args, **kwargs)` |
| Where it is applied | a **pointcut** — one rule, N methods | **one `@decorator` per function**, written by hand |
| Applied by | the container, at startup | the interpreter, at import time |
| Self-invocation | ⚠️ **broken** | ✅ works — the name is rebound, so all callers see the wrapper |
| Metadata preservation | automatic | you must remember `@functools.wraps` |

📌 **The one real difference to internalise.** Python rebinds the *name*, so every call to `create_user` — including from inside the same module — hits the wrapper. Java swaps the *injected reference*, so calls that never go through that reference (i.e. `this.foo()`) bypass everything. That single distinction is why [§C6.9](#c69-the-gotchas-that-will-actually-bite-you-)'s self-invocation bug exists in Java and has no Python equivalent.

📌 **The other real difference: reach.** In Python you decorate functions one at a time. In Java one pointcut can advise every method in a package. FastAPI's closest equivalent to a pointcut is **middleware** (`@app.middleware("http")`) or a router-level `dependencies=[Depends(...)]` — but those, like Spring's `HandlerInterceptor`, only see HTTP requests.

**Are interceptors AOP?** Conceptually yes — same wrap-and-delegate shape. But they are restricted:

| | Servlet `Filter` | Spring `HandlerInterceptor` | gRPC `ServerInterceptor` | Spring AOP |
|---|---|---|---|---|
| Sees | every HTTP request | requests reaching a handler | every RPC | **any method on any bean** |
| Knows the target method | ❌ | ✅ (`HandlerMethod`) | ✅ (method descriptor) | ✅ (`JoinPoint`) |
| Works on service/repo layers | ❌ | ❌ | ❌ | ✅ |

**Are all Spring annotations AOP?** No, and the distinction is useful:

| Purpose | Annotations | AOP? |
|---|---|---|
| Registration / DI | `@Component` `@Service` `@Repository` `@Autowired` `@Bean` `@Configuration` | ❌ |
| Routing / binding | `@GetMapping` `@RequestParam` `@RequestBody` | ❌ (handler mapping) |
| Mapping metadata | `@Entity` `@Column` `@OneToMany` | ❌ ([§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-)) |
| **Behaviour around a call** | **`@Transactional` `@Cacheable` `@Async` `@Retryable` `@PreAuthorize` `@Validated` `@Timed`** | **✅** |

Rule of thumb: **if the annotation changes what happens when the method is called, it is AOP.**

---

### C6.11 The dependency, and why it works without `@EnableAspectJAutoProxy` [+]

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-aspectj</artifactId>   <!-- Boot 4.0+ -->
</dependency>
```

⚠️ **In Spring Boot 3.x and earlier this artifact is `spring-boot-starter-aop`.** It was renamed in 4.0 — *"To clarify the scope of `spring-boot-starter-aop`, it has been renamed to `spring-boot-starter-aspectj`."* No Java code changes are required. See [§R2.6](00-start-here.md#r26-the-boot-3--boot-4-migration-checklist-).

#### The real `AopAutoConfiguration`

This is the actual structure in Spring Boot's source, not a paraphrase:

```java
@AutoConfiguration
@ConditionalOnBooleanProperty(name = "spring.aop.auto", matchIfMissing = true)
public class AopAutoConfiguration {

    @Configuration(proxyBeanMethods = false)
    @ConditionalOnClass(Advice.class)                        // org.aspectj.weaver.Advice
    static class AspectJAutoProxyingConfiguration {

        @Configuration(proxyBeanMethods = false)
        @EnableAspectJAutoProxy(proxyTargetClass = false)
        @ConditionalOnBooleanProperty(name = "spring.aop.proxy-target-class", havingValue = false)
        static class JdkDynamicAutoProxyConfiguration { }

        @Configuration(proxyBeanMethods = false)
        @EnableAspectJAutoProxy(proxyTargetClass = true)
        @ConditionalOnBooleanProperty(name = "spring.aop.proxy-target-class", matchIfMissing = true)
        static class CglibAutoProxyConfiguration { }
    }

    @Configuration(proxyBeanMethods = false)
    @ConditionalOnMissingClass("org.aspectj.weaver.Advice")   // ← AspectJ NOT on the classpath
    @ConditionalOnBooleanProperty(name = "spring.aop.proxy-target-class", matchIfMissing = true)
    static class ClassProxyingConfiguration {
        @Bean static BeanFactoryPostProcessor forceAutoProxyCreatorToUseClassProxying() { … }
    }
}
```

Read it as three decisions — this is [§C1](#c1-the-spring-boot-mental-model-and-auto-configuration-q47-)'s machinery doing exactly what it always does:

1. **`spring.aop.auto`** — on unless you set it to `false` (`matchIfMissing = true`).
2. **Is `org.aspectj.weaver.Advice` on the classpath?** If yes, `@EnableAspectJAutoProxy` is applied *for you* — that is why you never write it. If no, `ClassProxyingConfiguration` still forces class-based proxies, so **`@Transactional`, `@Async` and `@Cacheable` keep working without the AspectJ starter.**
3. **`spring.aop.proxy-target-class`** — defaults to `true` (CGLIB).

📌 **Point 2 is exactly why the Boot 4 migration guide adds "Please review if you actually need it before using the replacement."** If you only use Spring's built-in behavioural annotations, you need no AspectJ dependency at all. You need it only to write your own `@Aspect` classes.

#### Why `proxyTargetClass = true` is the default

| | `false` — JDK dynamic proxy | `true` — CGLIB (Boot default) |
|---|---|---|
| Requires an interface | ✅ yes | ❌ no |
| Proxy is | a new class implementing the interfaces | a **subclass** of your class |
| Injecting by concrete type | ❌ fails — the proxy is not a `MyServiceImpl` | ✅ works |

Boot defaults to CGLIB so AOP works on plain classes with no interface — which is how most services are written today. Without it, adding `@Transactional` to an interface-less class would break startup with a confusing bean-type mismatch.

📌 **New in Spring Framework 7:** *"forcing a specific proxy type for individual beans is possible through the `@Proxyable` annotation on a given `@Bean` method or `@Component` class, with `@Proxyable(INTERFACES)` or `@Proxyable(TARGET_CLASS)` overriding any globally configured default."*

---

### C6.12 Checklist [+]

**Do**
- Put `@Aspect` **and** `@Component` on aspect classes.
- Anchor every pointcut to your own package.
- Name and reuse pointcuts with `@Pointcut`.
- Use `Object` as the `@Around` return type.
- Bind arguments in the pointcut (`args(...)`, `@annotation(...)`) instead of casting `getArgs()`.
- Put `@Order` on the aspect **class**.
- Prefer a custom marker annotation over a broad wildcard — it is explicit at the call site.

**Don't**
- Rely on advice firing for a call from inside the same object ([§C6.9](#c69-the-gotchas-that-will-actually-bite-you-)).
- Annotate `private` or `final` methods and expect advice.
- Forget `@Retention(RUNTIME)` on a custom annotation.
- Use `@Order` to sequence advice *within* one aspect.
- Time a `CompletableFuture`-returning method with a naive `@Around`.
- Hide business logic in an aspect — cross-cutting *infrastructure* only. If a reader cannot understand what a method does without knowing your aspects exist, you have gone too far.

**The five-line summary**

1. Spring AOP = **runtime proxies** around **Spring beans**, **method executions only**.
2. Pointcut selects where; advice says what and when; the aspect bundles them.
3. `@Around` + `proceed()` gives total control; everything else observes.
4. The proxy is what gets injected — which is why `this.method()` bypasses it.
5. Need fields, constructors, `private` methods, or self-invocation? That is AspectJ, not Spring AOP.

---


## C7. Spring application events

> **Your question:** *"What is Spring events?"*

**Spring application events are an in-process publish/subscribe mechanism built into the `ApplicationContext`.** One bean announces "something happened"; any number of other beans react — and the publisher doesn't know who they are. It is the **Observer pattern**, provided by the container ([§C2.4](#c24-the-container-q13) — event publishing is one of the features `ApplicationContext` adds over `BeanFactory`).

### C7.1 The three pieces, and your order example

> **Your example:** *"The order service creates an order, but for that order we also need to (a) log the details, (b) send an email, (c) do auditing. These aren't the order service's responsibility, so it publishes an 'order created' event and the respective parts do their work independently — pub-sub / observer pattern. In Spring the producer is ApplicationEventPublisher, any method can be a consumer with @EventListener, and the listener receives the event as a parameter."*

```java
// 1. THE EVENT — any object (since Spring 4.2). A record is ideal: immutable data.
public record OrderCreatedEvent(Long orderId, String customerEmail, BigDecimal amount) {}

// 2. THE PUBLISHER
@Service
public class OrderService {
    private final OrderRepository repo;
    private final ApplicationEventPublisher publisher;     // injected like any bean

    public OrderService(OrderRepository repo, ApplicationEventPublisher publisher) {
        this.repo = repo; this.publisher = publisher;
    }

    public Order placeOrder(Order order) {
        Order saved = repo.save(order);
        publisher.publishEvent(new OrderCreatedEvent(saved.getId(), saved.getEmail(), saved.getAmount()));
        return saved;                                       // no idea who listens
    }
}

// 3. THE LISTENERS — any method on any bean
@Component
class OrderSideEffects {
    @EventListener void log(OrderCreatedEvent e)   { log.info("order {} created", e.orderId()); }
    @EventListener void email(OrderCreatedEvent e) { mailer.sendConfirmation(e.customerEmail()); }
    @EventListener void audit(OrderCreatedEvent e) { auditRepo.record(e); }
}
```

Adding a fourth reaction (analytics) means adding a fourth method — `OrderService` never changes. That's the benefit: **loose coupling and extensibility**.

📌 **Correction on scope:** this decouples **modules inside one application (one JVM)**. If logging, email and audit are **separate microservices**, Spring events cannot reach them — you need a broker (§C7.4). Your own conclusion later in your notes is exactly right.

You can also extend `ApplicationEvent` (the pre-4.2 style) — Spring wraps a plain object in a `PayloadApplicationEvent` internally, so both work the same.

### C7.2 How routing works: the multicaster and the listener parameter

> **Your questions:** *"Does routing happen using the event parameter of the listener? Does the listener receive only a single parameter?"*

**Yes, routing is by the parameter's type.** The listener above receives every published object that is an instance of `OrderCreatedEvent` — including subclasses (a listener for a parent type, or `Object`, receives the children too). Generic types are honoured where they can be resolved.

**Parameters:** **zero or one.**
- One parameter: the event type.
- Zero parameters: allowed if you name the type(s) on the annotation — `@EventListener(OrderCreatedEvent.class) void onAny()` — for "I only care that it happened". The annotation can list several types.
- Two or more: Spring fails with `IllegalStateException: Maximum one parameter is allowed for event listener method` (verified in `ApplicationListenerMethodAdapter`). It's thrown when the listener is registered, i.e. during startup.

**Internals** — what happens between `publishEvent` and your method:

```
publisher.publishEvent(evt)
      │   (the ApplicationContext IS the ApplicationEventPublisher)
      ▼
ApplicationEventMulticaster   (default: SimpleApplicationEventMulticaster)
      │  1. which listeners support this event type?
      │     → answer cached per (event type, source type) after the first lookup
      │  2. sort them by @Order
      │  3. invoke each one — on the CALLER'S thread by default
      ▼
listener methods (wrapped as ApplicationListenerMethodAdapter objects)
```

> **Your description of the startup scan** (*"at startup it looks at all beans for @EventListener methods and stores them in an internal listener cache, key = event type, value = listeners"*) — 📌 nearly right, with one refinement: at startup `EventListenerMethodProcessor` scans every bean and registers **one listener object per `@EventListener` method** with the multicaster. The **type → listeners cache is filled lazily**, the first time each event type is published, and reused afterwards. Same idea, built on demand rather than up front.

⚠️ Don't make listener beans `@Lazy` — the docs warn the context then won't register the method at all.

> **Your remark:** *"It's easy in Spring; in FastAPI we'd write the publisher and subscriber classes ourselves and handle finding the consumer on publish."* — Correct. 🐍 Python's nearest ready-made equivalents are libraries like `blinker` (Flask's signals) or `pyee`; 🟨 Node has `EventEmitter` built in (`emitter.on('orderCreated', fn)` / `emitter.emit(...)`), which is the closest analogue — also synchronous by default, also in-process.

### C7.3 Synchronous by default — what that implies

> **Your questions:** *"Do Spring events follow a fire-and-forget model, unlike Kafka/RabbitMQ where we configure acks? Are they synchronous, or can we use them async?"*

**Synchronous by default.** The docs: *"`publishEvent()` blocks until all listeners have finished processing the event."* Consequences:

| Consequence | Detail |
|---|---|
| Same thread | listeners run on the publisher's thread, one after another, in `@Order` order |
| Same transaction | the docs: a listener *"operates inside the transaction context of the publisher if a transaction context is available"* |
| Exceptions propagate | a listener exception stops the remaining listeners and is thrown out of `publishEvent()` into the publisher — and, if the publisher is `@Transactional` and doesn't catch it, **rolls the transaction back** |
| Latency adds up | the publisher's response waits for the email to send |

**Async is opt-in** with `@Async` (needs `@EnableAsync` — §C7.6).

**"Fire-and-forget"**: they are **in-memory with no delivery guarantees** — nothing is persisted, there are no acks, no retries, no replay. For synchronous listeners you *do* know they ran (the call returned); for async ones you don't. If the JVM dies while an async listener is running, or before an `AFTER_COMMIT` listener runs, that event is gone.

### C7.4 Spring events vs Kafka / RabbitMQ

> **Your questions:** *"Why and when should we use Spring events if we have Kafka and RabbitMQ? We use Spring events if all consumers and producers are in the same JVM, otherwise a distributed event system like Kafka, RabbitMQ or SQS?"*

Yes — that's the dividing line.

| | Spring events | Kafka / RabbitMQ / SQS |
|---|---|---|
| Boundary | **one JVM** | across services and machines |
| Durability | ❌ RAM only | ✅ persisted |
| Delivery guarantees | none (sync: you know it ran; async: best effort) | configurable — at-least-once, acks, DLQs, replay (Kafka) |
| Consumer down? | n/a — same process | messages wait for it |
| Infrastructure | none | a cluster to run and monitor |
| Latency | a method call | network + serialization |

**Use Spring events for:** decoupling modules inside a monolith / modular monolith; side effects that must follow a DB commit (`@TransactionalEventListener`, §C7.5); local cache invalidation, metrics, internal notifications where loss on crash is acceptable.

**Use a broker for:** anything crossing a service boundary; anything that must not be lost; buffering spikes; multiple independent consumer groups.

📌 **Correction to the "Outbox pattern" tip in your chat:** an `AFTER_COMMIT` listener that sends to Kafka is useful, but it is **not** the transactional outbox — if the process crashes between the commit and the send, the message is lost. The **outbox** pattern writes the event as a **row in the same DB transaction** as the business data, and a separate relay (poller or CDC such as Debezium) publishes it afterwards — that's what makes it reliable. (Spring Modulith's event publication registry implements this for Spring events.)

### C7.5 `@TransactionalEventListener` — react only after the commit

Problem: a plain `@EventListener` runs **at `publishEvent()` time** — inside the transaction. If the transaction then rolls back, the confirmation email has already gone out for an order that doesn't exist.

```java
@Service
public class OrderService {
    @Transactional
    public void placeOrder(Order order) {
        orderRepository.save(order);
        publisher.publishEvent(new OrderCreatedEvent(order.getId(), order.getEmail(), order.getAmount()));
        if (order.getAmount().signum() <= 0) {
            throw new IllegalArgumentException("Invalid amount");  // → rollback; AFTER_COMMIT listener never runs
        }
    }   // ← commit happens here; THEN AFTER_COMMIT listeners run
}

@Component
public class NotificationListener {
    @TransactionalEventListener                         // phase = AFTER_COMMIT is the default
    public void sendConfirmation(OrderCreatedEvent e) { mailer.send(e.customerEmail()); }

    @TransactionalEventListener(phase = TransactionPhase.AFTER_ROLLBACK)
    public void logFailed(OrderCreatedEvent e) { log.warn("order {} rolled back", e.orderId()); }
}
```

| Phase | Runs |
|---|---|
| `BEFORE_COMMIT` | just before commit, still inside the transaction (can still cause a rollback) |
| `AFTER_COMMIT` *(default)* | after a successful commit |
| `AFTER_ROLLBACK` | after a rollback |
| `AFTER_COMPLETION` | after either |

Rules that bite (Spring Framework reference + source):
- ⚠️ **No transaction active → the listener is not invoked at all.** Set `fallbackExecution = true` if it should run anyway.
- ⚠️ **Writing to the DB in an `AFTER_COMMIT` listener:** the original transaction is committed but its resources are still bound to the thread, so plain repository calls would "join" it and never commit. Annotate the listener `@Transactional(propagation = Propagation.REQUIRES_NEW)`. **Since Spring 6.1** this is enforced: a `@TransactionalEventListener` (other than `BEFORE_COMMIT`) annotated `@Transactional` with any propagation other than `REQUIRES_NEW` or `NOT_SUPPORTED` fails at startup (`RestrictedTransactionalEventListenerFactory`).
- Combine with `@Async` to send the email off the request thread after commit.

🔗 Transactions themselves: [§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production).

### C7.6 Ordering, async listeners, and `@EnableAsync`

> **Your notes:** *"Control order with @Order on the method of the component class rather than on the class. To enable async listeners add @EnableAsync on the main class and @Async on the listener method — [is @EnableAsync only for event listeners, or for any function?]. With @EnableAsync and @Async all listeners run in parallel. What happens with @Order and @Async together? Spring honours both: it submits the listeners to the executor in order, but since execution times differ the output may not be in that order."*

All correct:

- **`@Order` on the listener method** (lower value = earlier). The docs show it on the method.
- **`@EnableAsync` is application-wide**, not specific to events: it enables the `@Async` proxy for **any** method on **any** bean. Each `@Async` call is handed to a `TaskExecutor` and returns immediately (`void`, or a `CompletableFuture`). General coverage: [§P3](06-spring-production.md#p3-background-work-scheduled-and-async).
- **`@Order` + `@Async`:** the multicaster still iterates in order, so tasks are **submitted** in order — but they run concurrently, so **completion** order is not guaranteed. If B must run after A, don't make them both async — chain them (§C7.7).

Async listener caveats (from the reference docs):
- an exception is **not propagated** to the publisher — it goes to the `AsyncUncaughtExceptionHandler` (logged by default);
- an async listener **cannot publish a follow-up event by returning a value** — inject `ApplicationEventPublisher` instead;
- **ThreadLocals aren't propagated** — no `SecurityContext`, MDC/trace ids, or transaction on the listener thread unless you add a `TaskDecorator` ([§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder)).
- `@Async` is a proxy, so the self-invocation rule applies ([§C5.3](#c53-cglib-what-it-is-and-how-it-works)).

### C7.7 Returning events: chaining

> **Your question:** *"You can also return a new event or a collection of events from the listener and Spring will publish them next — is this used for chains of events?"*

Yes. A non-null return value (or each element of a returned `Collection`/array) is published as a new event:

```java
@EventListener
public PaymentRequestedEvent onOrderCreated(OrderCreatedEvent e) {      // returns the next event
    return new PaymentRequestedEvent(e.orderId(), e.amount());
}
@EventListener
public void onPaymentRequested(PaymentRequestedEvent e) { … }            // runs next, same thread
```

It keeps each listener single-purpose without injecting a publisher. Two limits: **not supported for async listeners** (above), and ⚠️ avoid cycles (A returns B, B returns A) — synchronously that recurses until `StackOverflowError`.

### C7.8 Conditional listeners (SpEL)

> **Your scenario and questions:** *"We have 3 listeners for OrderCreatedEvent, but want one more to run only if the price is > 1000: `@EventListener(condition = "#event.amount > 1000")`. What is the syntax? Can we use a static constant? Can we combine conditions with and/or?"*

`condition` is a **SpEL** expression evaluated per event; the listener runs only when it's `true`.

| You can reference | Syntax |
|---|---|
| the parameter by name | `#event` (needs `-parameters`, which Boot's build plugins set) |
| the parameter by index | `#a0` or `#p0` |
| the event / args root | `#root.event`, `#root.args[0]` |
| a static constant | `T(com.acme.OrderConstants).VIP_THRESHOLD` |
| a bean | `@pricingRules.isVip(#event)` |
| logic | `and`, `or`, `not` (or `&&`, `\|\|`, `!`), `==`, `>`, `matches` |

```java
public final class OrderConstants { public static final BigDecimal VIP_THRESHOLD = new BigDecimal("1000"); }

@EventListener(condition =
    "#event.amount > T(com.acme.OrderConstants).VIP_THRESHOLD and #event.status == 'CONFIRMED'")
public void onVipOrder(OrderCreatedEvent event) { … }
```
- Accessing `#event.amount` on a record calls the accessor `amount()`; on a class, `getAmount()`.
- ⚠️ `BigDecimal > BigDecimal` works in SpEL (it compares `Comparable`s); comparing a `BigDecimal` with an `int` literal also works because SpEL converts numbers, but a constant of the same type is clearer.
- The constant needs the **fully-qualified** class name inside `T(...)` — like pointcuts, SpEL strings can't see your imports ([§C6.6](#c66-pointcut-expressions-in-full-)).

### C7.9 Handling listener exceptions globally

> **Your notes:** *"Instead of try/catch in every listener, override the ApplicationEventMulticaster with a custom error handler:"* (your snippet, corrected below). *"Why do we need to override the multicaster, and why isn't it handled by @ControllerAdvice, which handles all exceptions globally?"*

```java
@Configuration
public class EventConfig {
    @Bean(name = "applicationEventMulticaster")      // ⚠️ this exact bean name replaces the default
    public ApplicationEventMulticaster applicationEventMulticaster() {
        SimpleApplicationEventMulticaster multicaster = new SimpleApplicationEventMulticaster();
        multicaster.setErrorHandler(t -> log.error("Event listener failed", t));   // ErrorHandler.handleError(Throwable)
        return multicaster;
    }
}
```
(Fixes to your snippet: the class is `ApplicationEventMulticaster` / `SimpleApplicationEventMulticaster` — lower-case "c"; `ErrorHandler` receives a `Throwable` (`t.getMessage()`), and Java's call is `System.out.println`. The method name `applicationEventMulticaster` already makes it the bean name; the explicit `name` just documents it.)

What it does (verified in `SimpleApplicationEventMulticaster.invokeListener`): each listener invocation is wrapped in `try { … } catch (Throwable t) { errorHandler.handleError(t); }`. So one failing listener **no longer stops the others** — and, ⚠️ equally, **the publisher never sees the exception**: a `@Transactional` publisher will commit even though a listener failed. Decide which behaviour you want.

⚠️ Don't also call `setTaskExecutor(...)` casually: that makes **every** listener in the application async — including Spring's own context lifecycle listeners. Prefer `@Async` per listener.

**Why `@ControllerAdvice` doesn't (always) catch these** — 📌 **correction to the Gemini answer**, which said it never does:

| Listener type | Where does its exception go? | `@ControllerAdvice` sees it? |
|---|---|---|
| **Synchronous**, event published during an HTTP request, **no** custom `ErrorHandler` | thrown out of `publishEvent()` → out of your service → out of the controller | ✅ **yes** — it's an ordinary exception in the request thread |
| Synchronous, with the custom `ErrorHandler` above | swallowed by the handler | ❌ |
| `@Async` | thrown on an executor thread → `AsyncUncaughtExceptionHandler` | ❌ (the HTTP response may already be sent) |
| Published from `@Scheduled`, a Kafka consumer, a `CommandLineRunner` | no HTTP request exists | ❌ |

`@ControllerAdvice` is **not** global exception handling for the whole app: it's used by Spring MVC's `ExceptionHandlerExceptionResolver` for exceptions that escape a **controller call** ([§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling)). For async listeners, register a handler by implementing `AsyncConfigurer.getAsyncUncaughtExceptionHandler()` ([§P3](06-spring-production.md#p3-background-work-scheduled-and-async)).

### C7.10 Summary

```
publishEvent(e) ─► ApplicationEventMulticaster ─► listeners matching e's TYPE, in @Order
                      │ default: same thread, same transaction, exceptions propagate
                      ├─ @Async listener          → executor thread, exceptions → AsyncUncaughtExceptionHandler
                      ├─ @TransactionalEventListener → deferred to AFTER_COMMIT (default); skipped if no tx
                      ├─ condition = "SpEL"       → filter per event
                      └─ return value             → published as the next event (sync only)
```

🔗 Connected topics: proxies behind `@Async` ([§C5](#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)); transactions ([§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production)); `@EnableAsync` and executors ([§P3](06-spring-production.md#p3-background-work-scheduled-and-async)); context propagation to other threads ([§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder)).



---

[⬅ 01-java.md](01-java.md) · [🏠 Start here](00-start-here.md) · [03-spring-web.md ➡](03-spring-web.md)
