# Java and Spring Boot — Start Here

> **Audience:** a backend engineer fluent in **Python/FastAPI** and **Node/Express**, learning Java → Spring → Spring Boot.
> **Purpose:** a set of revision documents, split by topic so you can open just the one you need. **Every question you asked is preserved**, reordered into a learning sequence, with duplicates merged and errors corrected.
> **Baseline:** Java 17/21 and **Spring Boot 3.x/4.x** (Spring Framework 6/7, `jakarta.*`). Boot 2.7 (`javax.*`, still common in older services) differences are called out where they bite. The version picture is in [§R2](#r2-version-landscape--november-2026).
> **Last updated:** 15 November 2026. This set replaces the single file `java-spring-boot-learning-notes.md`, which was deleted on 16 November 2026 (a backup is kept outside the repo).

---

## The document set

| # | Document | What it covers | Read it when |
|---|---|---|---|
| 00 | **This file** | Twenty traps, version landscape, quick revision sheet, glossary | First, then as a reference |
| 01 | [Java](01-java.md) | JVM orientation, language essentials (`Optional`, generics, lambdas, streams), strings, exceptions, records vs Lombok, concurrency (threads, `ThreadLocal`, virtual threads), `CompletableFuture` | Before any Spring doc |
| 02 | [Spring core](02-spring-core.md) | Boot's mental model, IoC/DI, bean scopes, `ObjectProvider`/`@Lookup`, configuration and `@ConfigurationProperties`, conditional beans, proxies (CGLIB), AOP, application events | Before the web doc: everything else is built on this |
| 03 | [Spring web (MVC)](03-spring-web.md) | Servlets, `DispatcherServlet`, `HandlerMapping`/`HandlerAdapter`, the request lifecycle, filters vs interceptors, binding, validation, responses and error handling, CORS, request-scoped context, Thymeleaf, OpenAPI | When building REST endpoints |
| 04 | [Spring data](04-spring-data.md) | Normalization, JDBC drivers and pools, JPA/Hibernate relationships, transactions, Spring Data REST, HATEOAS | When touching a database |
| 05 | [Spring Security](05-spring-security.md) | Filter-chain architecture, authentication flow, passwords, JWT and refresh tokens, authorization and method security, OAuth2, CSRF/CORS | When securing an API |
| 06 | [Production and microservices](06-spring-production.md) | Downstream calls and gRPC, retries and circuit breakers, `@Scheduled`/`@Async`, Spring Cloud Config, production concerns | When the service talks to other services and runs in prod |

### Suggested learning path

```text
 01 Java ──► 02 Spring core ──► 03 Web ──► 04 Data ──► 05 Security ──► 06 Production
  essentials   IoC/DI, config     request    JPA, tx     filters again,    resilience,
  concurrency  proxies, AOP       lifecycle              auth, authz       scheduling, config
```

### How the topics connect (the threads that run through every doc)

| Idea | Where it appears |
|---|---|
| **Everything is a bean, wired by the container** | [§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13) → controllers ([§W4](03-spring-web.md#w4-rest-controller--the-complete-unabstracted-request-lifecycle-q)), repositories ([§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-)), the security chain ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)) |
| **Proxies make annotations work** | [§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode) → `@Transactional` ([§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production)), AOP ([§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-)), `@PreAuthorize` ([§S4](05-spring-security.md#s4-authorization-what-are-you-allowed-to-do)), `@Retryable` ([§P2](06-spring-production.md#p2-resilience-retries-recovery-and-circuit-breakers)), `@Async` ([§P3](06-spring-production.md#p3-background-work-scheduled-and-async)). Same rule everywhere: self-invocation skips the proxy |
| **Two pipelines around a request** | Servlet filters ([§W5](03-spring-web.md#w5-filters-vs-handlerinterceptors)) → Spring Security is one filter ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)) → `DispatcherServlet` → interceptors → controller. CORS can live in either ([§W9](03-spring-web.md#w9-cors-crossorigin-corsfilter-and-spring-security)) |
| **Thread-bound state** | `ThreadLocal` ([§J6](01-java.md#j6-concurrency-and-multithreading-q2q9)) → `RequestContextHolder` ([§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder)) → `SecurityContextHolder` ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)) → transactions ([§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production)). All of it is lost when you hop to another thread |
| **Configuration drives behaviour** | properties and profiles ([§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12)) → conditional beans and auto-configuration ([§C4](02-spring-core.md#c4-conditional-beans-and-auto-configuration-ordering)) → runtime refresh ([§P4](06-spring-production.md#p4-externalized-configuration-at-scale-spring-cloud-config-and-runtime-refresh)) |

## Contents of this file

- [R1. Twenty facts that catch people out — read this first](#r1-twenty-facts-that-catch-people-out--read-this-first)
- [R2. Version landscape — November 2026](#r2-version-landscape--november-2026)
  - [R2.1 Java](#r21-java)
  - [R2.2 Spring](#r22-spring)
  - [R2.3 How we got here: the evolution story [+]](#r23-how-we-got-here-the-evolution-story-)
  - [R2.4 Spring Boot 4 / Framework 7 in depth [+]](#r24-spring-boot-4--framework-7-in-depth-)
  - [R2.5 What did *not* change [+]](#r25-what-did-not-change-)
  - [R2.6 The Boot 3 → Boot 4 migration checklist [+]](#r26-the-boot-3--boot-4-migration-checklist-)
  - [R2.7 Myths, and what is actually true [+]](#r27-myths-and-what-is-actually-true-)
- [R3. Quick revision sheet](#r3-quick-revision-sheet)
  - [R3.1 The thirteen mental models that carry everything else](#r31-the-thirteen-mental-models-that-carry-everything-else)
  - [R3.2 Python / JavaScript to Java translation](#r32-python--javascript-to-java-translation)
  - [R3.3 The annotations, by job](#r33-the-annotations-by-job)
  - [R3.4 The request lifecycle in one block](#r34-the-request-lifecycle-in-one-block)
  - [R3.5 The traps that will actually bite you](#r35-the-traps-that-will-actually-bite-you)
  - [R3.6 The commands](#r36-the-commands)
  - [R3.7 The traps from your November 2026 notes](#r37-the-traps-from-your-november-2026-notes)
- [R4. Glossary](#r4-glossary)

## How to use these documents

1. **Read [§R1](#r1-twenty-facts-that-catch-people-out--read-this-first) first.** Twenty facts that are easy to get wrong; two of them would cost you real time in production.
2. **Do 01 Java before the Spring docs.** Spring is *just a library*; if the Java underneath is fuzzy, Spring looks like magic.
3. **The Spring docs are ordered bottom-up**: container → web → data → security → production. Each assumes the ones before it.
4. **[§W4](03-spring-web.md#w4-rest-controller--the-complete-unabstracted-request-lifecycle-q)** is the centrepiece: the full journey of an HTTP request with every abstraction removed.
5. **[§R3](#r3-quick-revision-sheet)** is a one-page-per-topic recall sheet. Use it to revise; use the body docs when you need the *why*.
6. Section labels carry their document's letter (**J**ava, **C**ore, **W**eb, **D**ata, **S**ecurity, **P**roduction, **R**eference), so `§S3.2` always means the security doc.


### Legend

| Marker | Meaning |
|---|---|
| **[Q*n*]** | From your chat #*n*. All original content preserved, reorganised. |
| **[Q★]** | You asked this (via a Google AI Mode link) but no answer text was recoverable — I wrote it from scratch. |
| **[+]** | Added by me — adjacent material a backend engineer is expected to know. |
| ⚠️ | Real-world gotcha that bites people in production. |
| 📌 | A fact that is commonly misremembered — pin this one. All twenty are collected in [§R1](#r1-twenty-facts-that-catch-people-out--read-this-first). |
| ❌ / ✅ | In tables: not supported / supported. In code: the wrong way / the right way. |
| 🐍 / 🟨 / 🐹 | Python / JavaScript / Go comparison. |

---

## R1. Twenty facts that catch people out — read this first

Twenty things that are easy to get wrong, and expensive to get wrong. Each one is verified against a primary source and links to its full treatment later in the document. Skim it now; come back when something behaves unexpectedly.

---

### 1 — Thread priorities do essentially nothing on Linux [Q5, Q6]

`Thread.setPriority()` is effectively a **no-op** on a default JVM on Linux. Three reasons stack up:

- HotSpot's default is `-XX:ThreadPriorityPolicy=0`. In that mode, on Linux, **the JVM does not call `setpriority()` at all** for ordinary priority changes.
- Linux's `SCHED_OTHER` — the only scheduling class available to a non-root, non-realtime process — has **no static priority**. The only lever is the nice value.
- Raising a thread's priority means **lowering its nice value, which requires root** (`CAP_SYS_NICE`). `-XX:ThreadPriorityPolicy=1` ("aggressive") maps Java's 1–10 onto the full native range, but on Linux it too requires root, and Oracle's own docs warn it can degrade whole-system performance.

The textbook scheduler mechanics — preemption, longer quanta, an 80–90 % CPU split between a `MAX_PRIORITY` and a `MIN_PRIORITY` thread — describe how OS schedulers work in general, and are broadly accurate on **Windows**. They are not what your Java code gets on Linux.

**What this means for you:** in a container on Linux — i.e. essentially every backend service you will ever deploy — `t.setPriority(Thread.MAX_PRIORITY)` is a comment, not an instruction.

**What to do instead:** the `PriorityBlockingQueue` + `ThreadPoolExecutor` pattern, or separate executor pools for interactive vs. background work. Treat that as *the* answer, not the fallback. Full detail in [§J6.5](01-java.md#j65-thread-priorities-q5-q6--and-what-they-actually-do-on-linux).

*Sources: [Oracle Thread Priority docs](https://docs.oracle.com/javase/8/docs/technotes/guides/vm/thread-priorities.html), [JDK-5096173](https://bugs.java.com/bugdatabase/view_bug.do?bug_id=5096173), [javamex](https://www.javamex.com/tutorials/threads/priority_what.shtml)*

---

### 2 — gRPC interceptor lists are applied in reverse [Q19]

With `ClientInterceptors.intercept(channel, a, b)`, **the LAST interceptor listed is called FIRST** — `b` is application-near, `a` is network-near. The Javadoc is explicit: *"The last interceptor will have its `ClientInterceptor.interceptCall` called first."*

So to get caching application-near and logging network-near with `intercept(...)`, you write the list **backwards**:

```java
Channel ch = ClientInterceptors.intercept(base, loggingInterceptor, cachingInterceptor);
//                                              ^network-near      ^application-near (called FIRST)
```

There is a sibling method with the intuitive order: **`ClientInterceptors.interceptForward(channel, a, b)`** — *"The first interceptor will have its `interceptCall` called first."* Prefer that one, so the list reads application-near → network-near.

**The same reversal applies to `ServerInterceptors.intercept(...)`** (last added = called first), with `ServerInterceptors.interceptForward(...)` as the intuitive-order variant. And `ServerBuilder.intercept(...)` called repeatedly also runs in reverse order of addition.

Keep the *design intent* separate from the *API mechanics*: caching should short-circuit before logging, so logs only show real network traffic. That part is architecture. Only the argument order is counter-intuitive. Full detail in [§P1.6](06-spring-production.md#p16-interceptor-ordering--and-the-reversal-trap).

*Sources: [ClientInterceptors Javadoc](https://grpc.github.io/grpc-java/javadoc/io/grpc/ClientInterceptors.html), [ServerInterceptors Javadoc](https://grpc.github.io/grpc-java/javadoc/io/grpc/ServerInterceptors.html), [grpc-java#570](https://github.com/grpc/grpc-java/issues/570)*

---

### 3 — Spring Data REST projections do **not** optimise the SQL [Q30]

Two different mechanisms share the word "projection":

| Mechanism | How it's triggered | Does it reduce the SQL? |
|---|---|---|
| **Spring Data JPA interface projection** — `List<UserSummary> findByStatus(String s)` declared as a **repository query return type** | the return type of a repository method | ✅ **Yes** — closed projections let Spring Data JPA generate `SELECT u.email FROM User u …` |
| **Spring Data REST `@Projection`** — `GET /members?projection=userSummary` | a **query parameter at serialization time** | ❌ **No** — the repository runs plain `findAll(pageable)` and loads **full entities**; the projection proxy is applied afterwards, during JSON serialization |

A Spring Data REST `@Projection` (including `excerptProjection`) **hides fields from the client but does not save a single database column read**. It is a *payload-shaping* tool, not a *query-optimisation* tool — and because the hidden field is still loaded into memory, it is a **presentation** control, never a **security** control.

Two further caveats, both from the Spring docs:
- Projections only limit **top-level** properties. *"Any nested properties resolving to joins select the entire nested property causing the full join to materialize."*
- Interface-based DTO projections perform worse than **class-based (constructor) projections**, which *can* have their column list derived from the constructor parameter names.

**Practical upshot:** if you are choosing projections *for performance*, choose something else — DTOs, or class-based projections as repository return types. Choose `?projection=` for boilerplate reduction in a Spring Data REST app. This is also what makes the DTO-vs-Projection conclusion in Q31 the right one. Full detail in [§D5.7](04-spring-data.md#d57-projections-q30--and-what-they-actually-optimise).

*Sources: [Spring Data JPA Projections](https://docs.spring.io/spring-data/jpa/reference/repositories/projections.html), [Spring Data REST Projections](https://docs.spring.io/spring-data/rest/reference/projections-excerpts.html), [Thorben Janssen](https://thorben-janssen.com/spring-data-jpa-query-projections/)*

---

### 4 — Spring Data REST **does** handle irregular plurals [Q29]

Spring Data REST ships `EvoInflectorTypeBasedCollectionResourceMapping`, which uses **[Evo Inflector](https://github.com/atteo/evo-inflector)** — an implementation of Damian Conway's *"An Algorithmic Approach to English Pluralization"*. It handles `Person → people`, `Goose → geese`, `Mouse → mice`, `Category → categories` correctly. Spring's own official guide, *[Accessing JPA Data with REST](https://spring.io/guides/gs/accessing-data-rest/)*, exposes a `Person` entity at **`/people`** with no annotation at all.

**The nuance that matters in practice:** Spring Data REST only uses Evo Inflector **if `org.atteo:evo-inflector` is on the classpath**. It is declared as an *optional* dependency, so depending on your build it may be absent — and then the fallback really is a naive `+ "s"`. So:
- Check first: `mvn dependency:tree | grep evo-inflector`.
- To pin a path explicitly the annotation is **`@RepositoryRestResource(path = "people", collectionResourceRel = "people")`** — still the right tool when you want a name the inflector *can't* guess (`User → members`), or when you want the path fixed as an API contract regardless of library behaviour, which for a public API you usually do.

Full detail in [§D5.3](04-spring-data.md#d53-naming-conventions-and-irregular-plurals-q29).

---

### 5 — A missing file is a **runtime** error in Java too [Q10]

A missing file at runtime throws `FileNotFoundException` **at runtime** in Java, exactly like Python's `FileNotFoundError`. Java cannot know at compile time whether a file will exist.

What *is* a compile error is **failing to handle or declare the checked exception** — a different thing entirely:

| | Java | Python | JS |
|---|---|---|---|
| **File is missing at runtime** | Runtime `FileNotFoundException` | Runtime `FileNotFoundError` | Runtime `Error` |
| **You didn't write `try`/`throws` for it** | **Compile error** | nothing — legal | nothing — legal |

Full detail in [§J4](01-java.md#j4-checked-vs-unchecked-exceptions-q10).

---

### The other fifteen, handled inline where they appear

| # | Topic | The fact |
|---|---|---|
| 6 | Thread-state demos | A demo that coordinates with `Thread.sleep()` races on every state read, and a `notify()` fired while the other thread is `BLOCKED` (not yet `WAITING`) is silently discarded. Deterministic version in [§J6.4](01-java.md#j64-the-six-thread-states-q4). |
| 7 | `AggregateReference` | A **Spring Data JDBC** type. Mongo's equivalents are `@DBRef` / `@DocumentReference`, or just storing the raw id field. [§D5.9](04-spring-data.md#d59-associations-and-aggregatereference-q26) |
| 8 | `.env` dependency | The maintained Spring integration is **`me.paulschwarz:spring-dotenv`**. It wraps `io.github.cdimascio:dotenv-java`, which is a plain Java library with no Spring integration of its own. [§C3.12](02-spring-core.md#c312-actually-reading-a-env-file-q12) |
| 9 | `main` method | Since **Java 25 (JEP 512)** `public`, `static` and `String[]` are all optional, and the class itself can be omitted. [§J1.5](01-java.md#j15-how-the-main-method-is-found-and-called-q1) |
| 10 | "Jackson = the View" | Conceptually yes, architecturally no — `@ResponseBody` **bypasses** view resolution entirely (`mavContainer.setRequestHandled(true)`). [§W3.6](03-spring-web.md#w36-your-specific-questions-about-mvc-mapping-q50) |
| 11 | `time.sleep(0)` in Python | Releases the GIL, but since Python 3.2 thread switching is governed by `sys.setswitchinterval` (default 5 ms) — so it is a best-effort hint, not a guaranteed switch. [§J6.6](01-java.md#j66-threadyield-q9) |
| 12 | JWT filter + `SecurityContext` | Spring Security 6 wants `SecurityContextHolder.createEmptyContext()` rather than mutation of the shared context — and the filter needs a `try/catch`, or a malformed token yields a 500 instead of a 401. [§S3.1](05-spring-security.md#s31-writing-a-jwt-filter-by-hand-q35) |
| 13 | Entity as `UserDetails` | Making a JPA `@Entity` implement `UserDetails` is a common but poor pattern. Return a detached snapshot instead. [§S2.5](05-spring-security.md#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39) |
| 14 | Bean Validation naming | **JSR 380 = Bean Validation 2.0** (`javax.validation`); **Jakarta Bean Validation 3.0+** = `jakarta.validation`. **Hibernate Validator is the reference *implementation***, a swappable artifact — not another name for the spec. A copied `javax.validation.constraints.NotNull` **compiles and silently never validates** on Boot 3. [§W7.1](03-spring-web.md#w71-the-three-layers--spec-implementation-integration) |
| 15 | Which exception validation throws | **`@RequestBody`** + `@Valid` → `MethodArgumentNotValidException`. **`@ModelAttribute`** (form) + `@Valid` → **`BindException`**. Since Spring 6 the former *extends* the latter, so catching `BindException` catches both. [§W7.5](03-spring-web.md#w75-where-validation-runs-and-what-gets-thrown) |
| 16 | Nullability annotations | `javax.annotation.Nonnull` is **JSR-305, which was never ratified** and is dormant. Today's families are Spring's own `org.springframework.lang.*` and, increasingly, **JSpecify** (adopted across Spring Framework 7). [§W7.2](03-spring-web.md#w72-javaxannotationnonnull-vs-bean-validation-q55) |
| 17 | Lazy-loading exception | The class is **`org.hibernate.LazyInitializationException`** — worth knowing exactly, since you'll be searching for it. [§S2.5](05-spring-security.md#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39) |
| 18 | SQL bind-parameter logging | On Boot 3 (Hibernate 6) the logger is **`org.hibernate.orm.jdbc.bind=TRACE`**. A logger name that no longer exists doesn't error — it silently does nothing. [§S7.1](05-spring-security.md#s71-configuration-properties-and-debugging-q34-q38) |
| 19 | Interceptors are middleware | `ClientInterceptor` / `ServerInterceptor` are **middleware, not exception types** — they don't extend `Throwable` and can't be thrown. [§P1.3](06-spring-production.md#p13-the-mental-model-interceptors-are-middleware-not-exceptions-q18) |
| 20 | springdoc version | For Boot 3 the current line is **2.9.1**; springdoc **3.1.1** targets Boot 4. [§W12.2](03-spring-web.md#w122-the-dependency-q32) |

---
---

## R2. Version landscape — November 2026

⚠️ **Read this section before you trust a tutorial.** Java and Spring move fast, and the single biggest source of wasted time for a newcomer is following a guide written for the previous generation.

### R2.1 Java

| Version | Released | LTS | Status |
|---|---|---|---|
| Java 8 | 2014 | ✅ | ⚠️ ancient, still everywhere in enterprises |
| Java 11 | 2018 | ✅ | legacy |
| **Java 17** | 2021 | ✅ | the **baseline** for Spring Boot 3 **and 4** |
| **Java 21** | 2023 | ✅ | ✅ **virtual threads**, pattern matching for switch, records patterns — the sweet spot today |
| **Java 25** | Sept 2025 | ✅ | the current LTS |
| Java 26 | March 2026 | ❌ | 6-month release, superseded Sept 2026 |
| Java 27 | Sept 2026 | ❌ | current non-LTS feature release (superseded March 2027) |
| Java 29 | Sept 2027 (planned) | ✅ | the next LTS — LTS ships every two years (17 → 21 → 25 → 29) |

💡 **Target Java 21 or 25 for new work.** Java 21 is where **virtual threads** went GA ([§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads)), which is the single biggest change to how a Spring service scales.

### R2.2 Spring

| Spring Boot | Spring Framework | Released | Java | Namespace | Status |
|---|---|---|---|---|---|
| 2.7.x | 5.3 | 2022 | 8+ | `javax.*` | ⚠️ EOL |
| 3.0–3.4 | 6.0–6.2 | 2022–24 | 17+ | **`jakarta.*`** | ⚠️ EOL |
| **3.5.x** | 6.2 | 2025 | 17+ | `jakarta.*` | ⚠️ **OSS support ended 30 June 2026** (final patch 3.5.16) |
| **4.0.x** | **7.0** | Nov 2025 | 17+ | `jakarta.*` | ✅ OSS support to Dec 2026 (latest 4.0.9, 22 Oct 2026) |
| **4.1.x** | 7.0 | June 2026 | 17+ (up to Java 26) | `jakarta.*` | ✅ **current** — latest 4.1.2 (22 Oct 2026); OSS support to July 2027 |

> ⚠️ **Every Spring Boot 3.x branch is now past OSS end-of-life.** If you're learning from a 2024–2025 course — which is very likely — you are learning Boot 3.x. **That's fine:** the architecture in this document (DispatcherServlet, IoC, the filter chain, `jakarta.*`, the component model) is unchanged in Boot 4. But know that new projects should start on **4.1**, and that a real codebase on 3.5 is on borrowed time.

#### The `javax` to `jakarta` divide — still the #1 tutorial trap

```java
import javax.persistence.Entity;         // ❌ Boot 2 — silently ignored in Boot 3/4
import jakarta.persistence.Entity;       // ✅ Boot 3+

import javax.validation.constraints.NotNull;    // ❌ compiles, NEVER validates  (§W7.1)
import jakarta.validation.constraints.NotNull;  // ✅
```
Caused by Oracle's transfer of Java EE to the Eclipse Foundation, which could not keep the `javax` name. **Nothing about the code changed except the package.**

⚠️ **But "`jakarta` is right" is not the rule — "match your Spring generation" is.** On **Boot 2.7 and earlier, `javax.*` is correct** and `jakarta.*` is the broken import. Before fixing an import, check which Spring version your module builds against.

📌 This is not hypothetical. Large codebases often run **Boot 2.7 (`javax`) and Boot 4.x (`jakarta`) side by side** during a migration, sometimes with no Boot 3 at all. If your service is on the 2.7 side, the code you touch daily is `javax.*`.

#### What changed in Spring Boot 4 / Spring Framework 7

| Change | Why it matters to you |
|---|---|
| **Jackson 3** (`tools.jackson.*`) | ⚠️ the biggest migration item — package rename, different defaults ([§W4.8](03-spring-web.md#w48-json-to-java-object-where-jsonparse-really-lives)) |
| **API versioning** built in | first-class `@RequestMapping(version = "1.1")` instead of hand-rolled path/header schemes |
| ✅ **gRPC auto-configuration** (4.1) | **directly relevant to gateway work** — a Spring-native gRPC server/client starter, so [§P1](06-spring-production.md#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21) gets first-class support |
| **JSpecify null-safety** throughout | [§W7.2](03-spring-web.md#w72-javaxannotationnonnull-vs-bean-validation-q55) |
| Servlet 6.1 / Tomcat 11+ baseline | you cannot deploy to an older container |
| SSRF mitigations | tightened defaults in the HTTP clients |
| Kotlin 2.3, resilience + retry moved into core | |

#### Version-sensitive facts used throughout this document

| Fact | Version |
|---|---|
| `WebSecurityConfigurerAdapter` removed | Spring Security **6.0** ([§S2.1](05-spring-security.md#s21-enablewebsecurity-and-the-securityfilterchain-bean-q35)) |
| `MethodArgumentNotValidException extends BindException` | Spring **6.0** ([§W7.5](03-spring-web.md#w75-where-validation-runs-and-what-gets-thrown)) |
| Trailing-slash matching removed | Spring **6.0** ([§W4.13](03-spring-web.md#w413-routing-does-declaration-order-matter)) |
| `PathPattern` default, `AntPathMatcher` deprecated | Spring **6.0** |
| Hibernate 6 renamed the bind-parameter logger | Boot **3.0** ([§S7.1](05-spring-security.md#s71-configuration-properties-and-debugging-q34-q38)) |
| Thymeleaf 3.1 dropped `#request`/`#session` | Boot **3.0** ([§W11.4](03-spring-web.md#w114--configuration-and-production-gotchas)) |
| Validation split into its own starter | Boot **2.3** ([§W7.1](03-spring-web.md#w71-the-three-layers--spec-implementation-integration)) |
| Virtual threads (`spring.threads.virtual.enabled`) | Boot **3.2** + Java 21 ([§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads)) |
| `RestClient` | Spring **6.1** ([§P1.9](06-spring-production.md#p19--resttemplate-vs-webclient-vs-restclient-vs-httpexchange)) |
| `@ServiceConnection` for Testcontainers | Boot **3.1** ([§P5.3](06-spring-production.md#p53-testing-)) |
| `@MockBean` deprecated → `@MockitoBean` | Boot **3.4** ([§P5.3](06-spring-production.md#p53-testing-)) |
| Stable `Page` serialization / `PagedModel` | Spring Data **3.3** ([§D6.6](04-spring-data.md#d66--spring-hateoas-without-spring-data-rest)) |
| `DataBinder.setDeclarativeBinding` | Spring **6.1** ([§W6.11](03-spring-web.md#w611--mass-assignment-the-vulnerability-initbinder-actually-defends-against)) |
| Structured (JSON) logging built in | Boot **3.4** ([§P5.5](06-spring-production.md#p55-observability-structured-logging-and-tracing-)) |

#### How to tell whether a tutorial is current, in ten seconds

| Red flag | Means |
|---|---|
| `import javax.persistence` / `javax.validation` | Boot 2 — **stop reading** |
| `extends WebSecurityConfigurerAdapter` | Spring Security 5 — won't compile |
| `@EnableGlobalMethodSecurity` | superseded by `@EnableMethodSecurity` |
| SpringFox, `@ApiOperation`, `Docket` | dead since 2020 — use springdoc ([§W12.1](03-spring-web.md#w121-is-this-the-same-swagger-as-fastapis-q32)) |
| `antMatchers(...)` | renamed `requestMatchers(...)` in Security 6 |
| `new RestTemplate()` for new code | use `RestClient` ([§P1.9](06-spring-production.md#p19--resttemplate-vs-webclient-vs-restclient-vs-httpexchange)) |
| Hystrix | dead — use Resilience4j ([§P2.1](06-spring-production.md#p21--resilience-timeouts-retries-circuit-breakers)) |
| `@MockBean` | deprecated — `@MockitoBean` |
| `WebMvcConfigurerAdapter` | removed — implement `WebMvcConfigurer` |

---

### R2.3 How we got here: the evolution story [+]

You will understand Spring Boot far better if you know what each generation was reacting against. Read this as five problems and five answers.

```
  2002  ── Plain Java EE / EJB ────────────────────────────────────────────
           Problem: heavyweight containers, XML everywhere, untestable code,
                    business logic tangled with infrastructure.
                           │
  2003  ── Spring Framework 1.x ─────────────────────────────────────────── 
           Answer:  Inversion of Control + Dependency Injection (§C2), AOP (§C6).
                    Plain objects (POJOs), testable with `new`.
           New problem: you configured it all in applicationContext.xml.
                           │
  2006  ── Spring 2.x/2.5 ────────────────────────────────────────────────
           Answer:  annotations — @Component, @Autowired, @Controller.
                           │
  2009  ── Spring 3.x ───────────────────────────────────────────────────
           Answer:  @Configuration / @Bean — Java config, XML now optional.
                    REST support, @PathVariable.
           New problem: still ~100 lines of setup + a web.xml + a WAR + a
                    Tomcat install before "hello world" returns.
                           │
  2014  ── SPRING BOOT 1.0 ─────────────────────────────────────────────── 
           Answer:  * auto-configuration       (§C1)  — sensible defaults from the classpath
                    * starters                 (§C1)  — one dependency pulls a curated set
                    * embedded server          (§C1)  — java -jar, no Tomcat install
                    * Actuator                (§P5)  — health/metrics out of the box
                           │
  2022  ── SPRING BOOT 3.0 / Framework 6 ──────────────────────────────────
           Forced by:  Oracle → Eclipse Foundation handover of Java EE.
           Answer:  javax.* → jakarta.*, Java 17 baseline, native images (GraalVM),
                    Micrometer observability built in.
                           │
  2025  ── SPRING BOOT 4.0 / Framework 7 ──────────────────────────────────
           Answer:  modularisation, Jackson 3, built-in API versioning,
                    JSpecify null-safety, HTTP service client registration.
```

📌 **The FastAPI parallel.** FastAPI was born in 2018 already holding most of Boot's answers: it has DI (`Depends`), an embedded server (uvicorn), auto-docs, and sane defaults, because it was designed *after* the industry had learned these lessons. Spring had to *retrofit* them onto a 2003 codebase — which is why Spring has two layers (Framework and Boot) where FastAPI has one. **Spring Framework is the engine; Spring Boot is the engine plus the wiring harness, ignition and dashboard.**

| Your FastAPI habit | Spring Framework alone | Spring Boot |
|---|---|---|
| `pip install fastapi` | pick ~8 compatible jars yourself | `spring-boot-starter-webmvc` picks them |
| `uvicorn main:app` | deploy a WAR to Tomcat | embedded Tomcat, `java -jar` |
| defaults just work | configure `DispatcherServlet`, `ViewResolver`, `MessageConverter`s | auto-configured ([§C1](02-spring-core.md#c1-the-spring-boot-mental-model-and-auto-configuration-q47-)) |
| `/docs` free | — | springdoc starter ([§W12](03-spring-web.md#w12-api-documentation-openapi-and-swagger-q32-q33)) |

💡 **Hence the mantra: Spring Boot adds no new programming model.** Every annotation you learn — `@Component`, `@Transactional`, `@Aspect` — is *Spring Framework*. Boot only decides what to switch on. That is why the migration below is mostly about *dependencies and packages*, not about how you write code.

---

### R2.4 Spring Boot 4 / Framework 7 in depth [+]

#### R2.4.1 The component version matrix

| Component | Boot 3.5 | **Boot 4.0 / 4.1** | Consequence |
|---|---|---|---|
| Spring Framework | 6.2 | **7.0** | API versioning, JSpecify, `@Proxyable` |
| Java baseline | 17 | **17** (unchanged) | ✅ no forced JDK upgrade |
| Jakarta EE | 10 | **11** | Servlet **6.1**, Jakarta Persistence **3.2** |
| Tomcat | 10.1 | **11.0** | Servlet 6.1 requires it |
| Jetty | 12.0 | 12.1 | |
| Undertow | 2.3 | ⚠️ **removed** | *incompatible with Servlet 6.1* |
| Jackson | 2.x (`com.fasterxml`) | **3.x (`tools.jackson`)** | ⚠️ the largest code-level change |
| Hibernate ORM | 6.6 | **7.x** | Jakarta Persistence 3.2 ([§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-)) |
| Spring Security | 6.5 | **7.0** | |
| Spring Data | 2025.0 | 2025.1+ | |
| Kotlin | 1.9/2.x | **2.3** | |

⚠️ **The Java baseline did *not* move.** A lot of blog posts assumed Boot 4 would require Java 21. It does not — 17 is still the floor. Java 21+ is *recommended* (virtual threads), not required.

#### R2.4.2 Modularisation — the "70 modules" change

In Boot 3, a single jar — `spring-boot-autoconfigure` — contained the auto-configuration for *everything*: JPA, Kafka, Redis, Mongo, Security, Web, Batch… Your app downloaded all of it and evaluated hundreds of `@Conditional` checks at startup, even for technologies you had never heard of.

Boot 4 splits it into dedicated modules following the pattern **`spring-boot-<technology>`**, with root package **`org.springframework.boot.<technology>`**:

```
Boot 3                               Boot 4
──────────────────────────────       ─────────────────────────────────────
spring-boot-autoconfigure            spring-boot-webmvc
  ├─ …web.servlet.*                  spring-boot-webflux
  ├─ …data.jpa.*                     spring-boot-data-jpa
  ├─ …kafka.*                        spring-boot-kafka
  ├─ …security.*                     spring-boot-security
  └─ ~everything else                … ~70 modules
```

**Why you should care:** faster startup (fewer conditions to evaluate), smaller images, and clearer dependencies. **What you must do:** if you ever `@Import`ed or referenced an auto-configuration class by its fully-qualified name — e.g. `org.springframework.boot.autoconfigure.web.servlet.WebMvcAutoConfiguration` — **that FQCN has moved.** Plain application code that never names these classes needs no change.

📌 This matters for in-house platform frameworks: some explicitly *exclude* `WebMvcAutoConfiguration` and have services re-`@Import` it by name. Those imports are exactly the lines a Boot 4 upgrade would break.

#### R2.4.3 Jackson 3 — the migration item that actually touches your code

```java
// Boot 3 — Jackson 2
import com.fasterxml.jackson.databind.ObjectMapper;
ObjectMapper mapper = new ObjectMapper();
mapper.configure(SerializationFeature.INDENT_OUTPUT, true);   // mutable, configure-after-construct

// Boot 4 — Jackson 3
import tools.jackson.databind.json.JsonMapper;
JsonMapper mapper = JsonMapper.builder()                      // immutable, builder-only
        .enable(SerializationFeature.INDENT_OUTPUT)
        .build();
```

| Boot 3 | Boot 4 |
|---|---|
| group id `com.fasterxml.jackson` | **`tools.jackson`** |
| `ObjectMapper` (mutable) | **`JsonMapper`** (immutable, built via builder) |
| `Jackson2ObjectMapperBuilderCustomizer` | **`JsonMapperBuilderCustomizer`** |
| `@JsonComponent` | **`@JacksonComponent`** |
| `@JsonMixin` | **`@JacksonMixin`** |
| `JsonObjectSerializer` | `ObjectValueSerializer` |
| `JsonValueDeserializer` | `ObjectValueDeserializer` |
| `spring.jackson.read.*` / `.write.*` | **`spring.jackson.json.read.*` / `.json.write.*`** |

⚠️ **Two behavioural changes that cause silent bugs, not compile errors:**
1. Jackson 3 **throws unchecked exceptions** — `JacksonException` extends `RuntimeException`. Your `catch (IOException e)` around `readValue` no longer catches parse failures. ([§W4.8](03-spring-web.md#w48-json-to-java-object-where-jsonparse-really-lives))
2. Auto-configuration now provides **format-specific mappers**: a `JsonMapper` for JSON and an `XmlMapper` for XML, rather than one `ObjectMapper` for both. Injecting `ObjectMapper` by type may no longer resolve the way you expect.

💡 **Why Jackson renamed its packages at all** — the same reason as `javax`→`jakarta`: a major version with breaking changes needs a *new coordinate* so that Jackson 2 and 3 can sit on one classpath during migration. This is the JVM ecosystem's standard answer to "diamond dependency hell." Python solves it differently (one version per virtualenv) — the JVM has a single flat classpath, so the package name has to carry the version.

#### R2.4.4 Built-in API versioning

Previously you hand-rolled this with `/api/v1/...` paths or a custom header + `@RequestMapping(headers = ...)`. Framework 7 makes it first-class.

> ⚠️ **MYTH: `@ApiVersion("1.1")`.**
> **This annotation does not exist** — not in Spring Framework 7, not in Spring Boot 4, not anywhere in the Spring portfolio. It appears in a lot of AI-generated and blog content about Boot 4, and it will fail to compile with *"cannot find symbol"*, sending you off to hunt for a dependency that was never missing.

```java
// ❌ WRONG — no such annotation exists
@ApiVersion("1.1")
@GetMapping("/users/{id}")
public UserV2 get(@PathVariable Long id) { … }

// ✅ RIGHT — `version` is an ATTRIBUTE on the mapping annotation you already use
@GetMapping(value = "/users/{id}", version = "1.1")
public UserV2 get(@PathVariable Long id) { … }
```

The version is an **attribute on the existing mapping annotation** — `@RequestMapping`, `@GetMapping`, `@PostMapping`, and the rest:

```java
@RestController
@RequestMapping("/api/users")
public class UserController {

    @GetMapping(version = "1.0")                 // ← the attribute, not a new annotation
    public UserV1 getV1(@PathVariable Long id) { … }

    @GetMapping(version = "1.1")
    public UserV2 getV11(@PathVariable Long id) { … }

    @GetMapping(version = "2.0+")                // ← "2.0 and above"
    public UserV3 getV2Plus(@PathVariable Long id) { … }
}
```

Then tell Spring **where the version lives** in the request:

```java
@Configuration
public class WebConfiguration implements WebMvcConfigurer {

    @Override
    public void configureApiVersioning(ApiVersionConfigurer configurer) {
        configurer.useRequestHeader("API-Version");
    }
}
```

The built-in `ApiVersionResolver` options are: **request header**, **query parameter**, **path segment** (by index — the segment must be declared as a URI variable such as `/{version}`), **media-type parameter**, or a **custom** implementation.

| Piece | What it does |
|---|---|
| `ApiVersionStrategy` | the umbrella — resolve, parse, validate, deprecate |
| `ApiVersionResolver` | pulls the raw version string out of the request |
| `ApiVersionParser` | default `SemanticApiVersionParser` → `major.minor.patch`, missing parts default to `0`, result is `Comparable` |
| `ApiVersionDeprecationHandler` | default `StandardApiVersionDeprecationHandler` sets `Deprecation` (RFC 9745), `Sunset` (RFC 8594) and `Link` headers |

**Validation behaviour:** a missing version is **required by default** → `MissingApiVersionException` (400). You can make it optional (falls back to the most recent version) or set a default. An unrecognised version → `InvalidApiVersionException` (400). Supported versions are auto-collected from the versions declared on your mappings.

✅ Versioning is also supported on the **client** side — `RestClient`, `WebClient`, HTTP-service interfaces — and in tests via `MockMvc` and `WebTestClient`.

📌 **FastAPI comparison:** you would normally mount two `APIRouter`s (`/v1`, `/v2`) or use a dependency to read a header. Spring 7's version is closer to *content negotiation* — the same URL, dispatched by version — which keeps your URL space stable.

#### R2.4.5 HTTP service clients: declarative, and now registered for you

`@HttpExchange` (Spring 6.0) let you declare an HTTP client as an interface — Java's answer to nothing in FastAPI, but very close to Retrofit or to a typed wrapper around `httpx`:

```java
@HttpExchange(url = "/repos/{owner}/{repo}", accept = "application/vnd.github.v3+json")
public interface RepositoryService {

    @GetExchange
    Repository getRepository(@PathVariable String owner, @PathVariable String repo);

    @PatchExchange(contentType = MediaType.APPLICATION_FORM_URLENCODED_VALUE)
    void updateRepository(@PathVariable String owner, @PathVariable String repo,
                          @RequestParam String name, @RequestParam String description,
                          @RequestParam String homepage);
}
```

> ⚠️ **MYTH: "to use `@HttpExchange` you build an `HttpServiceProxyFactory` yourself."**
> That was the **Spring 6** answer, and it is what almost every tutorial still shows. It still compiles and still works — but on Spring Framework 7 / Boot 4 it is per-client boilerplate you no longer write, and it deprives you of the group-level configuration below.

**The Spring 6 way — recognise it, don't write it:**

```java
// ⚠️ OBSOLETE as the default approach (still valid; needed only for exotic wiring)
RestClient restClient = RestClient.create("https://api.github.com");
RestClientAdapter adapter = RestClientAdapter.create(restClient);
HttpServiceProxyFactory factory = HttpServiceProxyFactory.builderFor(adapter).build();
RepositoryService service = factory.createClient(RepositoryService.class);
```

Every client needs its own four lines, the result is not a bean (so nothing can inject it until you write a `@Bean` method too), and base URL and timeouts are buried in Java.

#### ✅ The Spring 7 / Boot 4 way

**Step 1 — declare the interfaces**, grouped. `@ImportHttpServices` is `@Repeatable`, and takes either explicit `types` or a package to scan:

```java
@SpringBootApplication
@ImportHttpServices(group = "echo",     types = {EchoServiceA.class, EchoServiceB.class})
@ImportHttpServices(group = "greeting", basePackageClasses = GreetServiceA.class)
@ImportHttpServices(group = "github",   basePackages = "com.example.github")
public class MyApplication { }
```

| Attribute | Use |
|---|---|
| `group` | the name this set of clients shares. Omitted → the group is `"default"` |
| `types` | list the interfaces explicitly |
| `basePackages` / `basePackageClasses` | scan for `@HttpExchange` interfaces instead |

**Step 2 — configure each group in `application.yml`**, not in Java. This is the part the manual approach cannot give you:

```yaml
spring:
  http:
    clients:                          # ← global: applies to RestClient, WebClient AND RestTemplate
      connect-timeout: 1s
      read-timeout: 2s
      redirects: dont-follow
    serviceclient:                    # ← per HTTP-service GROUP, overrides the global block
      echo:
        base-url: "https://echo.zuplo.io"
        connect-timeout: 2s
        read-timeout: 2s
```

💡 **This is the actual win.** Base URL and timeouts become environment-specific configuration ([§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12)) — different per profile, overridable by an environment variable, visible in one place — instead of constants compiled into a `@Configuration` class. It is the same argument as `.env` over hard-coded URLs in FastAPI.

**Step 3 — inject the proxies.** They are ordinary beans now:

```java
@RestController
public class EchoController {
    private final EchoService echoService;
    public EchoController(EchoService echoService) { this.echoService = echoService; }
}
```

⚠️ **If the same interface appears in two groups**, injection by type is ambiguous. Ask the registry by group name instead:

```java
public EchoController(HttpServiceProxyRegistry registry) {
    this.echoService1 = registry.getClient("echo1", EchoService.class);
    this.echoService2 = registry.getClient("echo2", EchoService.class);
}
```

**Step 4 (optional) — customise in Java** what YAML cannot express, with a group configurer:

```java
@Configuration(proxyBeanMethods = false)
public class MyHttpServiceGroupConfiguration {

    @Bean
    RestClientHttpServiceGroupConfigurer groupConfigurer() {
        return groups -> {
            groups.filterByName("echo").forEachClient((group, clientBuilder) -> { … });
            groups.forEachClient((group, clientBuilder) ->
                    clientBuilder.defaultHeader("service-group", group.name()));
            groups.forEachGroup((group, clientBuilder, factoryBuilder) -> { … });
        };
    }
}
```

**The programmatic escape hatch** — when the set of clients is computed rather than listed:

```java
public class MyHttpServiceRegistrar extends AbstractHttpServiceRegistrar {
    @Override
    protected void registerHttpServices(GroupRegistry registry, AnnotationMetadata metadata) {
        registry.forGroup("echo").register(EchoServiceA.class, EchoServiceB.class);
        registry.forGroup("greeting").detectInBasePackages(GreetServiceA.class);
    }
}

@Configuration
@Import(MyHttpServiceRegistrar.class)
public class ClientConfig { }
```

#### The three eras, side by side

| | Spring 5 | Spring 6 | **Spring 7 / Boot 4** |
|---|---|---|---|
| Write the client as | a class calling `RestTemplate` | an `@HttpExchange` **interface** | an `@HttpExchange` interface |
| Create the proxy | n/a | `HttpServiceProxyFactory`, by hand, per client | **`@ImportHttpServices`** — the container does it |
| Is it a bean? | only if you write `@Bean` | only if you write `@Bean` | ✅ **automatically** |
| Base URL / timeouts | Java constants | Java constants | ✅ **`application.yml`, per group** |
| Cross-cutting headers | an interceptor per client | an interceptor per client | ✅ one `HttpServiceGroupConfigurer` |

📌 **Also auto-configured for you in Boot 4**, for when you are not using the interface style: a prototype **`RestClient.Builder`** (and `RestTemplateBuilder` for legacy code), pre-wired with `HttpMessageConverters` and a `ClientHttpRequestFactory`, and obeying the same `spring.http.clients.*` properties:

```java
public MyService(RestClient.Builder restClientBuilder) {
    this.restClient = restClientBuilder.baseUrl("https://example.org").build();
}
```

⚠️ **Inject the *builder*, never a shared `RestClient`** — the builder bean is a prototype precisely so each service can set its own base URL without mutating everyone else's client.

✅ **API versioning works on the client too** — `RestClient`, `WebClient` and `@HttpExchange` interfaces can all send the version that [§R2.4.4](#r244-built-in-api-versioning) configures on the server.

See [§P1.9](06-spring-production.md#p19--resttemplate-vs-webclient-vs-restclient-vs-httpexchange) for how this compares to `RestTemplate` / `WebClient` / `RestClient`.

#### R2.4.6 JSpecify null-safety

Spring's own `@Nullable`/`@NonNull` annotations are replaced throughout by **[JSpecify](https://jspecify.dev/)**, a vendor-neutral standard backed by Google, JetBrains, Oracle, Uber and others.

```java
import org.jspecify.annotations.NullMarked;
import org.jspecify.annotations.Nullable;

@NullMarked                                     // everything in here is non-null by default
package com.example.orders;                     // ← usually in package-info.java
```

There are **four** annotations, not two:

| Annotation | Meaning |
|---|---|
| `@Nullable` | this type may be `null` |
| `@NonNull` | this type is not `null` |
| `@NullMarked` | **within this scope, unannotated types are non-null** — the one that does the real work |
| `@NullUnmarked` | opt a scope back out |

💡 **The mental model from Python:** `@NullMarked` on a package is the Java equivalent of turning on strict mode in mypy/pyright for a module — `str` means `str`, and you must write `Optional[str]` (i.e. `@Nullable String`) to allow `None`. Without `@NullMarked`, unannotated Java types are "unknown nullness" — exactly like an untyped Python function.

⚠️ **JSpecify is purely a *static-analysis* contract.** Nothing checks it at runtime. You need a checker — **NullAway**, the Error Prone plugin, which was open-sourced *by Uber* — to actually fail the build. That is very different from Bean Validation's `@NotNull` ([§W7.2](03-spring-web.md#w72-javaxannotationnonnull-vs-bean-validation-q55)), which *is* a runtime check on request data. **Two different jobs, confusingly similar names.**


#### R2.4.7 Other Framework 7 additions worth knowing

| Addition | Why it matters |
|---|---|
| `@Proxyable(INTERFACES \| TARGET_CLASS)` | per-bean override of the JDK-vs-CGLIB proxy choice ([§C6.11](02-spring-core.md#c611-the-dependency-and-why-it-works-without-enableaspectjautoproxy-)) |
| Resilience (`@Retryable`, `@ConcurrencyLimit`) moved into **core** | no Spring Retry dependency needed for basic retries ([§P2.1](06-spring-production.md#p21--resilience-timeouts-retries-circuit-breakers)) |
| ✅ **gRPC auto-configuration** (Boot 4.1) | a Spring-native gRPC server/client starter ([§P1](06-spring-production.md#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21)) |
| SSRF mitigations | tightened redirect/host handling in the HTTP clients |
| Bean registration DSL / programmatic `BeanRegistrar` | AOT- and native-image-friendly alternative to `@Bean` methods |

---

### R2.5 What did *not* change [+]

Just as important as the change list, because it tells you how much of what you have learned still applies. **All of this is identical in Boot 3 and Boot 4:**

- The IoC container, bean scopes, and the full lifecycle ([§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13)).
- `@Component` / `@Service` / `@Repository` / `@Configuration` / `@Bean` / `@Autowired`.
- `DispatcherServlet` and the entire request pipeline ([§W2](03-spring-web.md#w2-front-controller-and-dispatcherservlet-q41-q45-q46-q48)).
- The servlet filter chain and Spring Security's `SecurityFilterChain` ([§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)).
- Auto-configuration and `@Conditional*` ([§C1](02-spring-core.md#c1-the-spring-boot-mental-model-and-auto-configuration-q47-)).
- Spring AOP's proxy model and every gotcha in [§C6.9](02-spring-core.md#c69-the-gotchas-that-will-actually-bite-you-).
- JPA mapping annotations and relationship semantics ([§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-)).
- `jakarta.*` — that migration happened in **3.0**, not 4.0.

💡 **So a 2024 Spring Boot 3 course is still ~90 % accurate.** Learn from it without anxiety; just keep [§R2.6](#r26-the-boot-3--boot-4-migration-checklist-) in mind as the delta.

---

### R2.6 The Boot 3 → Boot 4 migration checklist [+]

Work top to bottom. Items are ordered by how likely they are to bite.

**1 — Prerequisite: be on the latest 3.5.x first.** Every deprecation warning you fix on 3.5 is a compile error you avoid on 4.0.

**2 — Rename the starters.**

| Boot 3 | Boot 4 |
|---|---|
| `spring-boot-starter-web` | **`spring-boot-starter-webmvc`** |
| `spring-boot-starter-aop` | **`spring-boot-starter-aspectj`** |
| `spring-boot-starter-web-services` | **`spring-boot-starter-webservices`** |
| `spring-boot-starter-oauth2-client` | **`spring-boot-starter-security-oauth2-client`** |
| `spring-boot-starter-oauth2-resource-server` | **`spring-boot-starter-security-oauth2-resource-server`** |
| `spring-boot-starter-oauth2-authorization-server` | **`spring-boot-starter-security-oauth2-authorization-server`** |

⚠️ For `spring-boot-starter-aspectj`, the migration guide adds: *"Please review if you actually need it before using the replacement."* If you never wrote your own `@Aspect`, you don't — `@Transactional`, `@Async` and `@Cacheable` work without it ([§C6.11](02-spring-core.md#c611-the-dependency-and-why-it-works-without-enableaspectjautoproxy-)).

**3 — Migrate Jackson 2 → 3** (§R2.4.3). Package, class names, property keys, and the unchecked-exception change.

**4 — Fix any auto-configuration FQCNs** you reference in `@Import`, `@ImportAutoConfiguration`, `spring.autoconfigure.exclude`, or `@SpringBootTest(excludeAutoConfiguration = …)` (§R2.4.2).

**5 — Replace what was removed.**

| Removed in Boot 4 | Do this instead |
|---|---|
| **Undertow** support | move to Tomcat 11 or Jetty 12.1 (Undertow is incompatible with Servlet 6.1) |
| `@MockBean` / `@SpyBean` | **`@MockitoBean` / `@MockitoSpyBean`** (deprecated back in 3.4) |
| Spock integration | Groovy 5 incompatibility |
| Spring Session Hazelcast / MongoDB | no direct support |
| Pulsar Reactive auto-configuration | |
| Uber-jar launch scripts | use a proper service manager or container |

**6 — Check Hibernate 7 / Jakarta Persistence 3.2.** Mostly source-compatible, but review `ddl-auto`, naming strategies and any use of deprecated `Criteria` APIs ([§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-)).

**7 — Only then adopt the new features** — API versioning, `@ImportHttpServices`, JSpecify. None of these are required to be on Boot 4.

💡 **Use the tooling.** OpenRewrite publishes a Boot 4 recipe, and the Spring Boot Migrator handles much of steps 2–5 mechanically. Run it, then read every diff — an automated rename cannot know whether you *needed* the AspectJ starter.

📌 **Do not skip versions.** 2.x → 4.x in one jump means absorbing the `jakarta` migration *and* the Jackson migration *and* the module split simultaneously, with no green build in between. Go 2.7 → 3.5 → 4.x.

---

### R2.7 Myths, and what is actually true [+]

⚠️ **Read this before trusting any Boot 4 / AOP content written by a blog or an AI assistant.** Each row is something widely repeated that is wrong or stale, with the verified correction and where this document covers it.

| ❌ The myth | ✅ What is actually true | § |
|---|---|---|
| `@ApiVersion("1.1")` versions an endpoint | **No such annotation exists.** `version` is an *attribute*: `@GetMapping(version = "1.1")`, plus an `ApiVersionConfigurer` to say where the version lives | [§R2.4.4](#r244-built-in-api-versioning) |
| You build an `HttpServiceProxyFactory` by hand to use `@HttpExchange` | That is the Spring 6 way. Spring 7 registers them via **`@ImportHttpServices`**, as beans, configured per group in YAML | [§R2.4.5](#r245-http-service-clients-declarative-and-now-registered-for-you) |
| Advice order is undefined unless you use `@Order` | True **between** aspects only. **Within** one aspect it is fixed by advice type and `@Order` is ignored | [§C6.9](02-spring-core.md#c69-the-gotchas-that-will-actually-bite-you-) |
| `returning =` / `throwing =` just name a variable | They also **narrow what matches** — `@AfterThrowing(throwing = "e")` with `e` typed `SQLException` only fires for that type | [§C6.5](02-spring-core.md#c65-the-five-advice-types-) |
| `@Transactional` / `@Cacheable` need the AOP starter | ❌ They work without it. `ClassProxyingConfiguration` forces class proxies when AspectJ is absent — the starter is for writing **your own** aspects | [§C6.11](02-spring-core.md#c611-the-dependency-and-why-it-works-without-enableaspectjautoproxy-) |
| `@Aspect` is enough to register an aspect | It also needs **`@Component`** (or a `@Bean` method). `@Aspect` alone marks the class and nothing instantiates it | [§C6.9](02-spring-core.md#c69-the-gotchas-that-will-actually-bite-you-) |
| Boot 4 requires Java 21 | ❌ The baseline is still **Java 17**. 21+ is recommended for virtual threads, not required | [§R2.4.1](#r241-the-component-version-matrix) |
| Boot 4 is where `javax` → `jakarta` happened | ❌ That was **Boot 3.0**, in 2022 | [§R2.2](#r22-spring) |
| JSpecify has `@Nullable` and `@NonNull` | It has **four** — `@NullMarked` is the one that does the real work, flipping a whole scope to non-null-by-default | [§R2.4.6](#r246-jspecify-null-safety) |
| JSpecify / `@NonNull` prevent NPEs at runtime | ❌ Pure metadata. You need a **checker** (NullAway, Error Prone) to fail the build. Runtime checking of request data is `jakarta.validation` — a different layer | [§W7.2](03-spring-web.md#w72-javaxannotationnonnull-vs-bean-validation-q55) |
| `spring-boot-starter-aop` is the Boot 4 artifact | Renamed to **`spring-boot-starter-aspectj`** — and the migration guide says *"review if you actually need it"* | [§R2.6](#r26-the-boot-3--boot-4-migration-checklist-) |
| `spring-boot-starter-web` is still the web starter | Renamed to **`spring-boot-starter-webmvc`** in Boot 4 | [§R2.6](#r26-the-boot-3--boot-4-migration-checklist-) |
| Spring AOP can advise any method | **Method *executions* on Spring beans only.** Not `private`, not `final`, not constructors, not fields, not self-invocation, not `new`-ed objects | [§C6.9](02-spring-core.md#c69-the-gotchas-that-will-actually-bite-you-) |
| Streams behave like JS array methods | ❌ Streams are **lazy**; `.map()` with no terminal operation does **nothing at all** | [§J2.9](01-java.md#j29-streams--your-comprehensions-and-array-methods) |
| proto3 `int32 x = 1;` can tell 0 from unset | ❌ Not without the **`optional`** keyword. Message fields and `oneof` members always track presence; scalars do not | [§P1.10](06-spring-production.md#p110--protobuf-the-schema-and-the-java-it-generates) |

💡 **Why so many of these are AI-generated errors specifically.** Each one is a *plausible extrapolation*: Spring does have `@Order`, so `@ApiVersion` "should" exist; annotations usually control behaviour, so `@Order` "should" work everywhere. Plausibility is exactly what a language model optimises for, and exactly what a compiler does not accept. When something sounds like it must exist, check the javadoc — the [Spring Framework reference](https://docs.spring.io/spring-framework/reference/) and the [Boot 4 migration guide](https://github.com/spring-projects/spring-boot/wiki/Spring-Boot-4.0-Migration-Guide) settle all of the above in under a minute.

---

## R3. Quick revision sheet

> **Read this page the morning of an interview, or before touching a codebase after a break.** Everything here is expanded elsewhere; the section link is the jump target.

### R3.1 The thirteen mental models that carry everything else

| # | Model | Section |
|---|---|---|
| 1 | **The JVM runs bytecode, not Java.** `javac` → `.class` → JIT compiles hot paths to native. This is why Java is slow to start and fast once warm. | [§J1.3](01-java.md#j13-the-runtime-picture-jdk-jre-jvm-bytecode-jit-) |
| 2 | **Java threads are real OS threads** (1:1), no GIL, true parallelism — until Java 21's **virtual threads**, which are M:N like Go. | [§J6.1](01-java.md#j61-who-actually-creates-and-schedules-threads-q7-q8) |
| 3 | **Spring is a container that builds your objects for you.** You declare *what*; it decides *when* and *in what order*. | [§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13) |
| 4 | **Spring Boot = Spring + auto-configuration + an embedded server.** It's Spring with conditional defaults, not a new framework. | [§C1](02-spring-core.md#c1-the-spring-boot-mental-model-and-auto-configuration-q47-) |
| 5 | **One servlet (`DispatcherServlet`) handles every request** and dispatches to your methods. The Front Controller pattern. | [§W2](03-spring-web.md#w2-front-controller-and-dispatcherservlet-q41-q45-q46-q48) |
| 6 | **Thread-per-request, blocking is normal.** ~200 Tomcat workers. Not an event loop — the opposite of Node. | [§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads) |
| 7 | **JSON never becomes a `String`.** Jackson streams bytes ↔ objects directly over the socket. | [§W4.8](03-spring-web.md#w48-json-to-java-object-where-jsonparse-really-lives) |
| 8 | **Routing sorts by specificity, not declaration order** — the opposite of FastAPI and Express. | [§W4.13](03-spring-web.md#w413-routing-does-declaration-order-matter) |
| 9 | **Security is a filter chain in front of everything**, and authorization is its *last* filter. | [§S1.2](05-spring-security.md#s12-the-architecture-the-servlet-filter-chain-q34) |
| 10 | **Anything annotated is a proxy** — `@Transactional`, `@PreAuthorize`, `@Async`, `@Cacheable`. **Self-invocation silently skips it.** | [§C2.13](02-spring-core.md#c213-what-actually-happens-at-startup-the-mechanism) |
| 11 | **AOP is how that proxy gets its behaviour.** A pointcut selects methods, advice wraps them, and the container swaps the proxy in at startup. Spring AOP = **method executions on Spring beans**, nothing else. | [§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-) |
| 12 | **Streams are lazy; JS array methods are eager.** No terminal operation means nothing runs at all. | [§J2.9](01-java.md#j29-streams--your-comprehensions-and-array-methods) |
| 13 | **Boot 4 changes dependencies and packages, not the programming model.** Starter renames, Jackson 3, a module split — every annotation you know still works. | [§R2.6](#r26-the-boot-3--boot-4-migration-checklist-) |
| 14 | **A "function" in Java is an object of a one-abstract-method interface.** `Predicate`/`Function`/`Consumer`/`Supplier`; `StreamObserver` (3 methods) is *not* functional. | [§J2.8](01-java.md#j28-functional-interfaces-lambdas-and-method-references--functions-in-java) |
| 15 | **A unary gRPC handler runs in `onHalfClose`, not `onMessage`.** `ServerCall` sends, `ServerCall.Listener` receives; exactly one of `onComplete`/`onCancel` fires. | [§P1.12](06-spring-production.md#p112--inside-a-grpc-call-the-call-objects-the-callbacks-and-the-unary-lifecycle) |
| 16 | **gRPC server interceptors run in reverse of the order they're registered; end every call path with exactly one of `onCompleted`/`onError`.** | [§P1.13](06-spring-production.md#p113--interceptors-clientserver-symmetry-and-execution-order), [§P1.14](06-spring-production.md#p114--streamobserver-the-rules-corrected) |

### R3.2 Python / JavaScript to Java translation

| You know | Java / Spring |
|---|---|
| `pip` / `npm` · `requirements.txt` / `package.json` | Maven or Gradle · `pom.xml` / `build.gradle` |
| virtualenv / `node_modules` | the classpath + a fat JAR |
| `uvicorn app:app` / `node server.js` | `java -jar app.jar` (Tomcat is **inside**) |
| `@app.get("/x")` / `app.get('/x')` | `@GetMapping("/x")` |
| `FastAPI()` / `express()` | `DispatcherServlet` |
| middleware | `Filter` (container) or `HandlerInterceptor` (Spring) |
| Pydantic model / Zod schema | a `record` + Bean Validation annotations |
| `Depends(get_db)` | constructor injection |
| `.env` + python-dotenv | `application.yml` + profiles + `@ConfigurationProperties` |
| `raise HTTPException(404)` | `throw new ResponseStatusException(NOT_FOUND)` |
| `@app.exception_handler` | `@RestControllerAdvice` + `@ExceptionHandler` |
| SQLAlchemy / Prisma | JPA / Hibernate + Spring Data |
| `requests` / `axios` | `RestClient` (or `@HttpExchange`) |
| `asyncio.gather` | `CompletableFuture.allOf` |
| `async`/`await` | `CompletableFuture`, or ✅ **virtual threads** (just write blocking code) |
| `threading.Lock` | `synchronized` / `ReentrantLock` |
| `Optional[T]` / `T \| null` | `Optional<T>` |
| Jinja2 / EJS | Thymeleaf |
| pytest + TestClient | JUnit 5 + `MockMvc` |
| OpenAPI (built in) | springdoc (one dependency) |
| a `@decorator` around a function | an **`@Aspect`** with a pointcut — but applied to *many* methods at once ([§C6.10](02-spring-core.md#c610-the-pythonfastapi-translation-)) |
| `functools.wraps` | nothing needed — the proxy preserves the signature |
| `@app.middleware("http")` | `Filter` / `HandlerInterceptor` — **not** AOP; HTTP-only |
| Pydantic `Optional[int] = None` | protobuf `optional int32` ([§P1.10](06-spring-production.md#p110--protobuf-the-schema-and-the-java-it-generates)) |
| a generator expression `(f(x) for x in xs)` | `xs.stream().map(f)` — both lazy |
| a list comprehension `[f(x) for x in xs]` | `xs.stream().map(f).toList()` — the terminal op materialises it |

### R3.3 The annotations, by job

```
COMPONENT / WIRING
  @SpringBootApplication  = @Configuration + @EnableAutoConfiguration + @ComponentScan
  @Component @Service @Repository @Controller @RestController @Configuration
  @Bean  @Autowired(avoid—use constructors)  @Qualifier  @Primary  @Lazy  @Scope
  @Value("${k:default}")   @ConfigurationProperties(prefix="app")   @Profile("prod")

WEB
  @RequestMapping(class-level base path) + @GetMapping/@PostMapping/@PutMapping/
                                            @PatchMapping/@DeleteMapping
  @PathVariable  @RequestParam  @RequestBody  @RequestHeader  @CookieValue
  @RequestPart   @ModelAttribute  @ResponseStatus  @ResponseBody  @CrossOrigin
  ResponseEntity<T>   ProblemDetail   @RestControllerAdvice + @ExceptionHandler
  @InitBinder (binding hooks — NOT for @RequestBody)

VALIDATION   (needs spring-boot-starter-validation!)
  @Valid  @Validated   @NotNull @NotEmpty @NotBlank  @Size @Min @Max @Range
  @Email @Pattern @Past @Future @Positive @Digits @AssertTrue
  BindingResult (forms only)   custom: @Constraint + ConstraintValidator

DATA
  @Entity @Table @Id @GeneratedValue @Column  @OneToMany @ManyToOne @ElementCollection
  @Transactional(readOnly=true)   @Query   @EntityGraph(attributePaths={"x"})
  @RepositoryRestResource  @RestResource(exported=false)  @Projection

AOP  (needs spring-boot-starter-aspectj — was -aop before Boot 4)
  @Aspect + @Component   @Order(n) on the ASPECT CLASS
  @Pointcut("execution(* com.example.service..*.*(..))")
  @Before  @AfterReturning(returning="r")  @AfterThrowing(throwing="e")  @After
  @Around  →  ProceedingJoinPoint.proceed()   (return type MUST be Object)
  ⚠️ self-invocation, private and final methods are NOT advised

SECURITY
  @EnableWebSecurity  @EnableMethodSecurity   SecurityFilterChain bean
  @PreAuthorize("hasRole('X') or #id == authentication.principal.id")
  @PostAuthorize  @Secured  @RolesAllowed    PasswordEncoder bean

DOCS        @Operation  @Schema  @Tag  @ApiResponse  @Hidden   (io.swagger.v3.oas.annotations)
TEST        @SpringBootTest  @WebMvcTest  @DataJpaTest  @MockitoBean  @Testcontainers
LOMBOK      @RequiredArgsConstructor  @Slf4j  @Getter  @Builder  @Value
```

### R3.4 The request lifecycle in one block

```
socket bytes
 → Tomcat Acceptor → Poller → worker thread "http-nio-8080-exec-N"
 → Http11Processor parses → HttpServletRequest
 → FILTER CHAIN  (encoding, CORS, CSRF, [security ~16 filters], metrics)
 → DispatcherServlet.doDispatch()
     → HandlerMapping          which @GetMapping method?      404/405/415/406
     → HandlerInterceptor.preHandle
     → HandlerAdapter → ArgumentResolvers
         → HttpMessageConverter → ObjectMapper.readValue(InputStream)   ← "JSON.parse"
         → Validator (@Valid)                                           → 400
     → Method.invoke(controllerBean, args)          ← YOUR CODE
     → ReturnValueHandler → content negotiation
         → HttpMessageConverter → ObjectMapper.writeValue(OutputStream) ← "stringify"
     → (or) HandlerExceptionResolver → @ExceptionHandler → ProblemDetail
 → Http11OutputBuffer → socket → keep-alive
 → worker returns to the pool
```
**Breakpoints:** `DispatcherServlet#doDispatch` · `RequestMappingHandlerMapping#lookupHandlerMethod` · `InvocableHandlerMethod#doInvoke` · `AbstractJackson2HttpMessageConverter#readInternal` — [§W4.16](03-spring-web.md#w416-debugging-cheatsheet-where-to-put-a-breakpoint)

### R3.5 The traps that will actually bite you

| ⚠️ | Section |
|---|---|
| Forgot `spring-boot-starter-validation` → `@Valid` **silently does nothing** | [§W7.1](03-spring-web.md#w71-the-three-layers--spec-implementation-integration) |
| `import javax.*` instead of `jakarta.*` → compiles, never runs | [§R2.2](#r22-spring) |
| `@RestController` where you meant `@Controller` → the view name prints as text | [§W11.2](03-spring-web.md#w112-do-you-create-the-html-file-yourself-q16) |
| Self-invocation bypasses `@Transactional` / `@PreAuthorize` / `@Async` | [§C2.13](02-spring-core.md#c213-what-actually-happens-at-startup-the-mechanism) |
| Stored `ADMIN` but wrote `hasRole("ADMIN")` → looks for `ROLE_ADMIN` → silent 403 | [§S4.3](05-spring-security.md#s43-roles-authorities-and-the-role_-prefix-q36-q40) |
| `anyRequest().authenticated()` placed first → every later rule unreachable | [§S4.2](05-spring-security.md#s42-declarative-security--the-central-configuration-q34) |
| No `PasswordEncoder` bean → `There is no PasswordEncoder mapped for the id "null"` | [§S2.6](05-spring-security.md#s26-passwords-hashing-salting-and-the-bcrypt-migration-q34-q37-q14) |
| Nested `@Valid` omitted → inner object never validated | [§W7.3](03-spring-web.md#w73-the-annotation-catalogue-q55) |
| `BindingResult` not immediately after the validated parameter | [§W7.6](03-spring-web.md#w76-bindingresult-q55) |
| Un-annotated POJO parameter = `@ModelAttribute`, so a JSON body is ignored | [§W6.2](03-spring-web.md#w62-the-complete-where-does-this-value-come-from-table-q55) |
| Reading the request body in a filter empties it for `@RequestBody` | [§W4.8](03-spring-web.md#w48-json-to-java-object-where-jsonparse-really-lives) |
| Unchecked checkbox submits nothing → boolean never set to false | [§W6.4](03-spring-web.md#w64-data-binding-for-html-forms-q55) |
| `new RestTemplate()` → **no timeouts** → thread pool exhaustion | [§P2.1](06-spring-production.md#p21--resilience-timeouts-retries-circuit-breakers) |
| `ClientInterceptors.intercept(a, b)` runs **b first** | [§P1.6](06-spring-production.md#p16-interceptor-ordering--and-the-reversal-trap) |
| gRPC `Metadata.Key` must be **lowercase** | [§P1.7](06-spring-production.md#p17-the-complete-worked-example-a-gateway-calling-a-payment-service-q20) |
| N+1 queries on every list endpoint | [§D4.3](04-spring-data.md#d43-the-n1-query-problem-) |
| JPA entity as `@RequestBody` → mass assignment | [§P5.2](06-spring-production.md#p52-dtos-vs-entities--never-expose-your-entities-) |
| `MDC`/`ThreadLocal` not cleared → leaks into the next request on a pooled thread | [§P5.5](06-spring-production.md#p55-observability-structured-logging-and-tracing-) |
| `spring.data.rest.detection-strategy` left at `DEFAULT` → every repository published | [§D5.11](04-spring-data.md#d511-configuration-properties-q29) |
| `?projection=` hides a field from JSON but still **loads** it — not a security control | [§D5.7](04-spring-data.md#d57-projections-q30--and-what-they-actually-optimise) |
| Thread priorities on Linux are effectively a **no-op** | [§J6.5](01-java.md#j65-thread-priorities-q5-q6--and-what-they-actually-do-on-linux) |
| `Integer` cache: `==` is true to 127, false at 128 | [§J2](01-java.md#j2-the-java-essentials-you-will-hit-in-week-one-) |
| Checked exception in a lambda → won't compile | [§J4](01-java.md#j4-checked-vs-unchecked-exceptions-q10) |

### R3.6 The commands

```bash
./mvnw spring-boot:run                       # run (Gradle: ./gradlew bootRun)
./mvnw clean package                         # → target/app.jar
./mvnw test -Dtest=OrderServiceTest          # one test class
./mvnw dependency:tree                       # ⭐ diagnose a version conflict
./mvnw spring-boot:build-image               # optimized OCI image, no Dockerfile
java -jar app.jar --spring.profiles.active=prod --server.port=9000
java -jar app.jar --debug                    # ⭐ the auto-configuration conditions report

jps -l                                       # running JVMs
jstack <pid>                                 # ⭐ thread dump — deadlocks, pool exhaustion
jcmd <pid> GC.heap_info
javap -c -p ClassName                        # disassemble bytecode  (§J1.3)

curl localhost:8080/actuator/mappings        # ⭐ every registered route
curl localhost:8080/actuator/conditions      # why did/didn't an auto-config apply
```

### R3.7 The traps from your November 2026 notes

Each row is a claim from the tutorials or chats that turned out to be wrong or only half right. The link goes to the full explanation.

| You might believe | What is actually true | Where |
|---|---|---|
| `postHandle` is too early because JSON isn't written yet | For `@ResponseBody`/`ResponseEntity` the JSON is already written and committed **before** `postHandle`. Use `afterCompletion` for timing because `postHandle` is skipped on exceptions | [§W5.5](03-spring-web.md#w55-posthandle-vs-aftercompletion-and-the-timing-example) |
| Interceptors never see static resources | Interceptors registered with `addInterceptors` also run for Spring MVC's resource handler | [§W5.3](03-spring-web.md#w53-does-an-interceptor-run-for-every-endpoint) |
| Filters can't use Spring beans | In Boot, a `Filter` declared as a bean is injected like any other bean and auto-registered | [§W5.4](03-spring-web.md#w54-filter-server-interceptor-or-client-interceptor-the-decision-guide) |
| `@CrossOrigin` + global CORS: the most specific wins | List properties are **combined** (union) | [§W9.4](03-spring-web.md#w94-global--local-combined-not-most-specific-wins) |
| `@RestController` = `@Component` + `@ResponseBody` | It is `@Controller` + `@ResponseBody`; since Spring 6 only `@Controller` classes are detected as handlers | [§W8.1](03-spring-web.md#w81-controller-vs-restcontroller-what--controller--responsebody-means) |
| `@InitBinder` never touches `@RequestBody` | Its *validators* do apply to `@Valid @RequestBody`; its editors don't | [§W6.9](03-spring-web.md#w69-initbinder-q55-q56) |
| Removing a child from a `mappedBy` list sets its FK to NULL | Nothing happens in the DB unless `orphanRemoval` is on or you change the owning side | [§D3.5](04-spring-data.md#d35-your-mappedby-questions-answered-one-by-one) |
| `deleteBy…` repository methods just work | Derived deletes need a transaction | [§D4.2](04-spring-data.md#d42-which-repository-methods-are-transactional-by-default--and-the-deleteby-trap) |
| `NOTIFICATION_MAX_RETRY_COUNT` sets `notification.max-retry-count` | Dashes are **removed**: `NOTIFICATION_MAXRETRYCOUNT` | [§C3.8](02-spring-core.md#c38-binding-rules-names-nesting-collections) |
| `@ConditionalOnMissingBean` is safe in any `@Configuration` | Only reliable on auto-configuration classes | [§C4.7](02-spring-core.md#c47-auto-configuration-ordering--why-onbean-conditions-are-only-safe-there) |
| Record `@ConfigurationProperties` get a fresh instance on refresh | Constructor-bound (record) properties are not refreshed at all | [§C3.11](02-spring-core.md#c311-runtime-refresh-which-properties-update-and-which-dont) |
| `@ControllerAdvice` never sees event-listener exceptions | A synchronous listener's exception propagates to the publisher, so to `@ControllerAdvice` | [§C7.9](02-spring-core.md#c79-handling-listener-exceptions-globally) |
| A long `fixedRate` task overlaps the next run | On the default (platform-thread) scheduler it never overlaps itself; the next run starts late. Overlap needs `@Async`. ⚠️ With `spring.threads.virtual.enabled=true` it **can** overlap (thread-per-run `SimpleAsyncTaskScheduler`) | [§P3.2](06-spring-production.md#p32-writing-scheduled-tasks-and-the-four-trigger-types-) |
| Resilience4j retries are non-blocking | Only for async/reactive methods; synchronous retries sleep the thread | [§P2.4](06-spring-production.md#p24-resilience4j-retry-and-how-it-differs-from-spring-retry-) |
| `@PostFilter` removes the items that match | It **keeps** the items where the expression is true | [§S4.7](05-spring-security.md#s47-postauthorize-prefilter-postfilter-in-depth) |
| `@AuthorizeReturnObject` goes on the DTO class | It goes on the method (or class) whose *return value* should be proxied | [§S4.8](05-spring-security.md#s48-graceful-denial-handleauthorizationdenied-authorizereturnobject-and-clean-403-json) |
| Passwords are decrypted to check them | They are never decrypted: `matches()` re-hashes the input with the stored salt | [§S2.2](05-spring-security.md#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder) |
| `ScopedValue` is a Java 21 feature inherited by every child thread | Preview in 21–24, final in 25; inherited only by `StructuredTaskScope` forks | [§J6.13](01-java.md#j613-threadlocal-inheritablethreadlocal-and-scopedvalue-per-thread-context-vs-pythons-contextvar) |
| Lombok `@Data` doesn't generate a constructor | It includes `@RequiredArgsConstructor` | [§J5.4](01-java.md#j54-the-lombok-annotations-youll-actually-see) |


---

## R4. Glossary

**Terms are grouped so related concepts sit together.** Bold entries are the ones worth being able to define out loud.

### Java platform

| Term | Meaning |
|---|---|
| **JVM** | Java Virtual Machine — executes bytecode, manages memory and threads |
| **JDK** | Java Development Kit — JVM + compiler (`javac`) + tools (`javap`, `jstack`) |
| **JRE** | Java Runtime Environment — JVM + libraries, no compiler. Not shipped separately since Java 11 |
| **Bytecode** | the portable `.class` instruction set `javac` emits |
| **JIT** | Just-In-Time compiler — compiles hot bytecode to native code at runtime (C1 = fast, C2 = optimizing) |
| **GC** | Garbage Collector — G1 (default), ZGC / Shenandoah (low-pause) |
| **Classpath** | where the JVM looks for classes |
| **Fat JAR / uber JAR** | one archive containing your code **and** every dependency **and** an embedded server |
| **Type erasure** | generics exist at compile time only; `List<String>` is a `List` at runtime |
| **Autoboxing** | automatic `int` ↔ `Integer` conversion. ⚠️ the `Integer` cache makes `==` behave oddly |
| **Checked exception** | must be caught or declared — a compile-time obligation. Unique to Java |
| **Record** | an immutable data carrier with generated constructor/accessors/`equals`/`hashCode` |
| **Sealed** | a type that restricts which classes may extend it |

### Concurrency

| Term | Meaning |
|---|---|
| **Platform thread** | a 1:1 wrapper over an OS thread; ~1MB stack |
| **Virtual thread** | Java 21+; thousands per OS thread, M:N scheduled. ✅ blocking code at event-loop scale |
| **`synchronized`** | intrinsic monitor lock on an object |
| **`volatile`** | guarantees visibility across threads; does **not** give atomicity |
| **happens-before** | the JMM ordering guarantee that makes a write visible to another thread |
| **CAS** | Compare-And-Swap — the lock-free primitive under `AtomicInteger` |
| **`ExecutorService`** | a managed thread pool |
| **`CompletableFuture`** | a composable async result. `thenApply` = map, `thenCompose` = flatMap |
| **Work stealing** | idle ForkJoinPool threads take tasks from busy ones' queues |
| **Spurious wakeup** | `wait()` can return without a `notify()` — ⚠️ **always loop, never `if`** |

### Spring core

| Term | Meaning |
|---|---|
| **IoC** | Inversion of Control — the framework creates and wires your objects |
| **DI** | Dependency Injection — the concrete pattern implementing IoC |
| **Bean** | an object the Spring container manages |
| **`ApplicationContext`** | the container itself |
| **Stereotype** | `@Component`, `@Service`, `@Repository`, `@Controller` — scannable markers |
| **Component scan** | startup search for stereotypes under the root package |
| **Auto-configuration** | Boot's conditional defaults from `AutoConfiguration.imports` |
| **Starter** | a curated dependency bundle (`spring-boot-starter-web`) |
| **BOM** | Bill of Materials — a POM that pins compatible versions |
| **Proxy** | the generated wrapper implementing `@Transactional`, `@PreAuthorize`, `@Async`, `@Cacheable`. ⚠️ self-invocation bypasses it |
| **AOP** | Aspect-Oriented Programming — cross-cutting behaviour woven in via proxies |
| **Profile** | a named configuration set (`dev`, `prod`) |
| **Relaxed binding** | `APP_MAX_RETRIES` ↔ `app.max-retries` ↔ `app.maxRetries` |

### Aspect-Oriented Programming

| Term | Meaning |
|---|---|
| **Cross-cutting concern** | behaviour needed in many places but belonging to none of them — logging, metrics, transactions, security |
| **Scattering** | the same concern duplicated across many classes |
| **Tangling** | one method mixing business logic with several concerns |
| **Aspect** | the module that bundles a concern: `@Aspect` + `@Component` |
| **Join point** | a point where advice *could* run. ⚠️ In **Spring AOP this is always a method execution** |
| **Pointcut** | the expression selecting join points — `execution(...)`, `@annotation(...)` |
| **Advice** | the code that runs: `@Before`, `@After`, `@AfterReturning`, `@AfterThrowing`, `@Around` |
| **`JoinPoint`** | the advice parameter exposing signature and arguments |
| **`ProceedingJoinPoint`** | `@Around`-only; adds **`proceed()`** — call the real method |
| **Weaving** | linking aspects to target code: compile-time, post-compile, **load-time (LTW)**, or **runtime proxy** (Spring's) |
| **Target object** | the real bean, wrapped by the proxy |
| **Introduction** | adding a new interface/method to a type (AspectJ; `@DeclareParents`) |
| **JDK dynamic proxy** | a proxy implementing the target's **interfaces** |
| **CGLIB proxy** | a proxy **subclassing** the target class. Boot's default (`proxy-target-class=true`) |
| **Self-invocation** | ⚠️ `this.method()` bypasses the proxy, so **no advice runs**. The #1 AOP bug |
| **`@Configurable`** | injects Spring dependencies into objects Spring did not create. Needs AspectJ weaving |
| **PCD** | Pointcut Designator. Spring supports 10; `call()`, `get()`, `set()` are AspectJ-only |

### Web layer

| Term | Meaning |
|---|---|
| **Servlet** | the Jakarta EE component handling an HTTP request |
| **Servlet container** | Tomcat / Jetty / Undertow — manages sockets, threads, servlet lifecycle |
| **`DispatcherServlet`** | Spring's **Front Controller** — the single entry point |
| **`HandlerMapping`** | resolves a request to a controller method |
| **`HandlerAdapter`** | invokes it, resolving arguments and return values |
| **`HttpMessageConverter`** | the JSON ↔ Java bridge; `MappingJackson2HttpMessageConverter` for JSON |
| **Jackson / `ObjectMapper`** | the JSON library. Streams bytes — never materialises a `String` |
| **Filter** | container-level middleware, outside Spring MVC |
| **`HandlerInterceptor`** | Spring-level middleware, knows which controller will run |
| **Content negotiation** | picking a response format from the `Accept` header |
| **`WebDataBinder`** | binds request parameters onto an object, with type conversion |
| **DTO** | Data Transfer Object — the API contract, ✅ never an entity |
| **`ProblemDetail`** | the RFC 9457 standard error body |
| **CORS** | browser cross-origin permission checks |
| **CSRF** | an attack exploiting **automatically-sent cookies**. ⚠️ cookie auth → protection required |

### Data

| Term | Meaning |
|---|---|
| **JPA** | the Java Persistence API *specification* |
| **Hibernate** | the JPA *implementation* Spring Boot ships |
| **Entity** | a class mapped to a table |
| **Repository** | a Spring Data interface; the implementation is generated |
| **Derived query** | a method name parsed into a query — `findByStatusAndCreatedAtAfter` |
| **JPQL** | object-oriented query language over entities. ⚠️ still a string, checked at runtime |
| **Querydsl** | type-safe, compile-checked query construction via generated `Q` classes |
| **N+1** | 1 query for a list + 1 per row. ⚠️ **the** performance bug |
| **`JOIN FETCH` / `@EntityGraph`** | load an association eagerly in one query |
| **`LazyInitializationException`** | touching a lazy association after the session closed |
| **Spring Data REST** | auto-exposes repositories as HAL endpoints |
| **Projection** | an interface view over an entity |
| **`DataSource`** | the JDBC connection pool (HikariCP) |

### Hypermedia and docs

| Term | Meaning |
|---|---|
| **HATEOAS** | Hypermedia As The Engine Of Application State — responses carry the available next actions |
| **HAL** | `application/hal+json` — the standard layout: `_links`, `_embedded` |
| **rel** | a link's semantic name — the key inside `_links` |
| **ALPS** | semantic profile metadata (Spring Data REST's `/profile`) |
| **OpenAPI** | the API description *specification* |
| **Swagger** | the *toolset* around it (Swagger UI) |
| **springdoc** | the library generating OpenAPI from Spring code. ⚠️ SpringFox is dead |

### Security

| Term | Meaning |
|---|---|
| **Authentication** | *who are you* → 401 if unknown |
| **Authorization** | *may you do this* → 403 if not |
| **`SecurityFilterChain`** | the bean defining the filter list and the rules |
| **`FilterChainProxy` / `DelegatingFilterProxy`** | the bridge from the servlet container to Spring beans |
| **`SecurityContextHolder`** | the `ThreadLocal` holding the current `Authentication` |
| **`UserDetailsService`** | the single-method contract for loading a user from anywhere |
| **`GrantedAuthority`** | one permission string. ⚠️ `hasRole("X")` looks for `ROLE_X` |
| **`PasswordEncoder`** | the hashing strategy. BCrypt salts automatically; output is always 60 chars |
| **`DelegatingPasswordEncoder`** | dispatches on a `{bcrypt}`-style prefix — enables zero-downtime migration |
| **JWT** | a signed token; validated in-memory, **no DB call per request** |
| **RBAC** | Role-Based Access Control |
| **LDAP** | a corporate directory protocol; Active Directory is the common implementation |
| **Mass assignment** | binding untrusted input onto every field of an object — the Spring4Shell class |

### gRPC and downstream

| Term | Meaning |
|---|---|
| **Protobuf** | binary serialisation defined by a `.proto` schema; field **numbers**, not names, are the contract |
| **Field presence** | whether "unset" is distinguishable from "default". ⚠️ proto3 scalars need `optional` to get `hasX()` |
| **`protoc`** | the compiler turning `.proto` into immutable message classes + a `Builder` |
| **Stub** | the generated client: `BlockingStub`, `Stub` (async), `FutureStub` |
| **`ImplBase`** | the generated server base class you extend |
| **`StreamObserver`** | the response channel — `onNext` / `onError` / `onCompleted` |
| **Deadline** | an absolute time by which the call must finish; propagates across hops |
| **Status code** | gRPC's 17 canonical codes, e.g. `NOT_FOUND`, `UNAVAILABLE`, `DEADLINE_EXCEEDED` |
| **gRPC** | binary RPC over HTTP/2, contract defined in `.proto` |
| **Protobuf** | the binary serialization format and IDL |
| **Stub** | the generated typed client |
| **`Metadata`** | gRPC's headers. ⚠️ keys must be lowercase |
| **`StatusRuntimeException`** | what a stub throws on a non-`OK` status |
| **`ClientInterceptor` / `ServerInterceptor`** | gRPC middleware. ⚠️ **NOT exceptions**, and ⚠️ `intercept()` **reverses** order |
| **Deadline** | a per-call time budget that **propagates downstream** — no REST equivalent |
| **`RestClient`** | Spring 6.1's modern blocking HTTP client ✅ |
| **`@HttpExchange`** | a declarative HTTP client interface — Spring's native Feign |
| **Resilience4j** | circuit breakers, retries, bulkheads, rate limiters |
| **Idempotency key** | a client-supplied id making a retried write safe |

### Operations

| Term | Meaning |
|---|---|
| **Actuator** | Boot's ops endpoints — health, metrics, mappings, loggers |
| **Micrometer** | the metrics facade (SLF4J, but for metrics) |
| **MDC** | Mapped Diagnostic Context — per-thread log fields. ⚠️ must be cleared |
| **Liveness vs readiness** | "restart me" vs "send me traffic" |
| **Testcontainers** | real dependencies in Docker, driven from a test |
| **`MockMvc`** | the servlet-layer test harness, no real network |

### Added in the November 2026 edition

| Term | Meaning |
|---|---|
| **`HandlerExecutionChain`** | the handler method plus the interceptors that apply to it, returned by `HandlerMapping` ([§W2.8](03-spring-web.md#w28-the-three-collaborators-inside-the-dispatcherservlet-handlermapping-handleradapter-handlerexecutionchain)) |
| **`HandlerAdapter`** | the strategy that actually invokes a handler; `RequestMappingHandlerAdapter` for annotated controllers |
| **`HttpMessageConverter`** | turns request/response bodies into Java objects and back; Jackson does JSON ([§W8.3](03-spring-web.md#w83-httpmessageconverter-and-jackson-who-actually-writes-the-json)) |
| **Preflight** | the browser's `OPTIONS` request asking whether a cross-origin call is allowed ([§W9.1](03-spring-web.md#w91-cors-in-60-seconds)) |
| **`RequestContextHolder`** | thread-bound access to the current request ([§W10.1](03-spring-web.md#w101-what-they-hold-and-who-fills-them)) |
| **Normal forms (1NF…BCNF)** | progressive rules that remove redundancy from relational tables ([§D1.2](04-spring-data.md#d12-quick-comparison)) |
| **HikariCP** | Boot's default JDBC connection pool ([§D2.4](04-spring-data.md#d24-hikaricp-in-spring-boot)) |
| **`DelegatingFilterProxy`** | the servlet filter that hands requests to Spring Security's `FilterChainProxy` bean ([§S1.3](05-spring-security.md#s13-your-architecture-notes-checked-delegatingfilterproxy--filterchainproxy--securityfilterchain--filters)) |
| **`ProviderManager`** | the standard `AuthenticationManager`; tries each `AuthenticationProvider` that supports the token ([§S2.2](05-spring-security.md#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder)) |
| **`AuthorizationManager`** | decides allow/deny for a request or method call ([§S4.1](05-spring-security.md#s41-the-authorization-architecture-authorizationfilter--authorizationmanager)) |
| **Refresh token** | long-lived, revocable credential used only to obtain new access tokens ([§S3.3](05-spring-security.md#s33-refresh-tokens-short-access-tokens-without-constant-re-login)) |
| **Resource server** | an API that validates bearer tokens issued by someone else ([§S5.5](05-spring-security.md#s55-pure-resource-server-oauth2resourceserver-and-mapping-roles)) |
| **CGLIB proxy** | a runtime-generated subclass that intercepts method calls ([§C5.3](02-spring-core.md#c53-cglib-what-it-is-and-how-it-works)) |
| **Scoped proxy** | a proxy that looks up the real target from its scope on every call ([§C2.10](02-spring-core.md#c210-a-prototype-inside-a-singleton-objectprovider-scoped-proxies-and-lookup)) |
| **`ApplicationEventMulticaster`** | routes published events to matching listeners ([§C7.2](02-spring-core.md#c72-how-routing-works-the-multicaster-and-the-listener-parameter)) |
| **`@RefreshScope`** | beans rebuilt after `/actuator/refresh` ([§P4.3](06-spring-production.md#p43-the-stale-config-problem-and-actuatorrefresh-)) |
| **Circuit breaker** | stops calling a failing dependency for a while ([§P2.5](06-spring-production.md#p25-combining-retry-and-circuitbreaker-why-the-order-matters-)) |
| **Record** | Java 16+ immutable data carrier ([§J5.2](01-java.md#j52-java-records-java-16)) |


---

## Closing note

Everything you asked has been preserved. **Nothing was dropped** — where two questions overlapped they were merged and cross-linked (Q14 and Q37 on bcrypt are now one place; Q17–Q21 became a single narrative on downstream calls). Where a source answer was wrong, **only the corrected version appears** — the document states what is true and nothing else, so re-reading it never re-teaches the mistake.

**A suggested revision order:**

1. **[§R3](#r3-quick-revision-sheet)** — the quick sheet. Five minutes.
2. **[§R1](#r1-twenty-facts-that-catch-people-out--read-this-first)** — the twenty high-leverage facts. Pin these before the wrong versions harden.
3. **[§W4](03-spring-web.md#w4-rest-controller--the-complete-unabstracted-request-lifecycle-q)** — the request lifecycle. If you genuinely know this one section, most Spring behaviour becomes predictable rather than magical.
4. Then whichever of [§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13) (DI), [§W7](03-spring-web.md#w7-validation-q55) (validation), [§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext) (security) or [§P1](06-spring-production.md#p1-calling-downstream-services-resttemplate-webclient-grpc-interceptors-q17q21) (downstream) matches what you're touching that week.

The two sections you'll return to most in daily work are **[§W4.16](03-spring-web.md#w416-debugging-cheatsheet-where-to-put-a-breakpoint)** (where to put a breakpoint) and **[§R3.5](#r35-the-traps-that-will-actually-bite-you)** (the traps). Bookmark those two.
