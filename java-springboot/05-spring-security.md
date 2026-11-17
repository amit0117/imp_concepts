# Spring Security — Architecture, Authentication and Authorization

[⬅ 04-spring-data.md](04-spring-data.md) · [🏠 Start here](00-start-here.md) · [06-spring-production.md ➡](06-spring-production.md)

> Part of the Java & Spring Boot learning set. Section labels in this file start with **S**. The legend, version landscape, quick revision sheet and glossary live in [00-start-here.md](00-start-here.md).

## Contents

- [S1. The architecture: from the servlet filter chain to the SecurityContext](#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext)
  - [S1.1 The mental shift from FastAPI](#s11-the-mental-shift-from-fastapi)
  - [S1.2 The architecture: the servlet filter chain [Q34]](#s12-the-architecture-the-servlet-filter-chain-q34)
  - [S1.3 Your architecture notes, checked: `DelegatingFilterProxy` → `FilterChainProxy` → `SecurityFilterChain` → filters](#s13-your-architecture-notes-checked-delegatingfilterproxy--filterchainproxy--securityfilterchain--filters)
  - [S1.4 `SecurityContextHolderFilter` — remembering the user between requests](#s14-securitycontextholderfilter--remembering-the-user-between-requests)
  - [S1.5 When it goes wrong: wrong passwords and `ExceptionTranslationFilter`](#s15-when-it-goes-wrong-wrong-passwords-and-exceptiontranslationfilter)
- [S2. Authentication: who are you?](#s2-authentication-who-are-you)
  - [S2.1 `@EnableWebSecurity` and the `SecurityFilterChain` bean [Q35]](#s21-enablewebsecurity-and-the-securityfilterchain-bean-q35)
  - [S2.2 The authentication engine: `AuthenticationManager` → `ProviderManager` → `AuthenticationProvider` → `UserDetailsService` + `PasswordEncoder`](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder)
  - [S2.3 Walkthrough: replacing the defaults with HTTP Basic + users from your database](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database)
  - [S2.4 Where users come from: the four strategies [Q34, Q36]](#s24-where-users-come-from-the-four-strategies-q34-q36)
  - [S2.5 Custom `UserDetailsService` — any schema, any database [Q36, Q38, Q39]](#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39)
  - [S2.6 Passwords: hashing, salting, and the bcrypt migration [Q34, Q37, Q14]](#s26-passwords-hashing-salting-and-the-bcrypt-migration-q34-q37-q14)
- [S3. Stateless authentication: JWT and refresh tokens](#s3-stateless-authentication-jwt-and-refresh-tokens)
  - [S3.1 Writing a JWT filter by hand [Q35]](#s31-writing-a-jwt-filter-by-hand-q35)
  - [S3.2 The complete JWT flow: login endpoint, token creation, and the filter](#s32-the-complete-jwt-flow-login-endpoint-token-creation-and-the-filter)
  - [S3.3 Refresh tokens: short access tokens without constant re-login](#s33-refresh-tokens-short-access-tokens-without-constant-re-login)
- [S4. Authorization: what are you allowed to do?](#s4-authorization-what-are-you-allowed-to-do)
  - [S4.1 The authorization architecture: `AuthorizationFilter` → `AuthorizationManager`](#s41-the-authorization-architecture-authorizationfilter--authorizationmanager)
  - [S4.2 Declarative security — the central configuration [Q34]](#s42-declarative-security--the-central-configuration-q34)
  - [S4.3 Roles, authorities, and the `ROLE_` prefix [Q36, Q40]](#s43-roles-authorities-and-the-role_-prefix-q36-q40)
  - [S4.4 Roles **and** permissions with enums, enforced by `requestMatchers`](#s44-roles-and-permissions-with-enums-enforced-by-requestmatchers)
  - [S4.5 Programmatic / method-level security [Q34, Q40]](#s45-programmatic--method-level-security-q34-q40)
  - [S4.6 Method security under the hood: interceptors, expression handler, `EvaluationContext`](#s46-method-security-under-the-hood-interceptors-expression-handler-evaluationcontext)
  - [S4.7 `@PostAuthorize`, `@PreFilter`, `@PostFilter` in depth](#s47-postauthorize-prefilter-postfilter-in-depth)
  - [S4.8 Graceful denial: `@HandleAuthorizationDenied`, `@AuthorizeReturnObject`, and clean 403 JSON](#s48-graceful-denial-handleauthorizationdenied-authorizereturnobject-and-clean-403-json)
- [S5. OAuth2: login with Google/GitHub vs resource server](#s5-oauth2-login-with-googlegithub-vs-resource-server)
  - [S5.1 Two different things both called "OAuth2"](#s51-two-different-things-both-called-oauth2)
  - [S5.2 The `oauth2Login()` flow, step by step](#s52-the-oauth2login-flow-step-by-step)
  - [S5.3 "Does Spring create a DB table for users, like Supabase?" — no; just-in-time provisioning](#s53-does-spring-create-a-db-table-for-users-like-supabase--no-just-in-time-provisioning)
  - [S5.4 Hybrid: log in with Google, then issue *your own* JWT to a SPA](#s54-hybrid-log-in-with-google-then-issue-your-own-jwt-to-a-spa)
  - [S5.5 Pure resource server: `oauth2ResourceServer()` and mapping roles](#s55-pure-resource-server-oauth2resourceserver-and-mapping-roles)
- [S6. CSRF and CORS](#s6-csrf-and-cors)
  - [S6.1 CSRF [Q34]](#s61-csrf-q34)
  - [S6.2 CORS when Spring Security is on the classpath](#s62-cors-when-spring-security-is-on-the-classpath)
- [S7. Configuration, debugging, gRPC and docs endpoints](#s7-configuration-debugging-grpc-and-docs-endpoints)
  - [S7.1 Configuration properties and debugging [Q34, Q38]](#s71-configuration-properties-and-debugging-q34-q38)
  - [S7.2 Securing gRPC [Q34]](#s72-securing-grpc-q34)
  - [S7.3 [+] Securing the docs endpoint [Q33]](#s73--securing-the-docs-endpoint-q33)
  - [S7.4 Your Q34 checklist — where each sub-question is answered](#s74-your-q34-checklist--where-each-sub-question-is-answered)
  - [S7.5 Your security-tutorial notes — where each question is answered](#s75-your-security-tutorial-notes--where-each-question-is-answered)

---


## S1. The architecture: from the servlet filter chain to the SecurityContext


> **Your question [Q34]** was the longest in the whole set. It's broken into subsections below; the mapping is at the end of [§S7.4](#s74-your-q34-checklist--where-each-sub-question-is-answered).

### S1.1 The mental shift from FastAPI

Moving from FastAPI — where you **write** middleware and security exceptions yourself — to Spring Security means shifting from a **"do-it-yourself" model** to a **"configured engine" model**.

In Spring Boot you do not write security from scratch. You **declare beans that configure a pre-existing, highly robust interceptor network.**

```
FastAPI                                Spring Boot
──────────────────────────────         ──────────────────────────────
you write  get_current_user()          you configure  SecurityFilterChain
you write  the JWT decode              Spring provides JwtDecoder
you write  the 401 raise               Spring provides AuthenticationEntryPoint
you write  the password hash call      Spring provides PasswordEncoder
you write  the role check              Spring provides @PreAuthorize
you write  Depends(...) per route      Spring provides central path matchers
──────────────────────────────         ──────────────────────────────
Total control, total responsibility    Less code, but you must learn the seams
```

⚠️ **The cost of that trade is the thing that frustrates people:** when it doesn't work, you're debugging a framework's 15-filter pipeline rather than your own 20 lines. That's exactly why [§S7.1](#s71-configuration-properties-and-debugging-q34-q38) — turning on the security debug log — matters more here than anywhere else in this document.

**The dependency** (this alone changes your app's behaviour immediately):
```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-security</artifactId>
</dependency>
```

> **Your question [Q34]:** *"do we need to write the code for these security as well or are they available automatically? in spring using spring boot security will it secure almost all the endpoints?"*
>
> **Adding that one dependency secures EVERY endpoint immediately, with zero configuration.** You get:
> - all URLs requiring authentication,
> - a generated login form at `/login`,
> - HTTP Basic also enabled,
> - a single user `user` with a **random UUID password printed to the console at startup**,
> - CSRF protection on, session fixation protection on, and security headers (`X-Content-Type-Options`, `X-Frame-Options: DENY`, `Cache-Control`, HSTS) added to every response.
>
> ```
> Using generated security password: 8e557245-73e2-4286-969a-ff57fe326336
> ```
> This is the "secure by default" philosophy: the framework locks everything and makes **you** open it deliberately. FastAPI's default is the opposite — open until you add `Depends`.

> **Your question [Q34]:** *"does spring security use basic authorization header or Bearer token by default?"*
>
> **Neither, exactly — it enables BOTH form login and HTTP Basic by default.** A browser gets the login form; `curl` gets a `401` with `WWW-Authenticate: Basic`. **Bearer tokens are NOT on by default** — you opt in with `.oauth2ResourceServer(oauth2 -> oauth2.jwt(...))` or your own filter ([§S3.1](#s31-writing-a-jwt-filter-by-hand-q35)).

### S1.2 The architecture: the servlet filter chain [Q34]

In FastAPI, a request hits Uvicorn, passes through your ASGI middleware list, and reaches your router. In Spring Boot the architectural gatekeeper is the **servlet container** (embedded Tomcat), and Spring Security works by placing a **servlet filter chain** in front of your application.

*(Your diagram, preserved.)*
```
[ Incoming HTTP Request ] 
          │
          ▼
┌─────────────────────────────────┐
│ Servlet Container (Tomcat)      │
│  └─ DelegatingFilterProxy       │ ◄── Bridges Servlet world to Spring world
│       └─ FilterChainProxy       │
│            └─ SecurityFilterChain│ ◄── Iterates through ~15-20 Security Filters
└─────────────────────────────────┘
          │
      (If Auth Passes)
          ▼
┌─────────────────────────────────┐
│ DispatcherServlet (Spring MVC)  │ ◄── The central Front Controller
└─────────────────────────────────┘
          │
          ▼
┌─────────────────────────────────┐
│ Custom @RestController          │ ◄── Your business logic code
└─────────────────────────────────┘
```

💡 **Why `DelegatingFilterProxy` exists at all** — a detail that clears up a lot of confusion. The servlet container instantiates filters itself and knows nothing about Spring beans. `DelegatingFilterProxy` is a container-managed filter whose only job is to look up a **Spring bean** named `springSecurityFilterChain` and delegate to it. That's the bridge between the two worlds, and it's why your security filters can be `@Autowired` with repositories and services.

#### [+] The actual filters, in order

Turn on the debug log ([§S7.1](#s71-configuration-properties-and-debugging-q34-q38)) and Spring prints this list at startup. Knowing it is what separates "security is broken and I don't know why" from a two-minute diagnosis:

| # | Filter | Job |
|---|---|---|
| 1 | `DisableEncodeUrlFilter` | stops the session id being written into URLs |
| 2 | `WebAsyncManagerIntegrationFilter` | propagates the `SecurityContext` to async threads |
| 3 | `SecurityContextHolderFilter` | **loads** the `SecurityContext` (from the session) at the start, clears it at the end |
| 4 | `HeaderWriterFilter` | adds the security response headers |
| 5 | `CorsFilter` | ⚠️ CORS runs **here**, before authentication |
| 6 | `CsrfFilter` | validates the CSRF token ([§S6.1](#s61-csrf-q34)) |
| 7 | `LogoutFilter` | handles `POST /logout` |
| 8 | **`UsernamePasswordAuthenticationFilter`** | processes the form login `POST /login` — ⚠️ **the landmark you position your own filter against** |
| 9 | `DefaultLoginPageGeneratingFilter` | renders the built-in login page |
| 10 | `BasicAuthenticationFilter` | reads `Authorization: Basic …` |
| 11 | `RequestCacheAwareFilter` | replays the request you were going to before being bounced to login |
| 12 | `SecurityContextHolderAwareRequestFilter` | makes `request.isUserInRole()` work |
| 13 | `AnonymousAuthenticationFilter` | gives unauthenticated requests an `anonymousUser` principal |
| 14 | `SessionManagementFilter` | session fixation, concurrency control |
| 15 | **`ExceptionTranslationFilter`** | turns `AccessDeniedException` → **403** and `AuthenticationException` → **401** |
| 16 | **`AuthorizationFilter`** | **the actual `authorizeHttpRequests` decision** — the last one |

🔖 **Versions:** this is the Security 6/7 list. On Boot 2.7 (Security 5.7) you'll see `SecurityContextPersistenceFilter` instead of `SecurityContextHolderFilter` ([§S1.4](#s14-securitycontextholderfilter--remembering-the-user-between-requests)), and `FilterSecurityInterceptor` instead of `AuthorizationFilter` when the config uses `authorizeRequests()` ([§S4.1](#s41-the-authorization-architecture-authorizationfilter--authorizationmanager)). The "401" in row 15 is the API default; with form login the entry point **redirects to `/login`** instead.

💡 **Two insights that pay off immediately:**
- **Authorization is the LAST filter**, so by the time it runs, authentication has already happened (or the request is anonymous). A 403 means *"I know who you are, you're not allowed"*; a 401 means *"I don't know who you are"*.
- **`ExceptionTranslationFilter` sits just before it**, which is why authorization failures come back as clean HTTP codes and not stack traces.

#### Pre-processing and post-processing [Q34]

> **Your question:** *"how does spring servlet use pre-process and post-process on each request? can spring servlet filter out the request based on the filter logic?"*

Servlet filters use the **wrapper pattern**. Every filter implements `doFilter(request, response, filterChain)`:

```java
public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) {
    // ── PRE-PROCESSING ────────────────────────────────────
    //   inspect the request before it goes further
    if (!isValid(req)) {
        ((HttpServletResponse) res).setStatus(401);
        return;                        // ⚠️ SHORT-CIRCUIT: chain.doFilter is never called,
    }                                  //    so the controller is never reached

    chain.doFilter(req, res);          // ── hand control DOWN the chain ──

    // ── POST-PROCESSING ───────────────────────────────────
    //   runs on the way back UP, after the controller returned
    res.setHeader("X-Response-Time", elapsed());
}
```
- **Pre-processing:** a filter inspects the request before passing it on (e.g. checking for an `Authorization` header). If validation fails it can **write a 401 directly and short-circuit** the chain so it never touches your controller. ✅ **Yes, filters can absolutely filter out requests.**
- **Post-processing:** if the filter calls `chain.doFilter(...)`, control moves down to the next filter and eventually the controller. When the controller finishes, execution flows **backwards up the chain**, letting filters mutate headers or log metrics before the socket flushes.

> **Your question [Q34]:** *"are these similar to interceptors in spring boot and middleware in python+fastapi or middleware in express?"*
>
> **Yes, exactly.** A servlet filter is functionally identical to an Express middleware `(req, res, next) => {}` or a FastAPI/Starlette middleware. `chain.doFilter()` **is** `next()`. Not calling it **is** ending the response early.
>
> | | Spring Filter | Express | FastAPI |
> |---|---|---|---|
> | Signature | `doFilter(req, res, chain)` | `(req, res, next)` | `async def m(request, call_next)` |
> | Continue | `chain.doFilter(req, res)` | `next()` | `await call_next(request)` |
> | Short-circuit | just return | `res.status(401).send()` | `return Response(status_code=401)` |
> | Order | `@Order` / explicit chain position | registration order | registration order (⚠️ reversed) |
>
> For Filter vs `HandlerInterceptor`, see the comparison in [§W4.6](03-spring-web.md#w46-the-filter-chain) — Spring Security is a **Filter**, which is why it runs before `DispatcherServlet` and can protect static resources and error pages too.



### S1.3 Your architecture notes, checked: `DelegatingFilterProxy` → `FilterChainProxy` → `SecurityFilterChain` → filters

> **Your notes (from the official architecture page):** *"When we added spring-boot-starter-security, a new filter got added named SecurityFilterChain… Servlet API lifecycle can't access the Spring application context… DelegatingFilterProxy looks up the BeanFilter and invokes it (does the name BeanFilter suggest a bean created for a Spring servlet filter?)… FilterChainProxy (a BeanFilter?) delegates to many filters (BeanFilters?) through SecurityFilterChain… SecurityFilterChain contains several filters which are beans (are they also BeanFilters?)… So in a nutshell Spring Filter has a SecurityFilterChain."*

Your picture is right. Here are the four layers with the exact names:

```
Servlet container (Tomcat) filter chain — knows NOTHING about Spring beans
 ├─ CharacterEncodingFilter, …                 (ordinary servlet filters)
 ├─ DelegatingFilterProxy  "springSecurityFilterChain"   ← ONE container filter, the bridge
 │     │  looks up the bean named springSecurityFilterChain and calls it
 │     ▼
 │   FilterChainProxy   (a Spring bean that IS a Filter)
 │     │  picks the FIRST SecurityFilterChain whose matcher matches the request
 │     ▼
 │   SecurityFilterChain #1 (/api/**)    SecurityFilterChain #2 (everything else)
 │     ├─ SecurityContextHolderFilter      ├─ …
 │     ├─ CsrfFilter                       │
 │     ├─ BasicAuthenticationFilter / your JwtFilter
 │     ├─ ExceptionTranslationFilter
 │     └─ AuthorizationFilter
 └─ DispatcherServlet  → your @RestController
```

| Your term | Correct term | Notes |
|---|---|---|
| "a new filter named SecurityFilterChain" in the servlet chain | **`DelegatingFilterProxy`**, registered **under the name** `springSecurityFilterChain` | `SecurityFilterChain` is not itself registered with Tomcat. It is an *interface* (a matcher plus a list of filters) held inside `FilterChainProxy`. Boot registers the proxy for you (`DelegatingFilterProxyRegistrationBean`). |
| "BeanFilter" | ✅ **"Bean Filter" is the docs' own diagram label**: *"`DelegatingFilterProxy` looks up **Bean Filter0** from the `ApplicationContext` and then invokes Bean Filter0."* | There is **no class** called `BeanFilter`. It just means "a Spring bean that implements `jakarta.servlet.Filter`". |
| "FilterChainProxy (a BeanFilter?)" | ✅ **Yes.** It is *the* Bean Filter that `DelegatingFilterProxy` delegates to. | Docs: *"FilterChainProxy is a special Filter provided by Spring Security that allows delegating to many Filter instances through SecurityFilterChain."* |
| "the filters inside SecurityFilterChain are beans (BeanFilters?)" | ⚠️ **Partly.** Docs: *"The Security Filters in SecurityFilterChain are typically Beans, but they are registered with FilterChainProxy instead of DelegatingFilterProxy."* | In practice the **built-in** filters (`BasicAuthenticationFilter`, `CsrfFilter`, …) are created by `HttpSecurity` configurers with `new` and post-processed by Spring. They are *not* named beans you can look up. **Your own** filter (e.g. a `@Component JwtFilter`) is a real bean. |

📌 **Correction to the nesting sentence.** "Spring Filter has a SecurityFilterChain" is close. Precisely: *the servlet chain has **one** `DelegatingFilterProxy` → which delegates to **one** `FilterChainProxy` bean → which holds **one or more** `SecurityFilterChain`s → each holding an ordered list of security filters.* Only the **first matching** chain runs for a request.

**Why the extra `FilterChainProxy` layer, rather than registering every security filter with Tomcat?** The docs give three reasons:
1. One debug entry point.
2. Mandatory housekeeping: it **clears the `SecurityContext`** after each request to avoid leaks, and applies the `HttpFirewall`.
3. Tomcat can choose filters by **URL only**, while `FilterChainProxy` can choose a chain by **anything in the request** (`RequestMatcher`).

> 📌 **Correction — what the starter turns on.** Your note says adding the starter adds "FormBasis security". It adds **both form login and HTTP Basic**, with *every* request requiring authentication. Boot's default chain, verified in Boot source:
> - Boot 2.7 version: `http.authorizeRequests().anyRequest().authenticated(); http.formLogin(); http.httpBasic();`
> - Boot 3/4 version: the same with `authorizeHttpRequests`.
>
> The generated password is logged as `Using generated security password: …`, with username `user`.

🔗 The servlet filter chain itself (what Tomcat does before Spring) is in [§W4](03-spring-web.md#w4-rest-controller--the-complete-unabstracted-request-lifecycle-q). Filters vs `HandlerInterceptor` is in [§W5](03-spring-web.md#w5-filters-vs-handlerinterceptors).

### S1.4 `SecurityContextHolderFilter` — remembering the user between requests

> **Your note:** *"there is one more filter springContextHolderFilter, which stores the authenticated request so for requests of the same session we don't need to authenticate again and again."*

The name is **`SecurityContextHolderFilter`** (Security 6+). It replaced `SecurityContextPersistenceFilter` (Security 5.x, and so Boot 2.7). Your idea is right, with one important refinement about **who saves**:

```
Request 1 (login)                               Request 2 (same session)
──────────────────                              ────────────────────────
SecurityContextHolderFilter: load → empty        SecurityContextHolderFilter: LOAD context
UsernamePasswordAuthenticationFilter:              from HttpSession (SecurityContextRepository)
  authenticate → success                          → SecurityContextHolder now has the user
  → SecurityContextHolder.setContext(...)         Auth filters see "already authenticated"
  → securityContextRepository.saveContext(...)    AuthorizationFilter → allowed → controller
     (the HttpSession now holds it)               No DB / password check again ✅
end of request: holder cleared (thread reused)   end of request: holder cleared
```

| | Security 5.x (Boot 2.7) `SecurityContextPersistenceFilter` | Security 6/7 `SecurityContextHolderFilter` |
|---|---|---|
| Loads context from session at start | ✅ | ✅ |
| Saves context at end of request automatically | ✅ (implicitly) | ❌ **only loads.** The authentication mechanism must call `SecurityContextRepository.saveContext(...)` explicitly |

⚠️ **Why this bites:** if you write a custom login endpoint on Security 6+ and only call `SecurityContextHolder.setContext(...)`, the user is logged in **for that one request** and anonymous on the next. Either save explicitly with `HttpSessionSecurityContextRepository.saveContext(context, request, response)`, or go stateless with JWT ([§S3](#s3-stateless-authentication-jwt-and-refresh-tokens)), where nothing is saved by design. The docs: *"if you need to save the SecurityContext so that it can be automatically set on future requests, `SecurityContextRepository#saveContext` must be explicitly invoked."*

🔗 How the "holder" is really a `ThreadLocal`, and why it must be cleared on pooled threads: [§J6](01-java.md#j6-concurrency-and-multithreading-q2q9) and [§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder).

### S1.5 When it goes wrong: wrong passwords and `ExceptionTranslationFilter`

> **Your question:** *"what happens when the user entered a wrong password, how to handle the exception? ExceptionTranslationFilter catches all exception failures — is this only for AuthenticationFailure, or all exceptions of our Spring Boot application, or only Spring Security exceptions? I think ControllerAdvice is based on AOP and exists inside Spring MVC. Does ExceptionTranslationFilter translate other exceptions as well? To what does it translate them?"*

**Two different failure paths. Don't mix them up.**

**Path 1: a wrong password at login.** This is handled by the *authentication filter itself*, not by `ExceptionTranslationFilter`:

```
POST /login (bad password)
  → UsernamePasswordAuthenticationFilter
     → AuthenticationManager → DaoAuthenticationProvider
        → passwordEncoder.matches(raw, hash) == false
        → throws BadCredentialsException  (an AuthenticationException)
  ← caught right there by the filter:
       SecurityContextHolder cleared
       AuthenticationFailureHandler invoked  → form login: redirect /login?error
  (BasicAuthenticationFilter instead calls its AuthenticationEntryPoint → 401 + WWW-Authenticate)
```

**Path 2: an unauthenticated or forbidden request to a protected URL.** This one goes through `ExceptionTranslationFilter`. It wraps the rest of the chain in a try/catch. This is the docs' pseudocode:

```java
try {
    filterChain.doFilter(request, response);              // AuthorizationFilter, controller, method security…
} catch (AccessDeniedException | AuthenticationException ex) {
    if (!authenticated || ex instanceof AuthenticationException) {
        startAuthentication();   // save request in RequestCache, call AuthenticationEntryPoint → 401 / redirect to login
    } else {
        accessDenied();          // AccessDeniedHandler → 403
    }
}
```

| Question | Answer |
|---|---|
| Does it catch **all** exceptions in the app? | ❌ **No.** Only `AuthenticationException` and `AccessDeniedException` (and their subclasses). Everything else (`NullPointerException`, your `OrderNotFoundException`) passes straight through it. |
| What does it translate them into? | HTTP responses: **`AuthenticationEntryPoint`** (default 401 or redirect to `/login`) and **`AccessDeniedHandler`** (default 403). |
| ⚠️ The subtle rule | An **anonymous** user who hits `AccessDeniedException` gets *Start Authentication* (401 / login), **not** 403, because of `!authenticated` above. |
| Where does it sit? | After the authentication filters, just before `AuthorizationFilter`, so it catches what `AuthorizationFilter` throws. It also catches `AccessDeniedException` from `@PreAuthorize` on controllers *if* nothing in MVC handled it first. |

📌 **Correction — `@ControllerAdvice` is not AOP.** It has nothing to do with proxies or aspects. `DispatcherServlet` calls its `HandlerExceptionResolver`s after a handler throws, and `ExceptionHandlerExceptionResolver` looks up the matching `@ExceptionHandler` method in your `@ControllerAdvice` beans. Your other instinct is correct: it lives **inside Spring MVC**, so it can only see exceptions thrown *inside* `DispatcherServlet`. A security filter's 401 happens before MVC exists for that request. That is why filter-level errors are customised via `http.exceptionHandling(e -> e.authenticationEntryPoint(...).accessDeniedHandler(...))`, not `@ControllerAdvice`.

⚠️ **The overlap trap.** `@PreAuthorize` on a controller throws *inside* MVC. If you add `@ExceptionHandler(AccessDeniedException.class)` to your advice, MVC handles it and `ExceptionTranslationFilter` **never sees it**, so an anonymous caller gets your 403 instead of the correct 401. Either don't handle `AccessDeniedException` in advice, or check authentication in the handler yourself.

🔗 The MVC exception path and `@RestControllerAdvice`: [§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling).

## S2. Authentication: who are you?

### S2.1 `@EnableWebSecurity` and the `SecurityFilterChain` bean [Q35]

> **Your questions [Q35]:** *"what does `@EnableWebSecurity` do? what will happen if we don't use this annotation? is `SecurityFilterChain` a special type of bean class which is pre-recognized by spring boot?"*

**`@EnableWebSecurity`** is the master switch. It tells Spring to find your configuration classes, build the global interceptor engine, and bind it to the servlet container's pipeline.

**What happens without it:**
- **In plain Spring MVC:** web security turns off completely — an open network, zero endpoint protection, no role checks, no header controls.
- **In Spring Boot:** ✅ **nothing changes.** Boot's auto-configuration (`SecurityAutoConfiguration` → `SpringBootWebSecurityConfiguration`) detects `spring-boot-starter-security` on the classpath and behaves **as if `@EnableWebSecurity` were written for you**.

🔖 **Since Security 6.0, `@EnableWebSecurity` no longer carries `@Configuration`** (it did in 5.x / Boot 2.7), so always put `@Configuration` next to it, as the examples here do. Details in [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database).

💡 **So it's optional in Boot — but keep writing it.** It signals architectural intent, it keeps your config working if you ever move off full Boot auto-configuration, and it makes the class findable by anyone grepping for security config.

**Is `SecurityFilterChain` a special bean?** **Yes — it is a core architectural interface the engine looks for by type.** At startup `FilterChainProxy` scans the application context for **any bean of type `SecurityFilterChain`**. If it finds one, it **discards the default "lock everything down with a generated password" configuration** and installs your chain instead. Mechanically, Boot's default chain is `@ConditionalOnDefaultWebSecurity`, which is false the moment your bean exists.

⚠️ **The single biggest migration trap in all of Spring:** **`WebSecurityConfigurerAdapter` was deprecated in Spring Security 5.7 and REMOVED in 6.0.** The overwhelming majority of tutorials, Stack Overflow answers and books still use it:
```java
// ❌ DEAD — does not exist in Spring Security 6 / Boot 3. Will not compile.
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    @Override protected void configure(HttpSecurity http) { ... }
}

// ✅ The component-based replacement
@Configuration
@EnableWebSecurity
public class SecurityConfig {
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception { ... }
}
```

💡 **[+] Multiple chains for multiple API surfaces** — the direct answer to *"in FastAPI I divided our API endpoints into authenticated and public, can we do that here?"* at the highest level. Chains are tried **in `@Order`**, and the **first one whose `securityMatcher` matches wins**:
```java
@Bean @Order(1)
SecurityFilterChain apiChain(HttpSecurity http) throws Exception {
    return http.securityMatcher("/api/**")            // ← only /api/**
        .csrf(csrf -> csrf.disable())
        .sessionManagement(s -> s.sessionCreationPolicy(STATELESS))
        .authorizeHttpRequests(a -> a.anyRequest().authenticated())
        .oauth2ResourceServer(o -> o.jwt(withDefaults()))
        .build();
}

@Bean @Order(2)
SecurityFilterChain webChain(HttpSecurity http) throws Exception {
    return http                                        // ← everything else
        .authorizeHttpRequests(a -> a.requestMatchers("/", "/css/**").permitAll()
                                    .anyRequest().authenticated())
        .formLogin(withDefaults())                     // sessions + CSRF for the HTML side
        .build();
}
```
✅ This is the correct way to run a **stateless JWT API and a session-based HTML admin UI in the same application** — a very common real requirement that people incorrectly try to solve inside one chain.

### S2.2 The authentication engine: `AuthenticationManager` → `ProviderManager` → `AuthenticationProvider` → `UserDetailsService` + `PasswordEncoder`

> **Your notes, summarised:** *"There are several ways of authentication: (a) Spring-generated username & password (UsernamePasswordAuthenticationFilter), (b) database/memory, (c) OAuth 2.0, (d) LDAP. For each Spring provides a dedicated AuthenticationProvider: DaoAuthenticationProvider, OAuthsLoginAuthenticationProvider, LDAPAuthenticationProvider. How does Spring know which provider to use? The Authentication Manager — ProviderManager — loops through all providers, checks supports() for this filter, and returns the first match… How does the provider know which username has what password? UserDetailsService… PasswordEncoder is part of the provider… After success the provider returns an Authentication object, stored in a SecurityContext (also known as the Principal object), accessed via SecurityContextHolder.getContext()."*

The architecture is right. Here is the complete flow, then the corrections.

```
 Client ──POST /login (or Authorization: Basic …)──▶ Tomcat ──▶ DelegatingFilterProxy ──▶ FilterChainProxy
                                                                                            │
 ┌──────────────────────────────────────────────────────────────────────────────────────────┘
 ▼
 Authentication FILTER  (UsernamePasswordAuthenticationFilter / BasicAuthenticationFilter / your JwtFilter)
   1. extract credentials from the request
   2. wrap them:  new UsernamePasswordAuthenticationToken("alice", "secret")   ← unauthenticated token
   3. authenticationManager.authenticate(token)
 ▼
 AuthenticationManager (interface)  ──implemented by──▶  ProviderManager
   for each provider in providers:
       if (!provider.supports(token.getClass())) continue          ← matched on the TOKEN TYPE
       result = provider.authenticate(token)
       if (result != null) break                                    ← null = "not mine, ask the next"
       (AuthenticationException → remember it, try the next one;
        account locked/disabled → stop immediately)
   nothing worked? → ask the parent AuthenticationManager, else throw
 ▼
 DaoAuthenticationProvider  (supports UsernamePasswordAuthenticationToken)
   4. userDetailsService.loadUserByUsername("alice")  ──▶ your DB / memory / Mongo
   5. check account flags (enabled, locked, expired…)
   6. passwordEncoder.matches("secret", user.getPassword())   ← never "decrypt"
   7. return new UsernamePasswordAuthenticationToken(userDetails, null, authorities) ← AUTHENTICATED
 ▼
 back in the filter:
   8. context = SecurityContextHolder.createEmptyContext(); context.setAuthentication(result)
   9. SecurityContextHolder.setContext(context)           ← ThreadLocal, for the rest of this request
  10. (session-based) securityContextRepository.saveContext(...)  ← for the NEXT request (§S1.4)
 ▼
 … AuthorizationFilter (§S4.1) … DispatcherServlet … your controller
     (anywhere: SecurityContextHolder.getContext().getAuthentication())
```

**Corrections and precise names:**

| Your note | Precise version |
|---|---|
| `OAuthsLoginAuthenticationProvider`, `LDAPAuthenticationProvider` | **`OAuth2LoginAuthenticationProvider`** (plus `OidcAuthorizationCodeAuthenticationProvider` when the `openid` scope is used, as with Google) and **`LdapAuthenticationProvider`** |
| "the Spring-generated username & password **is** UsernamePasswordAuthenticationFilter" | The **filter** reads a form login; the generated user comes from Boot's `InMemoryUserDetailsManager`. Form login and HTTP Basic both end up in `DaoAuthenticationProvider`. |
| "supports() checks if the provider supports **this filter**" | 📌 `supports(Class<?> authentication)` receives the **token class** (e.g. `UsernamePasswordAuthenticationToken.class`), not the filter. The filter decides *which token type* to build, and that indirectly picks the provider. |
| "returns the **first** match" | Not quite. It tries **every** provider that `supports()` the token until one returns a **non-null** `Authentication` (verified in `ProviderManager.authenticate` source). A provider that supports the type can still return `null` to pass. For example, `OAuth2LoginAuthenticationProvider` returns `null` for OIDC requests, so the OIDC provider handles them. A thrown `AuthenticationException` is remembered and the loop continues. `AccountStatusException` (locked/disabled) stops the loop at once. If none succeed, the optional **parent** manager is asked, then `ProviderNotFoundException` / the last exception is thrown. |
| "Calls Authentication Provider's authenticate method (it has an implementation i.e. ProviderManager)" | Swap the names: the filter calls the **`AuthenticationManager`**, whose implementation is **`ProviderManager`**, which calls the **`AuthenticationProvider`s**. |
| "InMemoryUserDetailsManager, JDBCUserDetailsManager are interfaces of UserDetailsService" | They are **classes**. `UserDetailsService` is the interface (one method, `loadUserByUsername`). `UserDetailsManager` extends it with create/update/delete. `InMemoryUserDetailsManager` and `JdbcUserDetailsManager` implement `UserDetailsManager`. |
| "PasswordEncoder is a part of the Authentication Provider" | ✅ Yes: `DaoAuthenticationProvider` *holds* a `PasswordEncoder`. If you set none, it uses `PasswordEncoderFactories.createDelegatingPasswordEncoder()` (the `{bcrypt}` prefix style, [§S2.6](#s26-passwords-hashing-salting-and-the-bcrypt-migration-q34-q37-q14)). |
| "SecurityContext stores the Authentication object (also known as Principal object)" | Three distinct things. **`SecurityContext`** holds one **`Authentication`**. The `Authentication` has a **principal** (usually your `UserDetails`), **credentials** (password, erased after login) and **authorities**. Why the name confusion: `Authentication` *extends* `java.security.Principal`, so technically it *is a* `Principal`, while `getPrincipal()` returns the user object inside it. |

> **Your question:** *"Do we have anything if we wanted to store user details in any NoSQL db? Does Spring Boot have any built-in implementation other than in-memory or SQL?"*
>
> **No built-in NoSQL implementation.** You write a small custom `UserDetailsService` over your Spring Data Mongo/Redis repository. The Mongo example is in [§S2.4](#s24-where-users-come-from-the-four-strategies-q34-q36).

> **Your question:** *"Does PasswordEncoder only encrypt the password, and at authentication time encrypt the plain password and compare it with the stored one, or does Spring decrypt the stored password? I think decryption is not possible… so we may encode at storing time and decode at authentication time?"*
>
> Your first instinct is right and the last guess is wrong: **nothing is ever decoded or decrypted.** bcrypt/argon2/pbkdf2 are one-way hashes. But it is also *not* "hash the input again and string-compare", because bcrypt salts randomly: `encode("pw")` twice gives two different strings. Instead `matches(raw, stored)` **reads the salt and cost out of the stored hash**, hashes `raw` with that same salt, and compares the results in constant time.
>
> | Method | When | What |
> |---|---|---|
> | `encode(raw)` | once, at signup / password change | random salt + hash → store the result |
> | `matches(raw, stored)` | every login (`DaoAuthenticationProvider` calls it) | re-hash with the *stored* salt, compare |
> | `upgradeEncoding(stored)` | after a successful login | "is this hash outdated?" → lazy re-hash ([§S2.6](#s26-passwords-hashing-salting-and-the-bcrypt-migration-q34-q37-q14)) |

> **Your closing note:** *"For any authentication flow the architecture remains the same but we need to tweak the default places."*
>
> ✅ Exactly. Every mechanism fills the same slots: **a filter** builds a token, **a provider** verifies it, **a `SecurityContext`** holds the result. Basic auth, JWT, OAuth2 and LDAP differ only in *which* filter and *which* provider. The next section swaps them one by one.

### S2.3 Walkthrough: replacing the defaults with HTTP Basic + users from your database

> **Your note:** *"To implement custom authentication we need to change the whole architecture so Spring doesn't pick the default: the FilterChainProxy (BasicAuthenticationFilter instead of UsernamePasswordAuthenticationFilter), the AuthenticationManager & Provider, the UserDetailsService, the PasswordEncoder."*

✅ Those are exactly the four slots. In practice you rarely replace all four. Declaring a `UserDetailsService` bean and a `PasswordEncoder` bean is enough, because Spring Security wires a `DaoAuthenticationProvider` from them automatically (shown in step 5).

#### Step 1 — the config class and the minimum chain

```java
@Configuration          // ✅ needed: since Security 6.0 @EnableWebSecurity no longer includes it
@EnableWebSecurity      // optional in Boot; keep it for clarity
public class SecurityConfig {

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .csrf(AbstractHttpConfigurer::disable)                       // = csrf -> csrf.disable()
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/login", "/signup", "/api/auth/**").permitAll()
                .anyRequest().authenticated())
            .httpBasic(Customizer.withDefaults());
        return http.build();
    }
}
```

| Your note / question | Answer |
|---|---|
| "@EnableWebSecurity tells Spring we're tweaking web security rather than using the default UsernamePasswordAuthentication" | 📌 Not quite. In Boot, **declaring any `SecurityFilterChain` bean** is what makes the default chain back off (`@ConditionalOnDefaultWebSecurity`). `@EnableWebSecurity` just switches the engine on, and Boot already does that. |
| "Does `@EnableWebSecurity` include `@Configuration`?" | **Security 5.x (Boot 2.7): yes. Security 6+/7: no.** It was removed in 6.0; verified by diffing the annotation source between `5.8.x` and `main`. So on Boot 3/4 keep `@Configuration` on the class. |
| "httpBasic(withDefaults()) — its configurer creates a new BasicAuthenticationFilter and replaces the default filter" | ✅ `HttpBasicConfigurer.configure()` does `new BasicAuthenticationFilter(authenticationManager, entryPoint)` and adds it to the chain. 📌 Small refinement: nothing is *replaced*. Your chain simply never calls `.formLogin()`, so `UsernamePasswordAuthenticationFilter` is never added. |
| `spring.security.user.name=testuser` / `spring.security.user.password=testpassword` | ✅ Replaces the generated user/password (Boot's `InMemoryUserDetailsManager`). ⚠️ It **stops applying** once you declare your own `UserDetailsService` bean, because Boot's in-memory user backs off. |
| "Without `authorizeHttpRequests` all requests pass?" | ✅ **Yes.** No authorization rules means no `AuthorizationFilter`, so nothing is ever rejected, even with `httpBasic` on. Credentials are *read* if sent, but never *required*. |
| `requestMatchers({"/login","/signup"})` | It's varargs: `requestMatchers("/login", "/signup")`. **Order matters: first match wins**, so specific rules go first and `anyRequest()` goes last ([§S4.2](#s42-declarative-security--the-central-configuration-q34)). |
| `http.csrf(csrf -> csrf.disable())` vs `csrf(AbstractHttpConfigurer::disable)` | Identical. The second is a method reference to the same thing. ⚠️ Safe only if no cookie carries the credential ([§S6.1](#s61-csrf-q34)). |
| 🔖 Boot 2.7 / Security 5.7 | Same lambda DSL works, but the older names are common there: `authorizeRequests()` / `antMatchers()` / `mvcMatchers()`. Verified in source: `requestMatchers(String…)` arrived in **5.8**; `antMatchers`/`mvcMatchers` were **removed in 6.0**; `authorizeRequests()` was deprecated in 6 and **removed in 7**. |

#### Step 2 — the `User` entity

```java
@Entity
@Table(name = "app_users")                 // ⚠️ "user" is a reserved word in PostgreSQL/H2
public class User implements UserDetails {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(unique = true, nullable = false) private String username;
    @Column(nullable = false)                private String password;   // the bcrypt HASH
    private String role;                                                // e.g. "ROLE_ADMIN"

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return List.of(new SimpleGrantedAuthority(role));   // what AuthorizationManager checks later
    }
    @Override public String getPassword() { return password; }
    @Override public String getUsername() { return username; }
    // isAccountNonExpired/isAccountNonLocked/isCredentialsNonExpired/isEnabled:
    // since Security 6.3 these are DEFAULT methods returning true, so you may omit them
    // (or write UserDetails.super.isEnabled() as in your notes). On Security <= 6.2
    // (incl. 5.x / Boot 2.7) they are abstract and you MUST implement them.
    // getters/setters …
}
```

- **`GenerationType.IDENTITY` and the other strategies** (`SEQUENCE`, `TABLE`, `AUTO`, `UUID`) are compared in [§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-). In short: `IDENTITY` uses the DB's auto-increment column, which is simplest for MySQL/Postgres. Its cost is that Hibernate can't batch inserts.
- **`UserDetails.super.isEnabled()`** works only on **Security 6.3+**, where those four methods became `default` methods returning `true` (verified in source: abstract in 6.2, default in 6.3). On Boot 2.7 it won't compile; implement them. ⚠️ Remember from [§S2.5](#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39): hardcoding `true` means your "ban user" flag does nothing. Also prefer a separate `UserPrincipal` over making the entity implement `UserDetails`.

#### Step 3 — the repository

```java
public interface UserDetailsRepository extends JpaRepository<User, Long> {
    Optional<User> findByUsername(String username);   // derived from the FIELD name "username"
}
```

> **Your question:** *"will this repository work even if we don't mark it @Repository? Is @Repository optional or mandatory?"*
>
> **Optional** on a Spring Data interface. Spring Data finds every interface extending `Repository`/`JpaRepository`, generates a proxy implementation and registers it as a bean, and that proxy already translates persistence exceptions. `@Repository` matters on your **own hand-written DAO classes**. Details: [§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-).
>
> ⚠️ Your note writes `findByUserName`. A derived query must match the **field name** exactly, so with a field `username` you must write `findByUsername`. `findByUserName` fails at startup with *"No property 'userName' found"*.

#### Step 4 — the custom `UserDetailsService`

```java
@Service
public class CustomUserDetailsService implements UserDetailsService {

    private final UserDetailsRepository repo;
    public CustomUserDetailsService(UserDetailsRepository repo) { this.repo = repo; }   // constructor injection

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return repo.findByUsername(username)                     // ✅ you must RETURN it
                .orElseThrow(() -> new UsernameNotFoundException("User not found: " + username));
    }
}
```
⚠️ Fixes to the note's version:
- It forgot `return`.
- It threw a custom `NoUserFoundException`. The contract is **`UsernameNotFoundException`**. By default `DaoAuthenticationProvider` converts it into `BadCredentialsException`, so attackers can't tell "no such user" from "wrong password" (`hideUserNotFoundExceptions`).

#### Step 5 — wiring the `AuthenticationManager`, provider and encoder

> **Your questions:** *"Why didn't we @Autowired the CustomUserDetailsService into the config — because it's a @Configuration not a @Component, or another reason? Can we pass a bean as a @Bean method parameter? Will userDetailsService be a function since we passed a bean?"*

```java
@Configuration
public class SecurityBeans {

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    // OPTIONAL — only if you need the AuthenticationManager yourself (e.g. a /login endpoint, §S3.2)
    @Bean
    public AuthenticationManager authenticationManager(UserDetailsService uds, PasswordEncoder encoder) {
        DaoAuthenticationProvider provider = new DaoAuthenticationProvider(uds);   // Security 7: constructor arg
        provider.setPasswordEncoder(encoder);
        return new ProviderManager(provider);
    }
}
```

| Question | Answer |
|---|---|
| Why not `@Bean public UserDetailsService userDetailsService() { return new CustomUserDetailsService(); }`? | ⚠️ **Don't write it.** `CustomUserDetailsService` is already a bean because of `@Service`. A second `@Bean` gives **two** `UserDetailsService` beans and `NoUniqueBeanDefinitionException` wherever one is injected by type. (`new CustomUserDetailsService()` also wouldn't compile once it has a constructor dependency.) It has nothing to do with `@Configuration` vs `@Component`: you *can* `@Autowired` into a `@Configuration`. You just don't need to. |
| Can a `@Bean` method take beans as parameters? | ✅ **Yes, and it's the preferred style.** Spring resolves each parameter **by type** from the container before calling the method, exactly like constructor injection ([§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13)). This works in any `@Bean` method, not just this one. |
| "Will `userDetailsService` be a function?" | No. It is the **actual bean instance** (your `CustomUserDetailsService` object, possibly a proxy). Passing it to the provider is ordinary object passing. |
| `new DaoAuthenticationProvider()` + `setUserDetailsService(uds)` (your version) | 🔖 **Version-dependent.** That is the Security 5.x / early-6 API (Boot 2.7). In **Security 7 (Boot 4)** the only constructor is `DaoAuthenticationProvider(UserDetailsService)` and `setUserDetailsService` is gone (verified in the 7.x javadoc). `setPasswordEncoder` still exists. |
| Do I even need this bean? | **Often not.** If the context has exactly one `UserDetailsService` bean and a `PasswordEncoder` bean, Spring Security builds the `DaoAuthenticationProvider` for you. To obtain that auto-built manager (e.g. in a login controller), inject `AuthenticationConfiguration` and call `getAuthenticationManager()`, or expose it: `@Bean AuthenticationManager am(AuthenticationConfiguration c) throws Exception { return c.getAuthenticationManager(); }`. Write the manual version when you need several providers or custom settings. |

#### Step 6 — seeding an admin at startup with `CommandLineRunner`

```java
@Configuration
public class AdminUserInitializer {

    @Bean
    public CommandLineRunner createAdminUser(UserDetailsRepository repo, PasswordEncoder encoder) {
        return args -> {                                               // CommandLineRunner is a functional interface
            if (repo.findByUsername("admin").isEmpty()) {
                User user = new User();
                user.setUsername("admin");
                user.setPassword(encoder.encode("admin123"));          // ✅ store the HASH
                user.setRole("ROLE_ADMIN");                            // ✅ ROLE_ prefix so hasRole("ADMIN") works
                repo.save(user);
            }
        };
    }
}
```

| Your question / note | Answer |
|---|---|
| "we encode while storing because at authentication time the manager will decode and decrypt using the same encoder" | 📌 **Correction:** it never decodes. It calls `matches(raw, storedHash)`, which re-hashes with the stored salt ([§S2.2](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder)). The part that matters is right: you must use **the same `PasswordEncoder` bean** for `encode` and `matches`. |
| What is `CommandLineRunner`, how and when to use it? | A one-method interface, `run(String... args)`. Boot calls every `CommandLineRunner` / `ApplicationRunner` bean **once, after the context is fully refreshed**. Use it for idempotent startup work: seeding dev data, warming a cache, a sanity check. Full lifecycle position: [§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13). |
| "Will this admin get added since we marked it @Bean, or do we need something in the main class?" | ✅ **It runs automatically.** Being a bean of type `CommandLineRunner` is enough; nothing goes in `main()`. Your version put `@Bean` inside a `@Component` class. That works ("lite mode"), but the convention is `@Configuration` (as above), or a `@Component` that `implements CommandLineRunner` directly. |
| ⚠️ Production notes | The embedded **web server is already listening** when runners execute. Boot publishes readiness `ACCEPTING_TRAFFIC` only after runners finish, verified in `SpringApplication.run`: `started → callRunners → ready`. So Kubernetes won't route traffic yet, but a direct request could arrive mid-seed. Never hardcode a real admin password: read it from config/secrets, or use Flyway/Liquibase for seed data. |

#### Step 7 — the signup (and "login") endpoint

> **Your request:** *"in the ideal case we will have a login flow to store the user credentials in the api (also give me the login api implementation details)."*

With **HTTP Basic there is no login endpoint**. The client sends `Authorization: Basic base64(user:pass)` on **every** request, and `BasicAuthenticationFilter` verifies it each time (a DB lookup + bcrypt per request, which is why Basic is slow and why JWT exists, [§S3](#s3-stateless-authentication-jwt-and-refresh-tokens)). You do need **signup**:

```java
@RestController
@RequestMapping("/api/auth")
public class AuthController {

    private final UserDetailsRepository repo;
    private final PasswordEncoder encoder;

    public AuthController(UserDetailsRepository repo, PasswordEncoder encoder) {
        this.repo = repo; this.encoder = encoder;
    }

    @PostMapping("/signup")
    public ResponseEntity<String> signup(@Valid @RequestBody SignupRequest req) {
        if (repo.findByUsername(req.username()).isPresent()) {
            return ResponseEntity.status(HttpStatus.CONFLICT).body("Username is already taken");  // 409
        }
        User u = new User();
        u.setUsername(req.username());
        u.setPassword(encoder.encode(req.password()));   // ✅ hash before save
        u.setRole("ROLE_USER");                           // ⚠️ never take the role from the request body
        repo.save(u);
        return ResponseEntity.status(HttpStatus.CREATED).body("User registered");
    }
}

public record SignupRequest(@NotBlank String username, @NotBlank @Size(min = 8) String password) {}
```
- `/api/auth/signup` must be in `permitAll()`.
- ⚠️ The check-then-insert has a race: two simultaneous signups can both pass `isPresent()`. The `unique = true` constraint is the real guard, so catch `DataIntegrityViolationException` → 409.
- For a **login endpoint that returns a token**, see [§S3.2](#s32-the-complete-jwt-flow-login-endpoint-token-creation-and-the-filter).

### S2.4 Where users come from: the four strategies [Q34, Q36]

> **Your question:** *"what are the different techniques for finding username, passwords, roles (authentication and authorization) [e.g. in-memory, LDAP (what is this ldap), jdbc, custom/pluggable]?"*

Spring Security abstracts user lookup behind one interface, **`UserDetailsService`**, with a single method: `loadUserByUsername(String)`.

| Strategy | Class | Use |
|---|---|---|
| **In-memory** | `InMemoryUserDetailsManager` | users in a volatile `Map` in RAM. ✅ Excellent for local dev and integration tests; **useless for multi-instance production.** |
| **JDBC** | `JdbcUserDetailsManager` | standard DB tables using Spring's **predefined schema**. |
| **LDAP** | `LdapUserDetailsManager` | centralized corporate directories. |
| **Custom / pluggable** | ✅ **your own `UserDetailsService`** | **the standard choice for real applications** — [§S2.5](#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39). |

**What is LDAP?** **Lightweight Directory Access Protocol** — an industry-standard protocol for **centralized user management in large corporate networks**. Think of it as a specialized hierarchical database optimised for fast lookups of employee names, org structure and permissions. **Microsoft Active Directory** is the implementation you'll actually meet. The value is single sign-on: one corporate identity across every internal application, with joiners/leavers handled by IT rather than by each app.

```java
// In-memory — dev and tests
@Bean
public UserDetailsService inMemory(PasswordEncoder encoder) {
    UserDetails user = User.withUsername("alice")
            .password(encoder.encode("password")).roles("USER").build();
    return new InMemoryUserDetailsManager(user);
}
```

#### JDBC and the `DataSource` [Q36]

> **Your question:** *"`@Bean public UserDetailsManager userDetailsManager(DataSource dataSource)` — what is this DataSource? is this bean structure fixed or can we use it as per our convenience (like the method name)?"*

**What `DataSource` is:** a core JDBC API type — in practice a **managed database connection pool**, powered by **HikariCP** in Spring Boot. You never instantiate it. When you put connection settings in `application.properties`, Boot builds the pool and registers it as a global bean:
```properties
spring.datasource.url=jdbc:postgresql://localhost:5432/mydb
spring.datasource.username=app
spring.datasource.password=${DB_PASSWORD}
```
Declaring `DataSource dataSource` as a method parameter just asks the container to inject that pool.

**Is the method name mandatory?** **No — it is completely arbitrary.** Name it `myCustomSqlSecurityManager` if you like. **Spring resolves beans by TYPE, not by method name.** The auto-wiring engine scans for any bean implementing `UserDetailsService` / `UserDetailsManager`. *(The name only becomes significant when two beans share a type and you need `@Qualifier` — [§C2.11](02-spring-core.md#c211-resolving-ambiguity).)*

**⚠️ The rigid part is the SCHEMA, not the bean.** `JdbcUserDetailsManager` runs fixed SQL and **crashes if your tables don't match**:
```sql
CREATE TABLE users (
    username VARCHAR(50)  NOT NULL PRIMARY KEY,
    password VARCHAR(100) NOT NULL,
    enabled  BOOLEAN      NOT NULL
);

CREATE TABLE authorities (
    username  VARCHAR(50) NOT NULL,
    authority VARCHAR(50) NOT NULL,
    CONSTRAINT fk_authorities_users FOREIGN KEY(username) REFERENCES users(username)
);
```
```java
@Configuration
public class SqlSecurityConfiguration {
    @Bean
    // The method name 'sqlSecurityEngine' is up to you.
    public UserDetailsManager sqlSecurityEngine(DataSource dbConnectionPool) {
        return new JdbcUserDetailsManager(dbConnectionPool);
    }
}
```
If your tables are named differently (`tbl_app_users`), you can re-map the SQL:
```java
JdbcUserDetailsManager m = new JdbcUserDetailsManager(dataSource);
m.setUsersByUsernameQuery("select login_uid, pass_hash, active from tbl_app_users where login_uid = ?");
m.setAuthoritiesByUsernameQuery("select login_uid, role_name from tbl_app_roles where login_uid = ?");
return m;
```
⚠️ **The column *order* in those queries is fixed even though the names are free** — `username, password, enabled` and `username, authority`. Get the order wrong and you get a baffling type error, not a helpful message.

**You cannot use `JdbcUserDetailsManager` with NoSQL** — there is no `DataSource` and no SQL. Write a custom `UserDetailsService`:
```java
@Document(collection = "app_members")
public class MemberDocument {
    @Id private String id;
    private String loginName;      // custom field name
    private String securedSecret;  // custom field name (hashed password)
    private List<String> roles;    // ["ROLE_USER", "ROLE_ADMIN"]
}

public interface MemberRepository extends MongoRepository<MemberDocument, String> {
    Optional<MemberDocument> findByLoginName(String loginName);
}
```
```java
@Configuration
public class NoSqlSecurityConfiguration {
    @Bean
    public UserDetailsService noSqlSecurityEngine(MemberRepository memberRepository) {
        return username -> {                       // UserDetailsService is a @FunctionalInterface
            MemberDocument member = memberRepository.findByLoginName(username)
                .orElseThrow(() -> new UsernameNotFoundException("User not found"));

            return org.springframework.security.core.userdetails.User.builder()
                .username(member.getLoginName())
                .password(member.getSecuredSecret())
                .authorities(member.getRoles().toArray(new String[0]))
                .build();
        };
    }
}
```

> **Summary:** `JdbcUserDetailsManager` if you're SQL-driven and happy to adopt Spring's default tables. **A custom `UserDetailsService` for everything else** — NoSQL, or a pre-existing corporate schema.

### S2.5 Custom `UserDetailsService` — any schema, any database [Q36, Q38, Q39]

> **Your questions [Q38]:** *"what if our enterprise db name is different and its column names are different, or we have more columns than Spring Security mentions, or all our data is in the Users table only and we don't have an Authorities table? what are the custom methods which we should implement — `getUserByUserName`, `findAuthority/RolesByUserName`? where should we override these?"*

**You implement exactly ONE method: `loadUserByUsername(String username)`.**

⚠️ **There are no `getUserByUsername` or `findRolesByUsername` methods to override — those don't exist.** `UserDetailsService` has a single method. You query your database however you like (Spring Data JPA, MongoDB, even an external REST call) and package the result into a `UserDetails`.

**Does this work for NoSQL?** **Yes, 100%.** Because you fully override *how* the user is fetched, Spring Security no longer cares whether the data came from PostgreSQL, a MongoDB collection, or an external API.

> **Your question:** *"is it mandatory to override `UserDetailsManager` for this?"*
>
> **No, absolutely not.** `UserDetailsManager` is the **heavier** interface — it adds `createUser()`, `deleteUser()`, `changePassword()`, `userExists()`, for when you want the framework to manage the user lifecycle. **To authenticate logins you only need `UserDetailsService`.**

#### The two contracts, and why you override those methods [Q39]

> **Your question [Q39]:** *"why do we need to override these methods — `getAuthorities()`, `getPassword()`, `getUsername()`, `isAccountNonExpired()`…?"*

Because you chose to implement the **`UserDetails` interface directly on your entity.** In Java an interface is a **strict contract**: implementing it promises the compiler *"I provide a concrete implementation of every method in this contract."*

Spring Security knows **nothing** about your `Employee` class. It doesn't know you named the column `pass_hash` or `login_uid`. It is hardcoded to talk only to `UserDetails`. **By overriding these methods you are writing an adapter:**

| Method | What you're telling Spring |
|---|---|
| `getPassword()` | *"when you need the hash to verify a login, read my `passHash` field"* |
| `getUsername()` | *"the login identifier is my `loginUid` field"* |
| `getAuthorities()` | *"here are this user's permissions, as `GrantedAuthority` objects"* |
| `isEnabled()`, `isAccountNonLocked()`, `isAccountNonExpired()`, `isCredentialsNonExpired()` | account-state flags — Spring uses them to refuse login for banned/suspended/expired accounts. Returning `true` says *"treat every user as active and valid."* |

**And if you don't override them, the code simply won't compile.**

⚠️ **Those four booleans are a real security surface, not boilerplate.** Returning a hardcoded `true` for `isEnabled()` means **your "ban user" feature does nothing** — a banned user keeps logging in. Wire them to real columns the moment you have them:
```java
@Override public boolean isEnabled()           { return this.active; }
@Override public boolean isAccountNonLocked()  { return this.failedLoginCount < 5; }
@Override public boolean isAccountNonExpired() { return this.expiresAt == null || this.expiresAt.isAfter(Instant.now()); }
```

#### Blueprint A — one custom table, custom columns, extra columns

```java
import jakarta.persistence.*;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import java.util.Collection;
import java.util.List;

@Entity
@Table(name = "corporate_employees")            // custom table name
public class Employee implements UserDetails {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "emp_id")
    private Long id;

    @Column(name = "login_uid", unique = true, nullable = false)   // custom column name
    private String loginUid;

    @Column(name = "pass_hash", nullable = false)                  // custom column name
    private String passHash;

    private String email;                       // extra column, not in Spring's default schema

    @Column(name = "security_role")             // roles in the SAME table — no authorities table
    private String securityRole;                // e.g. "ROLE_ADMIN"

    // --- the UserDetails contract ---
    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return List.of(new SimpleGrantedAuthority(this.securityRole));
    }
    @Override public String  getPassword()              { return this.passHash; }
    @Override public String  getUsername()              { return this.loginUid; }
    @Override public boolean isAccountNonExpired()      { return true; }
    @Override public boolean isAccountNonLocked()       { return true; }
    @Override public boolean isCredentialsNonExpired()  { return true; }
    @Override public boolean isEnabled()                { return true; }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }
}
```
```java
public interface EmployeeRepository extends JpaRepository<Employee, Long> {
    // Spring Data JPA compiles this into a PARAMETERIZED SQL query —
    // complete protection from SQL injection, with no effort from you.
    Optional<Employee> findByLoginUid(String loginUid);
}
```
```java
@Service
public class CustomEmployeeDetailsService implements UserDetailsService {

    private final EmployeeRepository employeeRepository;

    public CustomEmployeeDetailsService(EmployeeRepository employeeRepository) {
        this.employeeRepository = employeeRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return employeeRepository.findByLoginUid(username)
                .orElseThrow(() -> new UsernameNotFoundException("Employee UID not found: " + username));
    }
}
```

> **Your question [Q38] on injection:** *"i guess we need to use parameterized query to prevent SQL injection — do we also use the same parameterized query for NoSQL as well?"*
>
> **Spring Data JPA parameterizes everything automatically**, including derived query methods and `@Query`. For **NoSQL**, parameterized *strings* aren't the mechanism — the MongoDB driver compiles queries into **structured BSON documents** rather than evaluating a text string, so classic injection doesn't apply.
>
> ⚠️ **But NoSQL injection is real, and the source answer glossed over it.** If you build a query from raw user input — for example passing a client-supplied map straight into a `Criteria`, or using `@Query("{ 'username': ?0 }")` with unescaped concatenation — an attacker can inject **operators** like `{"$ne": null}` or `{"$gt": ""}` and bypass an authentication check. The rule is the same in both worlds: **never concatenate user input into a query; always bind it as a parameter.**

#### Blueprint B — user and roles in two separate tables [Q39]

> **Your question:** *"i think if we have two tables — one for user details and second for user roles — then we need to override `getUserByUserName` and `getRoleByUserName`, is this true?"*
>
> **Your instinct about the logic is right; the method names are not.** There is still only **one** method: `loadUserByUsername`. You solve the two-table problem with **JPA relationships** and let Hibernate emit the `JOIN`.

```java
@Entity
@Table(name = "app_users")
public class User implements UserDetails {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(unique = true, nullable = false) private String username;
    @Column(nullable = false)                private String password;

    // Maps the separate roles table. Creates 'user_roles' with 'user_id' + 'role_name'.
    @ElementCollection(fetch = FetchType.EAGER)      // ⚠️ see the LAZY discussion below
    @CollectionTable(name = "user_roles", joinColumns = @JoinColumn(name = "user_id"))
    @Column(name = "role_name")
    private List<String> roles;                      // ["ROLE_USER", "ROLE_ADMIN"]

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return this.roles.stream()
                .map(SimpleGrantedAuthority::new)
                .collect(Collectors.toList());
    }
    @Override public String  getPassword()             { return this.password; }
    @Override public String  getUsername()             { return this.username; }
    @Override public boolean isAccountNonExpired()     { return true; }
    @Override public boolean isAccountNonLocked()      { return true; }
    @Override public boolean isCredentialsNonExpired() { return true; }
    @Override public boolean isEnabled()               { return true; }
}
```
```java
public interface UserRepository extends JpaRepository<User, Long> {
    Optional<User> findByUsername(String username);
}
```
```java
@Service
public class CustomUserDetailsService implements UserDetailsService {

    private final UserRepository userRepository;
    public CustomUserDetailsService(UserRepository userRepository) { this.userRepository = userRepository; }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        // Because of EAGER fetching, Hibernate JOINs the roles table in the same query
        User user = userRepository.findByUsername(username)
                .orElseThrow(() -> new UsernameNotFoundException("User not found: " + username));
        return user;
    }
}
```
**The flow:** client sends login → Spring calls `loadUserByUsername("alice")` → JPA queries `app_users` and joins `user_roles` → `getAuthorities()` maps the strings to `SimpleGrantedAuthority` → authentication completes.

#### `LazyInitializationException` when you switch to `FetchType.LAZY` [Q40]

> 📌 **The class is `org.hibernate.LazyInitializationException`** — message: `failed to lazily initialize a collection of role: … could not initialize proxy - no Session`. Get the name exactly right; you'll be searching for it.

`FetchType.EAGER` is safe but costly: every load of a `User` joins the roles, which hurts when listing thousands of users in a dashboard. Switching to `LAZY` means Hibernate defers loading until `getAuthorities()` is called — but by then `loadUserByUsername` has returned, the transaction has closed, the Hibernate `Session` is gone, and you get the exception.

**Solution A — `@EntityGraph` (✅ cleanest):** keep the field `LAZY` globally, but make an exception for the security lookup:
```java
public interface UserRepository extends JpaRepository<User, Long> {

    @EntityGraph(attributePaths = {"roles"})   // one optimized JOIN FETCH, for this method only
    Optional<User> findByUsername(String username);
}
```
✅ Ordinary fetches (listing users) stay lightweight; the security lookup gets a single eager query.

**Solution B — `@Transactional`:** keep the session open for the whole method:
```java
@Service
public class CustomUserDetailsService implements UserDetailsService {
    @Autowired private UserRepository userRepository;

    @Override
    @Transactional(readOnly = true)            // keeps the Hibernate Session active
    public UserDetails loadUserByUsername(String username) {
        User user = userRepository.findByUsername(username)
                .orElseThrow(() -> new UsernameNotFoundException("User not found"));
        user.getAuthorities().size();          // force initialization inside the transaction
        return user;
    }
}
```
⚠️ Solution B works but leaves a **detached entity** carrying an uninitialized-proxy risk downstream. **Prefer A**, or better, C:

**Solution C — [+] don't return the entity at all.** This is the real fix, and it also avoids the anti-pattern described below:
```java
@Override
@Transactional(readOnly = true)
public UserDetails loadUserByUsername(String username) {
    User u = userRepository.findByUsername(username)
            .orElseThrow(() -> new UsernameNotFoundException(username));
    return org.springframework.security.core.userdetails.User.builder()
            .username(u.getUsername())
            .password(u.getPassword())
            .authorities(u.getRoles().toArray(new String[0]))
            .disabled(!u.isActive())
            .build();                            // ← a detached, immutable snapshot
}
```

⚠️ **Making a JPA `@Entity` implement `UserDetails` is an anti-pattern**, even though every tutorial does it. Four concrete problems:
1. **The entity is stored in the `SecurityContext`** — and, with sessions, **serialized into the session store**, dragging your whole ORM graph with it.
2. **`LazyInitializationException`**, exactly as above.
3. **The password hash lives in memory for the whole request**, reachable from anywhere via `SecurityContextHolder`.
4. **Two unrelated contracts on one class** — `getUsername()` now means something to Hibernate *and* to Spring Security, and they can disagree.

✅ **Use a separate `UserPrincipal implements UserDetails` built from the entity.** Slightly more code, dramatically fewer surprises.

### S2.6 Passwords: hashing, salting, and the bcrypt migration [Q34, Q37, Q14]

> **Your question [Q34]:** *"does spring boot automatically take care of storing plain text password in encrypting (doing peppering, hashing, adding salt to the password etc — does all of these get done by spring boot automatically for password storing)?"*

**No. Spring Boot will not guess how to hash your passwords.** If you pass a plain-text string straight to `repository.save(user)`, **it is written to your database as plain text.** Hashing on write is *your* call; Spring only standardises *how*.

What Spring does give you is **`PasswordEncoder`**, and the standard choice `BCryptPasswordEncoder`, which handles **salting, hashing and the CPU work factor automatically**.

**1. Register the encoder bean:**
```java
@Bean
public PasswordEncoder passwordEncoder() {
    return new BCryptPasswordEncoder();   // random salt per user, built in
}
```

**2. Use it at registration — explicitly:**
```java
@Service
public class RegistrationService {
    @Autowired private UserRepository userRepository;
    @Autowired private PasswordEncoder encoder;

    public void registerNewUser(UserRegistrationDto dto) {
        User user = new User();
        user.setUsername(dto.getUsername());

        String secureHash = encoder.encode(dto.getPassword());   // ← hash BEFORE the DB layer
        user.setPassword(secureHash);

        userRepository.save(user);
    }
}
```

**3. Verification is automatic.** You never write it. Spring Security's `DaoAuthenticationProvider` takes the incoming plain-text password, fetches the stored hash via your `UserDetailsService`, and calls `encoder.matches(plainText, storedHash)` internally.

**On salt and pepper specifically**, since you asked precisely:

| | Handled? | How |
|---|---|---|
| **Hashing** | ✅ by `PasswordEncoder` | you must call `.encode()` |
| **Salting** | ✅ **fully automatic** | bcrypt generates a random 16-byte salt per password and **stores it inside the hash string** — that's why two identical passwords give different hashes, and why there's no salt column |
| **Work factor / cost** | ✅ | default strength **10**; `new BCryptPasswordEncoder(12)` to raise it |
| **Peppering** | ❌ **not built in** | a pepper is an application-wide secret kept outside the DB. Spring has no first-class support; you'd wrap a `PasswordEncoder` or use `Argon2PasswordEncoder` with a secret |
| **Timing-attack resistance** | ✅ | `matches()` is constant-time |

**The bcrypt hash format** — worth being able to read:
```
$2a$10$N9qo8uLOickgx2ZMRZoMye  IjZAgcfl7p92ldGxad68LJZdL17lhWy
 │  │  └──────── salt (22 chars) ──┘ └──────── hash (31 chars) ────┘
 │  └─ cost factor (10 = 2^10 = 1024 rounds)
 └─ algorithm version
```
**Always 60 characters.** ⚠️ Your password column must be at least `VARCHAR(60)` — a `VARCHAR(32)` left over from an MD5 era will silently truncate and every login will fail.

**Available encoders:**

| Encoder | Note |
|---|---|
| **`BCryptPasswordEncoder`** | ✅ the safe default, universally understood |
| `Argon2PasswordEncoder` | ✅ the modern winner (Password Hashing Competition); memory-hard, best GPU resistance |
| `SCryptPasswordEncoder` | memory-hard alternative |
| `Pbkdf2PasswordEncoder` | FIPS-friendly |
| ⚠️ `NoOpPasswordEncoder` | **plain text.** Deprecated. Tests only, never anywhere else. |

#### [Q14 + Q37 — the same question, merged] Changing from a "normal"/reversible algorithm to bcrypt

> **Your question (asked twice, as Q14 and Q37):** *"do we need to make any code changes if we have changed our decryption algorithm from normal to bcrypt?"*

**Yes — and the changes are structural, because you are switching from an *encryption* model to a *hashing* model.**

**⚠️ The core realization: bcrypt has no decryption.** It is a **one-way** hash designed for password storage, not a reversible cipher like AES. It is mathematically impossible to recover the plaintext.

**1. The verification logic changes:**

| Action | Old way (encryption) | New way (bcrypt) |
|---|---|---|
| Verify | `decrypt(storedCipher) == userInput` | `encoder.matches(userInput, storedHash)` |

With the bean declared, Spring wires it into your `UserDetailsService` automatically (SQL or NoSQL) — you write **no** `if (inputPassword == dbPassword)` anywhere.

**2. You must delete every "reveal the plaintext" feature.** A "Show password" button, or an email that sends the user their actual password, **breaks entirely** and cannot be rewritten. Replace it with a **reset flow** (a one-time token link by email). *(This is a feature loss you should raise with product before the migration, not after.)*

**3. Database schema changes:**
- **Length:** bcrypt output is always 60 chars. `VARCHAR(60)` minimum.
- **Type:** if you stored raw encrypted bytes in a `BLOB`, move to a plain string column.

**4. ⚠️ The legacy-user problem — the part that causes a production incident.** If you swap the encoder on a live database, **every existing user is instantly locked out**: their stored value is plain text or MD5, Spring treats it as a bcrypt hash, and the comparison fails. (Depending on configuration you get either a silent auth failure or `IllegalArgumentException: Invalid salt version`.)

**Two migration strategies:**

**Option A — the lazy upgrade (✅ recommended).** Support the old format for verification only, and rewrite each user to bcrypt on their next successful login. Spring has a first-class mechanism for this: **`DelegatingPasswordEncoder`**.
```java
import org.springframework.security.crypto.factory.PasswordEncoderFactories;

@Bean
public PasswordEncoder passwordEncoder() {
    // Dispatches on a {prefix} in the stored string:
    //   {bcrypt}$2a$10...   {noop}plain_text   {pbkdf2}...   {argon2}...
    return PasswordEncoderFactories.createDelegatingPasswordEncoder();
}
```
Combine it with `UserDetailsPasswordService`, and Spring **re-encodes and saves the password automatically** on each successful login:
```java
@Service
public class CustomUserDetailsService implements UserDetailsService, UserDetailsPasswordService {
    @Override
    public UserDetails updatePassword(UserDetails user, String newEncodedPassword) {
        // Spring calls this itself when the stored encoding is outdated
        repo.updatePasswordHash(user.getUsername(), newEncodedPassword);
        return ...;
    }
}
```
✅ **Zero downtime, zero forced resets, and the population migrates itself.**

**Option B — a one-time decrypt-then-hash script.** Read every record, decrypt with the old system, bcrypt the plaintext, write it back. Only viable if you fully control the decryption keys and the volume is manageable. It also means **every password exists in plaintext in memory** during the run — do it in one transaction-scoped batch job, never with logging enabled.

#### Is the `{bcrypt}` / `{noop}` prefix mandatory in the database? [Q38]

> **Your question:** *"is it mandatory to store the operation type in the db for the password like {noop} plain pass, {bcrypt} encrypted pass?"*

**No — it depends entirely on which encoder bean you declare.**

| Your `PasswordEncoder` bean | Database must contain |
|---|---|
| `new BCryptPasswordEncoder()` | ✅ **raw hashes** — `$2a$10$...`, no prefix |
| `PasswordEncoderFactories.createDelegatingPasswordEncoder()` | ⚠️ **prefixed** — `{bcrypt}$2a$10$...` |
| **no bean at all** | ⚠️ **prefixed** — Boot's default *is* the delegating encoder |

⚠️ **That last row is the single most-Googled Spring Security error:**
```
java.lang.IllegalArgumentException: There is no PasswordEncoder mapped for the id "null"
```
It means you stored a raw hash but never declared a `PasswordEncoder` bean, so the **delegating** encoder is in play and cannot find a `{...}` prefix to dispatch on. Two fixes: declare `new BCryptPasswordEncoder()`, **or** prefix your stored values.

✅ **If your organisation standardises on one algorithm, a plain `BCryptPasswordEncoder` and unprefixed hashes is perfectly fine** — and if you later move to a custom scheme, you write a class implementing `PasswordEncoder` and return it from the same bean method. **The whole application adapts with no database mutation.**


## S3. Stateless authentication: JWT and refresh tokens

### S3.1 Writing a JWT filter by hand [Q35]

> **Your questions [Q35]:** *"what happens if we store our user in some NoSQL db and not in a SQL db? will this work, and how does each request make the db call to fetch the user credentials and match the password before forwarding to the controller? how to write a custom JWT Filter manually if you aren't using an external OAuth2 provider?"*

**Does NoSQL work?** **Yes, 100%** — `UserDetailsService` decouples verification from storage, as in [§S2.5](#s25-custom-userdetailsservice--any-schema-any-database-q36-q38-q39).

**Does every request hit the database?** **No — and this is the key insight about stateless JWT auth:**

| Step | DB hit? |
|---|---|
| **1. Login** — client sends username + password | ✅ **yes, once.** Query the user, `encoder.matches(...)`, sign a JWT, return it. |
| **2. Every later request** — client sends `Authorization: Bearer <jwt>` | ❌ **no.** The app holds the secret/public key, **cryptographically validates the token in local memory**, and if the signature is authentic and it hasn't expired, trusts the payload (username, roles) and maps it into the security context — **no network trip.** |

💡 That's the whole trade of JWT: you swap a database round-trip per request for the inability to revoke a token before it expires. **Keep access tokens short-lived (5–15 min)** and use a refresh token — which *is* checked against storage — so a revoked user is locked out within one token lifetime.

#### Step A — the domain and the `UserDetailsService`
```java
@Service
public class CustomUserDetailsService implements UserDetailsService {

    private final UserRepository userRepository;
    public CustomUserDetailsService(UserRepository userRepository) { this.userRepository = userRepository; }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        // Pull the document/row out of the target database platform
        return userRepository.findByUsername(username)
                .orElseThrow(() -> new UsernameNotFoundException("User not found: " + username));
    }
}
```

#### Step B — the filter itself

**A correct Spring Security 6 JWT filter.** Three details are easy to leave out and each causes a real bug; they are marked `✅ IMPORTANT` inline:

```java
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContext;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.web.filter.OncePerRequestFilter;
import java.io.IOException;

public class ManualJwtAuthenticationFilter extends OncePerRequestFilter {
    //                                      ^^^^^^^^^^^^^^^^^^^^^ guarantees ONE execution per
    //                                      request even across FORWARD/INCLUDE dispatches

    private final JwtTokenUtility jwtTokenUtility;
    private final CustomUserDetailsService userDetailsService;

    public ManualJwtAuthenticationFilter(JwtTokenUtility jwtTokenUtility,
                                         CustomUserDetailsService userDetailsService) {
        this.jwtTokenUtility = jwtTokenUtility;
        this.userDetailsService = userDetailsService;
    }

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response,
                                    FilterChain filterChain) throws ServletException, IOException {

        // 1. Extract the Authorization header
        String authHeader = request.getHeader("Authorization");

        // ✅ IMPORTANT 1: skip if already authenticated — another filter may have done it
        if (authHeader != null && authHeader.startsWith("Bearer ")
                && SecurityContextHolder.getContext().getAuthentication() == null) {

            String token = authHeader.substring(7);          // strip "Bearer "

            // ✅ IMPORTANT 2: a malformed/expired token throws — an uncaught exception
            //                 here produces a 500 instead of a clean 401
            try {
                // 2. Memory-isolated validation — NO DB CALL
                if (jwtTokenUtility.isTokenValid(token)) {
                    String username = jwtTokenUtility.extractUsername(token);
                    String role     = jwtTokenUtility.extractRole(token);

                    // 3. Rebuild the principal straight from the token contents.
                    //    Optional: to catch a user banned in the last 60s, call
                    //    userDetailsService.loadUserByUsername(username) here instead —
                    //    that trades the "no DB call" optimization for freshness.
                    UserDetails userDetails = new UserAccount(username, "", role);

                    // 4. Wrap it in Spring's token container
                    UsernamePasswordAuthenticationToken authentication =
                            new UsernamePasswordAuthenticationToken(
                                    userDetails, null, userDetails.getAuthorities());
                    //                          ^^^^ credentials MUST be null — never hold the token

                    authentication.setDetails(
                            new WebAuthenticationDetailsSource().buildDetails(request));  // IP, session id

                    // ✅ IMPORTANT 3: create a NEW context, don't mutate the shared one.
                    //    Spring Security 6 docs require this to avoid cross-thread race conditions.
                    SecurityContext context = SecurityContextHolder.createEmptyContext();
                    context.setAuthentication(authentication);
                    SecurityContextHolder.setContext(context);
                }
            } catch (Exception e) {
                // Leave the context empty. AuthorizationFilter will reject with 401/403 cleanly.
                logger.debug("JWT validation failed: " + e.getMessage());
            }
        }

        // 6. Continue down the chain (ALWAYS — even when auth failed)
        filterChain.doFilter(request, response);
    }
}
```

⚠️ **Why the three fixes matter, concretely:**
1. **Not checking for an existing authentication** lets a later header overwrite an already-established principal.
2. **No try/catch** means an expired token — the *normal* case — surfaces as a **500 Internal Server Error** instead of a 401, and leaks a stack trace.
3. **`getContext().setAuthentication(...)`** mutates the context object the thread already holds. The Spring Security reference explicitly says: *"You should create a new `SecurityContext` instance instead of using `SecurityContextHolder.getContext().setAuthentication(authentication)` to avoid race conditions across multiple threads."*

💡 **Always call `filterChain.doFilter(...)`, even on failure.** The filter's job is only to *populate* the context. `AuthorizationFilter` (#16 in [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34)) decides whether to reject — that's what keeps `permitAll()` paths reachable without a token.

#### Step C — wiring it in

```java
@Configuration
@EnableWebSecurity
public class SecurityEngineConfiguration {

    private final CustomUserDetailsService userDetailsService;
    private final JwtTokenUtility jwtTokenUtility;

    public SecurityEngineConfiguration(CustomUserDetailsService userDetailsService,
                                       JwtTokenUtility jwtTokenUtility) {
        this.userDetailsService = userDetailsService;
        this.jwtTokenUtility = jwtTokenUtility;
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())                                  // stateless API
            .sessionManagement(session ->
                 session.sessionCreationPolicy(SessionCreationPolicy.STATELESS))  // no cookies at all
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/api/v1/auth/login", "/api/v1/auth/register").permitAll()
                .requestMatchers("/api/v1/admin/**").hasAuthority("ROLE_ADMIN")
                .anyRequest().authenticated()
            );

        // Insert our filter BEFORE Spring's native form-login filter
        http.addFilterBefore(
            new ManualJwtAuthenticationFilter(jwtTokenUtility, userDetailsService),
            UsernamePasswordAuthenticationFilter.class
        );

        return http.build();
    }
}
```
💡 **Why `addFilterBefore(..., UsernamePasswordAuthenticationFilter.class)`?** It isn't arbitrary. That filter is the conventional landmark for "where authentication happens." Placing yours before it means the context is populated by the time any authentication or authorization step looks.

⚠️ **`SessionCreationPolicy.STATELESS` matters more than it looks.** Without it Spring creates an `HttpSession` for every request — in a stateless API that's a memory leak proportional to traffic, and it breaks horizontal scaling unless sessions are replicated.

💡 **[+] Consider not writing this filter at all.** If your tokens are standard JWTs, Spring's built-in resource server does everything above — validation, key rotation, JWKS fetching, clock skew, `scope` → authority mapping — with **three lines**:
```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-oauth2-resource-server</artifactId>
</dependency>
```
```java
.oauth2ResourceServer(oauth2 -> oauth2.jwt(Customizer.withDefaults()))
```
```properties
spring.security.oauth2.resourceserver.jwt.issuer-uri=https://auth.example.com/
# or point straight at the issuer's PUBLIC keys (asymmetric RS256/ES256), skipping discovery:
# spring.security.oauth2.resourceserver.jwt.jwk-set-uri=https://auth.example.com/.well-known/jwks.json
# (a symmetric HMAC secret has no property; expose a JwtDecoder bean: NimbusJwtDecoder.withSecretKey(key).build())
```
Write the manual filter only when the token format is non-standard. **Hand-rolled JWT code is a recurring source of CVEs** — `alg: none` acceptance, unverified signatures, missing `exp` checks.



### S3.2 The complete JWT flow: login endpoint, token creation, and the filter

> **Your design notes (condensed):** *"Authenticate with credentials → generate token → on later requests: extract → decode → verify signature → check expiry (and sub / custom checks) → process. With UsernamePassword or Basic we authenticate on each request, but with JWT only once — yet the default filters run for every request; how to make it only once? So for login we skip the filter chain and call the AuthenticationManager directly (UserDetailsService + PasswordEncoder, no Spring magic) — skip it for signup too. Is authorization also manual, or the same as before? After authentication we create the token using a JWT library."*

The full picture first:

```
① LOGIN (once)                                          ② EVERY LATER REQUEST
POST /api/auth/login {username,password}                GET /api/orders   Authorization: Bearer eyJ…
  │ filter chain runs (headers, CORS…)                     │ filter chain runs
  │ AuthorizationFilter: /api/auth/** permitAll ✅         │ JwtFilter (before UsernamePasswordAuthenticationFilter):
  ▼                                                        │   extract → parse+verify signature → check exp/nbf
AuthController.login()                                     │   (→ optional sub / custom claim checks)
  authenticationManager.authenticate(                      │   → build Authentication(username, authorities)
     new UsernamePasswordAuthenticationToken(u, p))        │   → SecurityContextHolder.setContext(...)
  → ProviderManager → DaoAuthenticationProvider            │ AnonymousAuthenticationFilter: context already set → skip
     → UserDetailsService (DB) + PasswordEncoder.matches   │ ExceptionTranslationFilter
  ✅ ok → jwtUtil.generateToken(user)                      │ AuthorizationFilter: hasRole/hasAuthority on the context ✅
  ◀── 200 {"accessToken":"eyJ…"}                           ▼ controller          (NO password check, NO session)
```

**Your questions, answered:**

| Your question / assumption | Answer |
|---|---|
| "JWT authenticates only once, but the filters run for every request: how do we make the check happen only once?" | Two different "once"s. The **password check** happens once, at login. The **filter** still runs on **every** request, but it only verifies a signature in memory (microseconds, no DB). That *is* the stateless design. `OncePerRequestFilter` means "once per HTTP request, even across internal forwards", not "once per user". |
| "For login we skip the filter chain" | 📌 **Not skipped.** `/login` still passes through the whole chain (security headers, CORS, firewall). `permitAll()` only tells `AuthorizationFilter` not to *demand* authentication there, and your `JwtFilter` simply finds no Bearer header and passes through. Then **your controller** calls `AuthenticationManager.authenticate(...)` itself. Same for `/signup`. |
| "Without Spring magic" | Half true. You call the manager by hand, but everything behind it (`ProviderManager` → `DaoAuthenticationProvider` → your `UserDetailsService` + `PasswordEncoder`) is exactly the machinery of [§S2.2](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder). You do need `UserDetailsService`, which is how the password is checked. |
| "Is authorization manual too, or the same as before?" | ✅ **Exactly the same as before.** Once the filter puts an `Authentication` with authorities into the `SecurityContextHolder`, `AuthorizationFilter` and `@PreAuthorize` don't care how it got there ([§S4](#s4-authorization-what-are-you-allowed-to-do)). |
| "once we create the token we don't need AuthenticationController, ProviderManager, UserDetails" | ✅ On later requests the manager/provider/password check are unused. ⚠️ But many JWT filters (including the one below) call `userDetailsService.loadUserByUsername()` **on every request**, which is a DB hit per request and undoes "stateless". Choose deliberately: authorities **from claims** (no DB; role changes apply when the token expires), or **from the DB** (fresh, but a query per request). [§S3.1](#s31-writing-a-jwt-filter-by-hand-q35) shows the claims-based version. |
| "register our jwtAuthenticationFilter **before** UsernamePasswordAuthenticationFilter, else Spring asks for username/password" | ✅ Right place, slightly different reason. In a custom chain without `.formLogin()`, `UsernamePasswordAuthenticationFilter` **isn't even in the chain**. Its class is still a valid **position anchor** in Spring's filter-order registry, so `addFilterBefore(jwtFilter, UsernamePasswordAuthenticationFilter.class)` works. What matters is that your filter runs **before `AnonymousAuthenticationFilter` and `AuthorizationFilter`**. Otherwise the request is marked anonymous and rejected first. |
| "jwtAuthenticationFilter talks to jwtUtil, creates the token…" | 📌 **Correction:** the filter **never creates** tokens; the login controller does. The filter only **extracts, verifies and parses** an incoming token and populates the `SecurityContext`. |

#### The three `jjwt` artifacts, and `compact()`

| Artifact | Role | Scope |
|---|---|---|
| `jjwt-api` | the interfaces you code against: `Jwts.builder()`, `Jwts.parser()`, `Claims`, `Keys` | compile |
| `jjwt-impl` | the actual implementation (signing, parsing, crypto) | **runtime**, so you can't accidentally depend on internals |
| `jjwt-jackson` (or `jjwt-gson`) | JSON (de)serialization of header and claims | runtime |

(Latest release checked on Maven Central: **0.13.0**, API-identical to 0.12.x, which introduced the `Jwts.SIG` / `verifyWith` / `parseSignedClaims` style used below. 0.11-era tutorials using `setSubject` / `parseClaimsJws` / `SignatureAlgorithm.HS256` use deprecated names.)

**What `compact()` does:** it Base64URL-encodes the header and the payload, signs `header.payload`, Base64URL-encodes the signature, and joins the three with **dots**: `xxxxx.yyyyy.zzzzz`. 📌 It uses dots, not colons. ⚠️ Base64URL is **encoding, not encryption**. Anyone can read the payload at jwt.io, so never put secrets in claims. (Encrypted JWTs, JWE, exist but are a different feature.)

#### Symmetric vs asymmetric signing, and JWKS

> **Your note:** *"with symmetric signing both our public and private key will be the same; with asymmetric they differ, and we fetch a public URL to get the list of keys and then sign or verify the token."*

| | **Symmetric** — HMAC (`HS256`) | **Asymmetric** — RSA / EC (`RS256`, `ES256`) |
|---|---|---|
| Keys | **one shared secret** signs *and* verifies (there's no "public/private" here, just one secret) | **private key signs**, **public key verifies** |
| Who can verify | only holders of the secret, who could also *forge* tokens | anyone with the public key, who **cannot** forge tokens |
| Fits | one service issues and verifies its own tokens | an auth server issues, many services verify |
| JWKS | not used | the issuer publishes public keys at e.g. `/.well-known/jwks.json`. The token header carries a `kid` (key id) saying which key verifies it, which enables key rotation |

📌 **Correction:** a JWKS URL is used **only to verify**. **Signing always uses the private key, which never leaves the issuer.** Verifiers fetch the JWKS (and cache it); they cannot sign.

#### `JwtUtil` — corrected and complete

```java
@Component
public class JwtUtil {

    private final SecretKey hmacKey;                 // Option A — symmetric
    private final Duration ttl = Duration.ofMinutes(15);

    // ✅ secret from config/secret store, never hardcoded. HS256 needs >= 256 bits (32 bytes);
    //    Keys.hmacShaKeyFor throws WeakKeyException otherwise.
    public JwtUtil(@Value("${app.jwt.secret}") String base64Secret) {
        this.hmacKey = Keys.hmacShaKeyFor(Decoders.BASE64.decode(base64Secret));
    }

    public String generateToken(UserDetails user) {
        List<String> roles = user.getAuthorities().stream()
                .map(GrantedAuthority::getAuthority)          // ✅ STRINGS, not GrantedAuthority objects
                .toList();
        Instant now = Instant.now();
        return Jwts.builder()
                .subject(user.getUsername())
                .claim("roles", roles)
                .issuer("https://auth.myapp.example")
                .issuedAt(Date.from(now))
                .expiration(Date.from(now.plus(ttl)))
                .signWith(hmacKey)                            // alg (HS256/384/512) inferred from key size
                .compact();
    }

    /** Verifies signature AND exp/nbf; throws JwtException (e.g. ExpiredJwtException) if invalid. */
    public Claims parseAndVerify(String token) {
        return Jwts.parser()
                .verifyWith(hmacKey)
                .requireIssuer("https://auth.myapp.example")  // custom check: reject foreign tokens
                .clockSkewSeconds(30)                         // tolerate small clock drift
                .build()
                .parseSignedClaims(token)
                .getPayload();
    }
}
```

**Option B: asymmetric, as a sketch.** Sign with `.signWith(privateKey)` and verify with `.verifyWith(publicKey)`, loading the keys from PEM files or a keystore. `Jwts.SIG.RS256.keyPair().build()` generates a pair but creates a **new pair at every restart**, which invalidates all tokens. Demos only. If you're the *verifier* of someone else's RS256 tokens, don't hand-roll JWKS fetching: use Spring's resource server ([§S5.5](#s55-pure-resource-server-oauth2resourceserver-and-mapping-roles)), which fetches, caches and rotates keys for you.

⚠️ **Fixes vs the source implementation:**
- **Hardcoded secret string.** Load it from config.
- **`claims.put("roles", userDetails.getAuthorities())`** serialized `SimpleGrantedAuthority` *objects*. Map them to strings.
- **No issuer/audience check.** Added `requireIssuer`.
- **`Jwts.SIG.RS256.keyPair().build()` as a field.** Keys regenerate on every restart.

#### The filter, the controller and the config

The robust filter is in [§S3.1](#s31-writing-a-jwt-filter-by-hand-q35): it skips if already authenticated, wraps parsing in try/catch, creates an empty context, and always calls `doFilter`. The short version tied to `JwtUtil` above, with authorities from claims (no DB hit):

```java
public class JwtFilter extends OncePerRequestFilter {        // ⚠️ deliberately NOT @Component — see below
    private final JwtUtil jwtUtil;
    public JwtFilter(JwtUtil jwtUtil) { this.jwtUtil = jwtUtil; }

    @Override
    protected void doFilterInternal(HttpServletRequest req, HttpServletResponse res, FilterChain chain)
            throws ServletException, IOException {
        String header = req.getHeader(HttpHeaders.AUTHORIZATION);
        if (header != null && header.startsWith("Bearer ")
                && SecurityContextHolder.getContext().getAuthentication() == null) {
            try {
                Claims claims = jwtUtil.parseAndVerify(header.substring(7));   // signature + exp checked HERE
                List<SimpleGrantedAuthority> authorities = claims.get("roles", List.class).stream()
                        .map(r -> new SimpleGrantedAuthority((String) r)).toList();
                var auth = new UsernamePasswordAuthenticationToken(claims.getSubject(), null, authorities);
                auth.setDetails(new WebAuthenticationDetailsSource().buildDetails(req));
                SecurityContext ctx = SecurityContextHolder.createEmptyContext();   // ✅ new context
                ctx.setAuthentication(auth);
                SecurityContextHolder.setContext(ctx);
            } catch (JwtException | IllegalArgumentException e) {
                // invalid/expired → leave context empty; AuthorizationFilter → 401 via entry point
            }
        }
        chain.doFilter(req, res);                                // ✅ always continue
    }
}
```

```java
@RestController
@RequestMapping("/api/auth")
public class AuthController {
    private final AuthenticationManager authenticationManager;
    private final JwtUtil jwtUtil;

    public AuthController(AuthenticationManager am, JwtUtil jwtUtil) {   // ✅ constructor injection
        this.authenticationManager = am; this.jwtUtil = jwtUtil;          //    (the note's "@Autowired final
    }                                                                     //     field" won't compile)
    @PostMapping("/login")
    public TokenResponse login(@RequestBody AuthRequest req) {
        Authentication result = authenticationManager.authenticate(
                new UsernamePasswordAuthenticationToken(req.username(), req.password()));
        // wrong password → BadCredentialsException (see "Which exception goes where" below)
        return new TokenResponse(jwtUtil.generateToken((UserDetails) result.getPrincipal()));
    }
}

public record AuthRequest(String username, String password) {}   // ✅ immutable request DTO
public record TokenResponse(String accessToken) {}
```

📌 Your `AuthRequest` sketch declared `final` fields *with setters*, which can't compile (a `final` field can't be reassigned). A `record` is the clean fix. Also, re-using `result.getPrincipal()` avoids a second `loadUserByUsername` DB call after `authenticate` already loaded the user.

```java
@Configuration
@EnableWebSecurity
public class SecurityConfig {
    @Bean
    SecurityFilterChain chain(HttpSecurity http, JwtUtil jwtUtil) throws Exception {
        return http
            .csrf(AbstractHttpConfigurer::disable)                           // header-based token → no CSRF
            .sessionManagement(s -> s.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
            .authorizeHttpRequests(a -> a
                .requestMatchers("/api/auth/login", "/api/auth/signup", "/api/auth/refresh").permitAll()
                .anyRequest().authenticated())
            .addFilterBefore(new JwtFilter(jwtUtil), UsernamePasswordAuthenticationFilter.class)
            .build();
    }
    @Bean
    AuthenticationManager authenticationManager(AuthenticationConfiguration cfg) throws Exception {
        return cfg.getAuthenticationManager();     // the auto-built Dao provider from your UDS + encoder
    }
    @Bean PasswordEncoder passwordEncoder() { return new BCryptPasswordEncoder(); }
}
```

⚠️ **The `@Component` double-registration trap.** The docs warn: *"When you declare a Filter as a Spring bean… Spring Boot automatically registers it with the embedded container. That may cause the filter to be invoked twice."* Either don't make the filter a bean (as above: `new JwtFilter(...)` inside the config), or keep it a bean and add a `FilterRegistrationBean` with `setEnabled(false)`.

⚠️ **Which exception goes where on a bad login?** `authenticate()` throws `BadCredentialsException` inside your controller. If no `@ExceptionHandler` handles it, it propagates out of `DispatcherServlet`, up to `ExceptionTranslationFilter`, and then to the entry point (401). With JWT and no `httpBasic`/`formLogin`, set an explicit entry point so the 401 has a sensible body: `http.exceptionHandling(e -> e.authenticationEntryPoint(new HttpStatusEntryPoint(HttpStatus.UNAUTHORIZED)))`.

#### "We didn't add the token validation, i.e. whether it has expired?"

> **Your question:** *"inside `if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) { … }` we didn't add the token validation, i.e. if it has expired or not?"*

**It's already done, one line earlier.** `parseSignedClaims(token)` (inside `extractUsername` / `parseAndVerify`) **verifies the signature first**, and then checks `exp` and `nbf` (with the configured clock skew). An expired token throws `ExpiredJwtException` (a `JwtException`) and execution jumps to the `catch` before your `if` runs, so no username is ever returned from an expired or tampered token. Tutorials that add `isTokenExpired(token)` are redundant on JJWT 0.10+.

Explicit checks worth adding are the ones JJWT *can't* know:
- `userDetails.isEnabled()` / `isAccountNonLocked()` (this needs the DB, so it's the freshness trade-off above);
- issuer/audience (`requireIssuer`, `requireAudience`);
- a token denylist for logout-before-expiry.

### S3.3 Refresh tokens: short access tokens without constant re-login

**Why two tokens:**
- A JWT **cannot be revoked** before `exp` (no server state), so the access token must be **short** (5–15 min).
- Users shouldn't type passwords every 15 minutes, so a long-lived **refresh token** is issued alongside.
- The refresh token is **stateful**: it is stored server-side, so it *can* be revoked.

| | Access token | Refresh token |
|---|---|---|
| Lifetime | minutes | days |
| Format | signed JWT | ✅ an opaque random string (a JWT adds nothing here) |
| Sent | every API call, `Authorization: Bearer …` | only to `/api/auth/refresh` |
| Stored (client) | memory | ✅ `HttpOnly; Secure; SameSite=Strict` cookie, scoped to the refresh path |
| Stored (server) | nowhere | ✅ DB row, **hashed** like a password |
| Revocable | ❌ (wait for expiry) | ✅ delete the row |

```
login ──▶ {access(15m), refresh(7d)}
API call ──▶ 200 … 15 min later ──▶ 401 (expired)
client ──POST /api/auth/refresh (refresh token)──▶ server: look up hash, not expired/revoked?
        ◀── new access + NEW refresh (rotation: old one deleted)
reuse of an OLD refresh token ⇒ theft signal ⇒ revoke ALL of that user's tokens
logout ──▶ delete the refresh row (access token dies by itself within 15 min)
```

```java
@Entity
public class RefreshToken {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY) private Long id;
    @Column(nullable = false, unique = true) private String tokenHash;   // ✅ SHA-256 of the token, never the raw value
    @Column(nullable = false) private Instant expiresAt;
    @ManyToOne(optional = false) private User user;                      // ✅ many: one per device/session
}

public interface RefreshTokenRepository extends JpaRepository<RefreshToken, Long> {
    Optional<RefreshToken> findByTokenHash(String tokenHash);

    @Modifying
    @Query("delete from RefreshToken r where r.user = :user")            // bulk delete, runs immediately
    void deleteAllForUser(@Param("user") User user);
}
```

```java
@Service
public class RefreshTokenService {
    private static final Duration TTL = Duration.ofDays(7);
    private final RefreshTokenRepository repo;
    private final SecureRandom random = new SecureRandom();

    public RefreshTokenService(RefreshTokenRepository repo) { this.repo = repo; }

    @Transactional
    public String issue(User user) {
        byte[] bytes = new byte[32];
        random.nextBytes(bytes);
        String raw = Base64.getUrlEncoder().withoutPadding().encodeToString(bytes);
        RefreshToken t = new RefreshToken();
        t.setUser(user); t.setTokenHash(sha256(raw)); t.setExpiresAt(Instant.now().plus(TTL));
        repo.save(t);
        return raw;                                   // the raw value goes to the client only
    }

    /** Validates and ROTATES: deletes the presented token, returns its user. */
    @Transactional
    public User consume(String raw) {
        RefreshToken t = repo.findByTokenHash(sha256(raw))
                .orElseThrow(() -> new BadCredentialsException("Invalid refresh token"));
        repo.delete(t);
        if (t.getExpiresAt().isBefore(Instant.now())) {
            throw new BadCredentialsException("Refresh token expired");   // ⚠️ the delete rolls back with the throw;
        }                                                                 //    a cleanup job purges expired rows
        return t.getUser();
    }
}
```

```java
@PostMapping("/refresh")
public TokenResponse refresh(@CookieValue("refresh_token") String raw, HttpServletResponse res) {
    User user = refreshTokenService.consume(raw);
    setRefreshCookie(res, refreshTokenService.issue(user));      // rotation
    return new TokenResponse(jwtUtil.generateToken(user));
}

@PostMapping("/logout")
public ResponseEntity<Void> logout(@CookieValue(value = "refresh_token", required = false) String raw) {
    if (raw != null) { try { refreshTokenService.consume(raw); } catch (AuthenticationException ignored) {} }
    return ResponseEntity.noContent().build();
}
```

⚠️ **What was changed from the source implementation, and why:**
1. **The raw token was stored.** A DB leak would hand out live sessions. Store a hash; SHA-256 is enough for 256-bit random tokens, so no bcrypt is needed.
2. **`@OneToOne` + `deleteByUser` then `save` in the same flow.** This allows one session per user, so logging in on a phone logs out the laptop.
   - **The failure (each step is documented; I did not run this exact code):**
     - Spring Data's derived `deleteBy…` loads the rows and calls `remove()`, and the `DELETE` is deferred to flush.
     - The Hibernate 6.6 User Guide says an `IDENTITY` generator *"must execute the insert right after calling persist()"*. So the `INSERT` runs **immediately** at `save()`, before the pending `DELETE`.
     - Even with a sequence id, the guide's *Flush operation order* puts `EntityInsertAction` before `EntityDeleteAction`. Its own example (remove a row, then persist a new one) prints the `INSERT` first.
     - The result: with the unique `user_id` that `@OneToOne` implies, the insert **hits a unique-constraint violation on the second login**.
     - The fixes: call `flush()` after the delete, use the bulk `@Modifying @Query` delete, or use `@ManyToOne`.
   - The bulk `@Modifying @Query` delete above executes at once; `@ManyToOne` removes the conflict entirely.
3. **Derived `deleteBy…` without a transaction** fails with *"No EntityManager with actual transaction available"*. Service methods are `@Transactional` above.
4. **Expiry is checked before rotating.** Rotation means the old token can't be replayed. Reuse detection (storing a token "family" id and revoking the family on reuse) is the next step up.
5. **`RuntimeException("...")` → `BadCredentialsException`.** With the explicit entry point from §S3.2 this gives a 401, not a 500.
6. Add `/api/auth/refresh` to `permitAll()`. Its own credential is the refresh cookie. ⚠️ Because it is a **cookie** endpoint, CSRF applies to it ([§S6.1](#s61-csrf-q34)). `SameSite=Strict` plus a path-scoped cookie is the usual mitigation.

## S4. Authorization: what are you allowed to do?

### S4.1 The authorization architecture: `AuthorizationFilter` → `AuthorizationManager`

> **Your notes:** *"By default role-based permissions use ROLE_ as prefix (changeable). At the end of the filter chain is the authorization filter. Like the AuthenticationManager, it delegates to the AuthorizationManager (a functional interface with a single abstract method check()); if authorized the request goes to the controller, else AccessDenied exception. There are several implementations — what are they? Each has .authorize — how does the AuthorizationManager decide which concrete one to choose — does it loop over all like the AuthenticationManager? And then it calls .check, so for authorization we have two methods .authorize and .check?"*

```
request (already authenticated, or anonymous)
   │
   ▼
AuthorizationFilter  (LAST filter)  ── authorizationManager.authorize(() -> authentication, request)
   │
   ▼
RequestMatcherDelegatingAuthorizationManager      ← built from your authorizeHttpRequests(...) block
   entries, IN DECLARATION ORDER:
     "/api/auth/**"            → permitAll         (AuthorizationManager)
     GET  "/api/bookings/**"   → hasAuthority(...) (AuthorityAuthorizationManager)
     "/api/admin/**"           → hasRole("ADMIN")  (AuthorityAuthorizationManager)
     anyRequest                → authenticated()   (AuthenticatedAuthorizationManager)
   → FIRST entry whose RequestMatcher matches → delegate.authorize(...)   (no further looping)
   │
   ├─ granted → chain.doFilter → DispatcherServlet → (method security, §S4.6) → controller
   └─ denied  → throws AccessDeniedException ──▶ ExceptionTranslationFilter (§S1.5)
                     anonymous? → AuthenticationEntryPoint → 401   |   authenticated? → AccessDeniedHandler → 403
```

| Your note | Precise version |
|---|---|
| "single abstract method `check()`" | 🔖 **Version-dependent.** Security 5.5–6.3: `check(Supplier<Authentication>, T)` returning `AuthorizationDecision`. **6.4** added `authorize(...)` returning `AuthorizationResult`, and in **Security 7 `check` is gone**: `authorize` is the single abstract method (verified in the 7.x javadoc). The default method `verify(...)` calls it and throws `AccessDeniedException` on denial. |
| "two methods `.authorize` and `.check`" | 📌 **No, it's one decision method.** It was renamed over versions, not split into two steps. |
| "does it loop over all managers like the AuthenticationManager?" | **Different rule.** `ProviderManager` loops until a provider *succeeds*. `RequestMatcherDelegatingAuthorizationManager` loops over **request matchers** and stops at the **first matching path**. That manager alone decides, even if it denies. That's why rule order matters ([§S4.2](#s42-declarative-security--the-central-configuration-q34)). No match at all → denied. |
| 🔖 Boot 2.7 | Boot 2.7's default chain uses the *older* `authorizeRequests()`, which runs **`FilterSecurityInterceptor`** with an `AccessDecisionManager` and voters, not `AuthorizationFilter`. You get `AuthorizationFilter` on 5.7 only if you write `authorizeHttpRequests(...)`. Boot 3+ always uses `AuthorizationFilter`. |

**The implementations you meet (most are created for you by the DSL):**

| Implementation | Created by | Example |
|---|---|---|
| `AuthorityAuthorizationManager` | `hasRole`, `hasAnyRole`, `hasAuthority`, `hasAnyAuthority` | `.requestMatchers("/admin/**").hasRole("ADMIN")` — checks for authority `ROLE_ADMIN` |
| `AuthenticatedAuthorizationManager` | `authenticated()`, `fullyAuthenticated()`, `rememberMe()`, `anonymous()` | `fullyAuthenticated()` rejects "remember-me" logins for sensitive pages |
| `SingleResultAuthorizationManager` (`permitAll` / `denyAll`) | `permitAll()`, `denyAll()` | public docs, shut-off legacy paths. ✅ Verified in source: `SingleResultAuthorizationManager` is `@since 6.5`. In 5.8–6.4, `permitAll()` used a lambda field (`permitAllAuthorizationManager`) in `AuthorizeHttpRequestsConfigurer`. In 7.x it goes through `AuthorizationManagerFactory.permitAll()`, whose default returns `SingleResultAuthorizationManager.permitAll()` |
| `WebExpressionAuthorizationManager` | `.access(new WebExpressionAuthorizationManager("…"))` | `"hasRole('ADMIN') and hasIpAddress('10.0.0.0/8')"` |
| `AuthorizationManagers.allOf(...)` / `anyOf(...)` | composition | role **and** a custom IP/tenant check |
| your own lambda | `.access((auth, ctx) -> new AuthorizationDecision(...))` | `"/tenants/{id}/**"` only for that tenant's users |
| `RequestMatcherDelegatingAuthorizationManager` | the whole `authorizeHttpRequests` block | the router shown above |
| `PreAuthorizeAuthorizationManager`, `PostAuthorizeAuthorizationManager`, `SecuredAuthorizationManager`, `Jsr250AuthorizationManager` | method security ([§S4.6](#s46-method-security-under-the-hood-interceptors-expression-handler-evaluationcontext)) | `@PreAuthorize("hasAuthority('booking:write')")` |

> **Your question:** *"do we do the same in FastAPI and Express — for RBAC do we add the middleware at the very top or in the respective controller, unlike Spring where RBAC is configured at a single central place, the filter?"*

| | Where RBAC usually lives | Code |
|---|---|---|
| **Spring** | **both, by design**: a central URL gate (`authorizeHttpRequests`) plus per-method rules (`@PreAuthorize`) | see §S4.2 / §S4.5 |
| 🐍 **FastAPI** | **per route**, via dependencies; central only per router | `@app.delete("/b/{id}", dependencies=[Depends(require("booking:write"))])` or `APIRouter(dependencies=[...])` |
| 🟨 **Express** | **per route** middleware, or mounted on a path prefix | `router.post("/b", authJwt, authorize("booking:write"), handler)` / `app.use("/admin", requireRole("admin"))` |

✅ The Spring advantage is that a **new endpoint is denied by default** (`anyRequest().authenticated()` catches it), whereas forgetting a `Depends(...)` in FastAPI leaves the route open. `@PreAuthorize` is Spring's equivalent of FastAPI's per-route `Depends`.

### S4.2 Declarative security — the central configuration [Q34]

> **Your questions:** *"what are the methods of securing spring boot application (declarative and programmatic)? do we put these security checks in each controller/router or at a central place? how to protect url based on the role (RBAC)? what is the spring security configuration class? is this also a bean?"*

**A. Declarative security (centralized filter routing).** You configure routing rules in one central class — **identical in spirit to organizing routes into public and private groups in FastAPI.**

```java
@Configuration
@EnableWebSecurity                     // 1. Activates the security engine
public class SecurityConfiguration {

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())              // Disabled for stateless REST APIs
            .authorizeHttpRequests(auth -> auth
                // Public endpoints (no auth needed)
                .requestMatchers("/api/v1/public/**", "/swagger-ui/**").permitAll()

                // Role-Based Access Control (RBAC)
                .requestMatchers("/api/v1/admin/**").hasRole("ADMIN")
                .requestMatchers("/api/v1/orders/**").hasAnyRole("USER", "ADMIN")

                // Catch-all: any other endpoint requires a valid login
                .anyRequest().authenticated()
            )
            // Accept standard Bearer tokens
            .oauth2ResourceServer(oauth2 -> oauth2.jwt(Customizer.withDefaults()));

        return http.build();
    }
}
```

**Is this a bean?** **Yes** — the method returns a `SecurityFilterChain` bean. Spring reads it at boot, compiles your rules, and replaces the default lockdown behaviour.

⚠️ **Rules are evaluated top to bottom, FIRST MATCH WINS.** Unlike controller routing ([§W4.13](03-spring-web.md#w413-routing-does-declaration-order-matter)), **order matters enormously here** — and getting it backwards is the classic self-inflicted security hole:
```java
.anyRequest().authenticated()                            // ❌ matches everything…
.requestMatchers("/api/public/**").permitAll()           //    …so this is UNREACHABLE
```
✅ Always: **most specific first, `anyRequest()` last.** (Spring Security 6 actually fails fast on some unreachable-matcher cases, but don't rely on it.)

**The matcher and rule vocabulary:**

| Matcher | Matches |
|---|---|
| `.requestMatchers("/api/**")` | an Ant-style path |
| `.requestMatchers(HttpMethod.POST, "/api/orders")` | method **+** path — ✅ *read public, write protected* |
| `.requestMatchers(RegexRequestMatcher.regexMatcher("..."))` | a regex |
| `.securityMatcher(...)` | scopes the **whole chain** (see above) |

| Rule | Means |
|---|---|
| `.permitAll()` | open to everyone, including anonymous |
| `.authenticated()` | any logged-in user |
| `.denyAll()` | nobody — ✅ good for deliberately shutting off a legacy path |
| `.hasRole("ADMIN")` | authority **`ROLE_ADMIN`** (prefix added for you — [§S4.3](#s43-roles-authorities-and-the-role_-prefix-q36-q40)) |
| `.hasAnyRole("USER","ADMIN")` | any of them |
| `.hasAuthority("SCOPE_orders:read")` | ⚠️ **exact** string, no prefix added |
| `.anonymous()` | only NOT-logged-in users |
| `.access(new WebExpressionAuthorizationManager("..."))` | arbitrary SpEL |

### S4.3 Roles, authorities, and the `ROLE_` prefix [Q36, Q40]

> **Your question [Q36]:** *"is there any specific rule enforced by spring boot for any column name — for example must the role or authority column have `ROLE_` as the prefix?"*

**The column NAME is free. The VALUE convention is what matters.**

In Spring Security a **role** is a permission bucket that, by convention, is **stored with the `ROLE_` prefix**: `ROLE_ADMIN`, `ROLE_USER`. Spring then adds or omits that prefix depending on **which method you call**:

| You write | Spring looks for | Prefix behaviour |
|---|---|---|
| `.hasRole("ADMIN")` | `ROLE_ADMIN` | ⚠️ **prepends `ROLE_` implicitly** |
| `@PreAuthorize("hasRole('ADMIN')")` | `ROLE_ADMIN` | prepends |
| `@RolesAllowed("ADMIN")` | `ROLE_ADMIN` | prepends |
| `.hasAuthority("ROLE_ADMIN")` | `ROLE_ADMIN` | **exact match, no magic** |
| `@Secured("ROLE_ADMIN")` | `ROLE_ADMIN` | exact match — you must write the prefix |
| `.hasAuthority("orders:read")` | `orders:read` | exact match |

⚠️ **The catch, stated plainly:** if you store `ADMIN` in the database and write `.hasRole("ADMIN")`, Spring searches for `ROLE_ADMIN`, doesn't find it, and **authorization silently fails with a 403** — no error, no warning, no hint. This is the most common Spring Security bug in existence.

✅ **Two ways out. Pick one and be consistent:**
```java
// 1. Store the prefix in the database: "ROLE_ADMIN". Then hasRole("ADMIN") works.
// 2. Or add it at mapping time, so the DB can stay clean:
return roles.stream()
            .map(r -> new SimpleGrantedAuthority("ROLE_" + r))   // DB holds "ADMIN"
            .toList();
```
And if you genuinely can't use the prefix at all, change the default globally:
```java
@Bean
static GrantedAuthorityDefaults grantedAuthorityDefaults() {
    return new GrantedAuthorityDefaults("");     // ⚠️ must be static — needed very early in startup
}
```

💡 **[+] Roles vs authorities — the distinction worth adopting.** Mechanically they are the same thing: a `GrantedAuthority` is just a string. The convention is:
- **Role** = *who you are*, coarse — `ROLE_ADMIN`, `ROLE_MANAGER`
- **Authority / permission** = *what you may do*, fine — `orders:read`, `orders:cancel`

Real systems grow out of roles fast ("managers can refund up to ₹5000 but only in their own region"). ✅ **Assign permissions to roles, roles to users, and check permissions in code:**
```java
@PreAuthorize("hasAuthority('orders:cancel')")     // ✅ scales
@PreAuthorize("hasRole('MANAGER')")                // ⚠️ breaks the day a second role needs it
```
Changing who can cancel an order then becomes a data change, not a deployment.

### S4.4 Roles **and** permissions with enums, enforced by `requestMatchers`

> **Your note:** *"first we have to update the UserDetails entity to update the role from a plain string to include authority and role… `public enum Role { ADMIN(Set.of(PERMISSIONS.BOOKING_APPLICATION_READ, PERMISSIONS.BOOKING_APPLICATION_WRITE)), USER(Set.of(PERMISSIONS.BOOKING_APPLICATION_READ)) }` … in the filter chain we use request matchers for different endpoints to allow different permissions, and only allow if they have some role."*

Roles and permissions both end up as plain strings in `getAuthorities()`. The only difference is the naming convention: roles carry `ROLE_`, permissions don't ([§S4.3](#s43-roles-authorities-and-the-role_-prefix-q36-q40)).

```java
public enum Permission {
    BOOKING_READ("booking:read"),
    BOOKING_WRITE("booking:write");

    private final String value;
    Permission(String value) { this.value = value; }
    public String value() { return value; }
}

public enum Role {
    USER(Set.of(Permission.BOOKING_READ)),
    ADMIN(Set.of(Permission.BOOKING_READ, Permission.BOOKING_WRITE));

    private final Set<Permission> permissions;
    Role(Set<Permission> permissions) { this.permissions = permissions; }

    /** e.g. ADMIN → [booking:read, booking:write, ROLE_ADMIN] */
    public List<SimpleGrantedAuthority> authorities() {
        List<SimpleGrantedAuthority> list = new ArrayList<>();
        permissions.forEach(p -> list.add(new SimpleGrantedAuthority(p.value())));
        list.add(new SimpleGrantedAuthority("ROLE_" + name()));
        return list;
    }
}
```
⚠️ The source version did `stream()...collect(Collectors.toList())` and then `.add(...)`. That happens to work (today's `toList()` collector returns an `ArrayList`), but mutability isn't guaranteed by its contract, and with Java 16's `stream().toList()` the `.add` **throws** `UnsupportedOperationException`. Build a list you own, as above.

```java
@Entity
@Table(name = "app_users")
public class User implements UserDetails {
    // id, username, password …
    @Enumerated(EnumType.STRING)          // ✅ store "ADMIN", never the ordinal (reordering the enum would corrupt data)
    private Role role;

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() { return role.authorities(); }
}
```

```java
.authorizeHttpRequests(auth -> auth
    .requestMatchers("/api/auth/**").permitAll()
    .requestMatchers(HttpMethod.GET,    "/api/bookings/**").hasAuthority(Permission.BOOKING_READ.value())
    .requestMatchers(HttpMethod.POST,   "/api/bookings/**").hasAuthority(Permission.BOOKING_WRITE.value())
    .requestMatchers(HttpMethod.DELETE, "/api/bookings/**").hasAuthority(Permission.BOOKING_WRITE.value())
    .requestMatchers("/api/admin/**").hasRole(Role.ADMIN.name())          // looks for "ROLE_ADMIN"
    .anyRequest().authenticated())                                         // ✅ last
```

> **Your question:** *"but if we have hundreds of APIs, how do we handle this with request matchers? The filter chain will be huge."*
>
> That is exactly why **method security** exists ([§S4.5](#s45-programmatic--method-level-security-q34-q40)). Keep the URL rules coarse (public vs authenticated vs `/admin/**`) and put fine rules next to the code they protect: `@PreAuthorize("hasAuthority('booking:write')")`.
>
> 🔗 Enums in Java (they are full classes with fields and constructors, unlike Python's `Enum` values): [§J2](01-java.md#j2-the-java-essentials-you-will-hit-in-week-one-).

### S4.5 Programmatic / method-level security [Q34, Q40]

**B. Programmatic (method-level).** Instead of managing paths centrally, decorate individual methods in controllers **or service classes**. Activate it with `@EnableMethodSecurity`:

```java
@Configuration
@EnableWebSecurity
@EnableMethodSecurity(securedEnabled = true, jsr250Enabled = true)  // activates @Secured / @RolesAllowed
public class SecurityConfiguration { /* filterChain beans... */ }
```
*(`prePostEnabled = true` — which switches on `@PreAuthorize`/`@PostAuthorize` — is the **default** in Spring Security 6, so you only need the other two flags if you want the older annotation styles.)*

```java
@RestController
@RequestMapping("/api/v1/reports")
public class ReportController {

    @GetMapping("/summary")
    @PreAuthorize("hasRole('ADMIN') or hasAuthority('SCOPE_read')")
    public ResponseEntity<String> getAdminReport() {
        return ResponseEntity.ok("Highly sensitive corporate data");
    }
}
```

**How it works under the hood:** Spring uses **AOP** to wrap the bean in a **proxy**. Before the method body runs, the proxy reads the thread's `SecurityContext`; if the user lacks the role it throws **`AccessDeniedException`**. ✅ This strategy works for **gRPC service implementations too** — because it's AOP on a bean, not a servlet filter. That is the key to [§S7.2](#s72-securing-grpc-q34).

⚠️ **It's a proxy — so the self-invocation trap from [§C2.13](02-spring-core.md#c213-what-actually-happens-at-startup-the-mechanism) applies exactly.** Calling an `@PreAuthorize` method from *inside the same class* bypasses the proxy entirely and **the check silently doesn't run**.

#### `@Secured` vs `@RolesAllowed` vs `@PreAuthorize` [Q40]

| Annotation | Origin | `ROLE_` prefix | SpEL | Verdict |
|---|---|---|---|---|
| `@Secured("ROLE_ADMIN")` | Spring-specific | ⚠️ **you must write it** | ❌ | legacy |
| `@RolesAllowed("ADMIN")` | JSR-250 standard | ✅ added for you | ❌ | portable but limited |
| **`@PreAuthorize("...")`** | Spring | depends on the function used | ✅ **full SpEL** | ✅ **use this** |

```java
// A. @Secured — strict string matching. Fails if you pass just "ADMIN".
@GetMapping("/admin-dashboard")
@Secured("ROLE_ADMIN")
public ResponseEntity<String> getDashboard() { return ResponseEntity.ok("Welcome Admin"); }

// B. @RolesAllowed — the JSR-250 standard; appends ROLE_ behind the scenes.
@DeleteMapping("/delete-user/{id}")
@RolesAllowed("ADMIN")
public ResponseEntity<String> deleteUser(@PathVariable Long id) { return ResponseEntity.ok("User deleted"); }

// C. @PreAuthorize — SpEL, so it can read METHOD PARAMETERS. This is the real win.
@PutMapping("/update-profile/{userId}")
@PreAuthorize("hasRole('ADMIN') or #userId == authentication.principal.id")
// ONLY an admin OR the actual owner of the profile can modify this data
public ResponseEntity<String> updateProfile(@PathVariable Long userId) { return ResponseEntity.ok("Profile updated"); }
```

💡 **That third example is the point of the whole feature.** "Admin **or the owner**" is *not expressible* as a URL pattern, so no amount of central `authorizeHttpRequests` configuration can do it. This is where declarative and programmatic security divide cleanly:

| | Central (`authorizeHttpRequests`) | Method-level (`@PreAuthorize`) |
|---|---|---|
| Granularity | URL patterns | per method, with arguments |
| Visibility | ✅ one file, auditable at a glance | scattered — must grep |
| Can express ownership rules | ❌ | ✅ |
| Protects non-HTTP entry points (jobs, listeners, gRPC) | ❌ | ✅ |
| **Best practice** | ✅ **coarse-grained gate** | ✅ **fine-grained rules** — use **both** |

**The rest of the family:**
```java
@PostAuthorize("returnObject.ownerId == authentication.principal.id")  // checks the RESULT
@PreFilter("filterObject.ownerId == authentication.principal.id")      // filters an input collection
@PostFilter("filterObject.public or filterObject.ownerId == authentication.principal.id")  // filters the result
```
⚠️ `@PostAuthorize` and `@PostFilter` run **after** the method — so the work (and any DB write) already happened. Never use them on anything with side effects, and never use `@PostFilter` on a large result set: it filters **in memory**, after loading everything.

💡 **A cleaner idiom for complex rules** — move the expression into a bean so it's testable:
```java
@PreAuthorize("@orderSecurity.canCancel(#orderId, authentication)")
public void cancel(Long orderId) { ... }

@Component("orderSecurity")
public class OrderSecurity {
    public boolean canCancel(Long orderId, Authentication auth) { /* real Java, unit-testable */ }
}
```



### S4.6 Method security under the hood: interceptors, expression handler, `EvaluationContext`

> **Your questions:** *"what is method security? @PreAuthorize/@PostAuthorize run inside Spring MVC, unlike filters which run outside Spring MVC inside the servlet container [using AOP?]. What's their order — before or after other AOP? What is AuthorizationManagerBeforeMethodInterceptor — does it use the same AuthorizationManager as the last filter? … What's the use of MethodSecurityExpressionHandler? It takes the expression and using the EvaluationContext [what is it?]… Why the name 'method security' — only controller methods, or others? To enable we add @EnableMethodSecurity… what other expressions besides hasAuthority/hasRole/hasAnyRole, and on what field of UserDetails do they depend — I think the abstract method of UserDetailsService? Does anything change if @PreAuthorize is written above @PostMapping?"*

```
caller (DispatcherServlet, a @Scheduled job, a Kafka listener, another bean…)
   │  calls bookingService.getBooking(42)        ← actually calls the CGLIB/JDK PROXY
   ▼
AuthorizationManagerBeforeMethodInterceptor (order 200, @PreAuthorize)
   └─ PreAuthorizeAuthorizationManager.authorize(authSupplier, methodInvocation)
        └─ MethodSecurityExpressionHandler.createEvaluationContext(auth, invocation)
             root object: authentication, principal, hasRole(), hasAuthority(), …
             variables:   #id (method args), later returnObject / filterObject
        └─ SpEL evaluates "hasAuthority('booking:read')" → true / false
   ├─ false → AuthorizationDeniedException (an AccessDeniedException)
   ▼ true
(@Transactional interceptor — default order LOWEST_PRECEDENCE, so INSIDE security)
   ▼
real method body
   ▼
AuthorizationManagerAfterMethodInterceptor (order 500, @PostAuthorize) → PostAuthorizeAuthorizationManager
   (returnObject now available)
```

| Your question | Answer |
|---|---|
| "Runs inside Spring MVC, unlike filters?" | 📌 **Not tied to MVC at all.** It is **Spring AOP on any bean**: `@Service`, `@Repository`, `@Component`, gRPC services, and controllers too. For a controller call it happens to run inside `DispatcherServlet` (after the whole filter chain), but the same check fires when a scheduled job calls the service. ✅ Yes, it uses AOP proxies. |
| "Why the name method security?" | It secures **method invocations**, not URLs. ✅ It works on **any Spring-bean method**, and putting it on the **service layer** is best practice: every entry point (REST, gRPC, jobs, listeners) is covered. ⚠️ Proxy rules apply: self-invocation (`this.method()`) skips the check, and `private`/`final` methods can't be intercepted ([§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)). |
| "Order relative to other AOP?" | Each annotation has its own interceptor with a fixed order (`AuthorizationInterceptorsOrder`): `@PreFilter` 100, `@PreAuthorize` 200, `@Secured` 300, JSR-250 400, `@PostAuthorize` 500, `@PostFilter` 600. `@Transactional`/`@Cacheable` default to the lowest precedence, so **security wraps them**: `@PreAuthorize` denies *before* a transaction or cache is touched. ⚠️ The flip side: `@PostAuthorize` runs **after the transaction committed**, so denying then does *not* roll back a write. The docs say not to combine `@PostAuthorize` with DB writes (or to order `@EnableTransactionManagement` before `@EnableMethodSecurity` if you must). `@EnableMethodSecurity(offset = …)` shifts all security interceptors at once. |
| "Does `AuthorizationManagerBeforeMethodInterceptor` use the same AuthorizationManager as the last filter?" | **The same interface, different implementations.** `AuthorizationFilter` uses `RequestMatcherDelegatingAuthorizationManager` (for URLs); the method interceptors use `PreAuthorizeAuthorizationManager` / `PostAuthorizeAuthorizationManager` (for SpEL on methods). The *same* `Authentication` from `SecurityContextHolder` feeds both. |
| What is `MethodSecurityExpressionHandler`? | The factory that **parses the SpEL string** and **builds the `EvaluationContext`** for each call. Its default implementation adds `returnObject`/`filterObject` and the method-argument variables. You customise it (e.g. a `PermissionEvaluator` for `hasPermission(...)`, or a different role prefix) by exposing your own as a **`static` `@Bean`**. |
| What is `EvaluationContext`? | A SpEL "scope" built **per invocation**. The **root object** provides `authentication`, `principal` and the functions (`hasRole`, …). **Variables** hold the method arguments by name (`#bookingId`, `#user.email`), `returnObject` (post) and `filterObject` (filters). `@bean` references (`@orderSecurity.canCancel(...)`) resolve to Spring beans. |
| Which expressions exist? | `permitAll`, `denyAll`, `isAnonymous()`, `isAuthenticated()`, `isFullyAuthenticated()`, `isRememberMe()`, `hasRole`, `hasAnyRole`, `hasAuthority`, `hasAnyAuthority`, `hasPermission(target, perm)`, `principal`, `authentication`, `#arg`, `returnObject`, `filterObject`, `@beanName.method(...)`. Combine them with `and` / `or` / `not`. Recent versions also add `hasAllRoles` / `hasAllAuthorities` (listed in the 7.x docs). |
| "Which UserDetails field do hasRole/hasAuthority depend on — the abstract method of UserDetailsService?" | 📌 **Correction:** they read **`authentication.getAuthorities()`** from the `SecurityContext`. That collection was filled at **login** from your **`UserDetails.getAuthorities()`** (or, for JWT, from token claims in your filter). `UserDetailsService` is not consulted at check time; its only method is `loadUserByUsername`. |
| `#username` style argument names | They need the **parameter names at runtime**: compile with `-parameters` (Boot's Maven/Gradle plugins set it), or annotate the argument with `@P("username")` / Spring Data `@Param`. |
| "Does anything change if `@PreAuthorize` is above `@PostMapping`?" | **No.** Annotation order on a method is irrelevant; they're metadata read by reflection. |
| Enabling | `@EnableMethodSecurity` on any `@Configuration` class (or on the main class). `prePostEnabled` defaults to `true`. 🔖 **Boot 2.7 / Security 5.7:** `@EnableMethodSecurity` exists (since 5.6) and is the recommended one. Older code uses `@EnableGlobalMethodSecurity(prePostEnabled = true)`, where the flag defaults to **false**, so forgetting it silently disables every `@PreAuthorize`. |

### S4.7 `@PostAuthorize`, `@PreFilter`, `@PostFilter` in depth

> **Your questions:** *"@PostAuthorize uses AuthorizationManagerAfterMethodInterceptor → PostAuthorizeAuthorizationManager with the same EvaluationContext — what can we use in @PostAuthorize? How do I use a custom entity with nested fields — returnObject refers to the controller's return, then nested fields normally? How does it behave on an exception? When does it run, after the request completes? Use case for authorizing after the method? What are @PreFilter and @PostFilter (AOP too?), how are they different? Does @PreFilter filter the incoming parameter (only controllers?), does @PostFilter filter the returned list, and how does it work for non-list returns (scalar, boolean)? The rule: single object → @PostAuthorize, collection → @PostFilter? In @PostFilter, only objects which matched the condition will be removed from the response."*

**`@PostAuthorize`: when, what, why**
- **When:** right after **the method returns** to the proxy, before the value goes back to the caller. It does *not* run after the HTTP response is sent. The response is written later, by MVC.
- **What:** everything in `@PreAuthorize`, plus **`returnObject`** with normal SpEL navigation: `returnObject.owner.username == authentication.name`, `returnObject.customer.profile.email`, or the null-safe `returnObject?.owner?.id`. If the method returns `ResponseEntity<Booking>`, write `returnObject.body.owner…`.
- **Why:** **ownership checks you can only do after loading.** `GET /bookings/42`: the ID alone doesn't tell you who owns booking 42, so load it, then check. Doing it *before* would mean a second query.
- **On exception:** the method threw, so there is no return value. The after-interceptor **does not evaluate** and your original exception propagates (to `@ControllerAdvice`, or to `ExceptionTranslationFilter` if it's a security exception).
- ⚠️ Never on writes: the change already happened (and, per §S4.6, the transaction already committed).

```java
@PreAuthorize("hasAuthority('booking:read')")
@PostAuthorize("returnObject.ownerUsername == authentication.name or hasRole('ADMIN')")
public BookingResponse getBooking(Long id) { … }
```

**`@PreFilter` / `@PostFilter`: filtering, not allowing/denying**

| | `@PreAuthorize` / `@PostAuthorize` | `@PreFilter` / `@PostFilter` |
|---|---|---|
| Outcome | all-or-nothing: run, or `AccessDeniedException` (403) | **never denies**: silently drops elements |
| Variable | `#args`, `returnObject` | **`filterObject`** = the current element |
| Mechanism | AOP interceptors (orders 200/500) | AOP interceptors `PreFilterAuthorizationMethodInterceptor` (100) / `PostFilterAuthorizationMethodInterceptor` (600) |
| Where | any bean method | any bean method (not just controllers) |

```java
@PreFilter("filterObject.owner == authentication.name")     // keeps only the caller's own items from the ARGUMENT
public void bulkCancel(List<Booking> bookings) { … }

@PostFilter("filterObject.owner == authentication.name")    // keeps only the caller's own items in the RESULT
public List<Booking> findAll() { … }
```

- 📌 **Correction to your last sentence:** elements for which the expression is **true are KEPT**; those that evaluate to **false are removed**. Your sentence says the matching ones are removed, which is backwards.
- **Supported types** (docs, verified in `DefaultMethodSecurityExpressionHandler` source): **arrays, collections, maps, and streams** (while still open). For a `Map`, `filterObject` is the entry (`filterObject.value…`). A read-only collection gets a new filtered list returned instead of being mutated.
- **Several collection parameters?** Name the one to filter: `@PreFilter(value = "...", filterTarget = "bookings")`.
- **A scalar / single-object return** (`Booking`, `boolean`) under `@PostFilter` throws `IllegalArgumentException: Filter target must be a collection, array, map or stream type…`. ✅ So your rule is right: **single object → `@PostAuthorize`, collection → `@PostFilter`.**
- ⚠️ `@PostFilter` loads everything and then discards it **in memory**. On real tables, filter in the query (`findByOwner(username)`) and use `@PostFilter` only for small lists.

### S4.8 Graceful denial: `@HandleAuthorizationDenied`, `@AuthorizeReturnObject`, and clean 403 JSON

🔖 **Security 6.3+ (Boot 3.3+ and Boot 4). Not available on Boot 2.7.**

**1. Masking instead of failing: `@HandleAuthorizationDenied`.** By default a denied `@PreAuthorize`/`@PostAuthorize` throws `AuthorizationDeniedException` (a subclass of `AccessDeniedException`, 6.3+). A `MethodAuthorizationDeniedHandler` can **return a substitute value** instead:

```java
@Component
public class MaskingHandler implements MethodAuthorizationDeniedHandler {
    @Override   // called when @PreAuthorize denied (the method never ran)
    public Object handleDeniedInvocation(MethodInvocation invocation, AuthorizationResult result) {
        return "***";
    }
    // optional: handleDeniedInvocationResult(MethodInvocationResult, AuthorizationResult)
    //           for @PostAuthorize — you get the real value and can partially mask it
}
```

**2. Applying it to fields of a returned DTO: `@AuthorizeReturnObject`.** A DTO isn't a Spring bean, so annotations on its getters do nothing by themselves. `@AuthorizeReturnObject` tells Spring Security to **wrap the returned object in a proxy** so that its annotated getters *are* checked.

📌 **Correction to the source example:** `@AuthorizeReturnObject` goes on the **method (or class) that returns the object**, i.e. the service or repository. **Not on the DTO class.** On the DTO class it would mean "proxy whatever the DTO's own methods return". The docs' example puts it on `UserRepository.findByName(...)`, and warn that class-level use proxies *every* return value, including `String` and `Integer`.

```java
public class BookingResponse {                        // ⚠️ must be non-final (records are final) to get a class proxy
    private Long id;
    private String ownerUsername;
    private String paymentReference;
    // getters …

    @PreAuthorize("hasRole('ADMIN')")
    @HandleAuthorizationDenied(handlerClass = MaskingHandler.class)
    public String getPaymentReference() { return paymentReference; }   // non-admins see "***"
}

@Service
public class BookingService {
    @AuthorizeReturnObject                                        // ✅ HERE: proxy the returned BookingResponse
    @PreAuthorize("hasAuthority('booking:read')")
    @PostAuthorize("returnObject.ownerUsername == authentication.name or hasRole('ADMIN')")
    public BookingResponse getBooking(Long id) { … }

    @PreAuthorize("hasAuthority('booking:write')")                // ✅ check BEFORE writing
    public BookingResponse createBooking(BookingRequest req, String currentUser) { … }

    @PreAuthorize("hasRole('ADMIN') or @bookingSecurity.isOwner(#id, authentication.name)")
    public void deleteBooking(Long id) { … }
}
```
When Jackson serializes the proxied DTO, it calls `getPaymentReference()`, the check runs, and the JSON shows `"***"` for non-admins. Why the class must not be `final` (verified in `AuthorizationAdvisorProxyFactory`, Security 7.1.2; the reference docs don't spell it out):
- The factory calls `setProxyTargetClass(!Modifier.isFinal(...))`.
- A **non-final** class gets a CGLIB subclass proxy, which *is a* `BookingResponse` ([§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode)).
- A **final** class, which includes every **record**, can only get a JDK proxy of its interfaces. That proxy is not a `BookingResponse`, so code expecting the DTO type gets a `ClassCastException`.
- Collections, streams, arrays, `Optional`, iterators and map values are unwrapped, and their elements are proxied. Simple value types such as `String` and `Integer` are returned as-is.

**3. A clean JSON 403 for hard denials.** A method-security denial inside a controller call is thrown **inside MVC**, so `@RestControllerAdvice` can format it as an RFC 9457 `ProblemDetail`:

```java
@RestControllerAdvice
public class SecurityExceptionAdvice {
    @ExceptionHandler(AuthorizationDeniedException.class)        // 6.3+; use AccessDeniedException on older versions
    public ProblemDetail denied(AuthorizationDeniedException ex) {
        ProblemDetail pd = ProblemDetail.forStatusAndDetail(HttpStatus.FORBIDDEN,
                "You do not have permission to access this resource.");
        pd.setTitle("Access Denied");
        return pd;                                                // ResponseEntity not required: status comes from the ProblemDetail
    }
}
```
⚠️ Two caveats:
- This **swallows the exception before `ExceptionTranslationFilter`**, so an *anonymous* caller also gets 403 instead of 401 (§S1.5). Return 401 yourself when `authentication` is anonymous, or leave it to the filter.
- Denials from the **URL rules** (`authorizeHttpRequests`) and authentication failures happen in the **filter chain**, before MVC. They are formatted by `http.exceptionHandling(e -> e.authenticationEntryPoint(...).accessDeniedHandler(...))`, never by advice.

🔗 `ProblemDetail` and the global exception design: [§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling).

## S5. OAuth2: login with Google/GitHub vs resource server

### S5.1 Two different things both called "OAuth2"

> **Your notes:** *"when we have the OAuth2 dependency it gives us a new filter, OAuth2LoginAuthenticationFilter, which we register in the chain (same @Configuration as basic auth, but oauth2Login(Customizer.withDefaults()) instead of httpBasic). To enable it we provide a ClientRegistrationRepository so our app can give client id and secret to the authorization server and request tokens on the user's behalf — configured in application.properties/yaml."*

Spring Security plays **two separate roles** in OAuth2. Pick the one your app is.

| | **OAuth2 Client / Login**, `oauth2Login()` | **Resource Server**, `oauth2ResourceServer()` |
|---|---|---|
| Your app is… | the website users log in to ("Sign in with Google") | an API that receives `Bearer` tokens issued by someone else |
| Starter (Boot 3) | `spring-boot-starter-oauth2-client` | `spring-boot-starter-oauth2-resource-server` |
| Starter (Boot 4) | 🔖 `spring-boot-starter-security-oauth2-client` (the old name still exists, marked deprecated) | 🔖 `spring-boot-starter-security-oauth2-resource-server` |
| Filters added | `OAuth2AuthorizationRequestRedirectFilter` (redirects to Google) + **`OAuth2LoginAuthenticationFilter`** (handles the callback) | **`BearerTokenAuthenticationFilter`** |
| Result | an `HttpSession` holding `OAuth2AuthenticationToken` | a stateless `JwtAuthenticationToken` per request |
| Typical client | server-rendered app, BFF | SPA / mobile app / other services |

(Boot 4 starter names verified in the spring-boot `starter/` directory; the old `spring-boot-starter-oauth2-client` describes itself as *"deprecated in favor of spring-boot-starter-security-oauth2-client"*.)

✅ Your notes describe the **login** role, and they're right: `oauth2Login(...)` replaces `httpBasic(...)` in the same config class.

**`ClientRegistrationRepository`:**
- 📌 You don't implement it yourself in Boot. Boot reads `spring.security.oauth2.client.registration.*` and **registers an `InMemoryClientRegistrationRepository` bean** for you.
- With a `SecurityFilterChain` of its own, Boot also enables `oauth2Login()`.
- For Google, GitHub, Facebook, X and Okta, only `client-id` and `client-secret` are needed. `CommonOAuth2Provider` fills in the URLs, because the registration id (`google`) matches its enum.

```yaml
spring:
  security:
    oauth2:
      client:
        registration:
          google:
            client-id: ${GOOGLE_CLIENT_ID}            # ✅ from env/secret store
            client-secret: ${GOOGLE_CLIENT_SECRET}
            scope: openid, profile, email
```

### S5.2 The `oauth2Login()` flow, step by step

> **Your note:** *"the complete flow: OAuth2LoginAuthenticationFilter → AuthenticationManager → AuthenticationProvider (oAuthLoginAuthenticationProvider) which uses DefaultOAuth2UserService (an implementation of Spring's UserDetailsService) … after authentication Spring stores the authentication object inside OAuth2AuthenticationToken in the SecurityContextHolder."*

```
Browser          Your app (Spring)                                             Google
   │ GET /orders (anonymous)
   │──────────────▶ AuthorizationFilter denies → ExceptionTranslationFilter → entry point
   │◀── 302 /oauth2/authorization/google
   │──────────────▶ OAuth2AuthorizationRequestRedirectFilter: build state (+PKCE), save in session
   │◀── 302 https://accounts.google.com/o/oauth2/v2/auth?client_id=…&state=…&redirect_uri=…/login/oauth2/code/google
   │─────────────────────────────────────────────────────────────────────────▶ user logs in, consents
   │◀──────────────────────────────── 302 /login/oauth2/code/google?code=XYZ&state=…
   │──────────────▶ OAuth2LoginAuthenticationFilter (matches /login/oauth2/code/*)
   │                  → AuthenticationManager → ProviderManager
   │                     → OidcAuthorizationCodeAuthenticationProvider ('openid' scope)
   │                         (OAuth2LoginAuthenticationProvider returns null for OIDC → §S2.2's null rule)
   │                     → back-channel: POST code → Google token endpoint ──────▶ id_token + access_token
   │                     → verify the ID token; OidcUserService loads the user (userinfo if needed) ─▶
   │                  → OAuth2AuthenticationToken(principal = OidcUser, authorities)
   │                  → SecurityContext saved in the HttpSession; tokens saved in OAuth2AuthorizedClientService
   │◀── 302 /orders  (now authenticated, JSESSIONID cookie)
```

| Your note | Precise version |
|---|---|
| "oAuthLoginAuthenticationProvider" | `OAuth2LoginAuthenticationProvider` for plain OAuth2 (GitHub); **`OidcAuthorizationCodeAuthenticationProvider`** when the `openid` scope is present (Google, Okta) |
| "DefaultOAuth2UserService (an implementation of UserDetailsService)" | 📌 It implements **`OAuth2UserService<OAuth2UserRequest, OAuth2User>`**, the OAuth2 *analogue* of `UserDetailsService`, not that interface. For OIDC it is **`OidcUserService`**. It loads user attributes from the provider's userinfo endpoint (or the ID token), not from your DB. |
| "stores the authentication object inside OAuth2AuthenticationToken" | ✅ The `Authentication` **is** an `OAuth2AuthenticationToken`. Its principal is an `OAuth2User` / `OidcUser` (attributes like `email`, `name`, `sub`). It is saved **in the session**, so `oauth2Login` is stateful by default. |
| Callback URL | default `{baseUrl}/login/oauth2/code/{registrationId}`. It must be registered exactly in Google's console. |

### S5.3 "Does Spring create a DB table for users, like Supabase?" — no; just-in-time provisioning

> **Your question:** *"does it create any db in our application to store user details? With Supabase + FastAPI + Google OAuth the user details end up in Supabase — so does Spring Boot create some table to store the user details or not?"*

**No.**
- Supabase is a backend *platform* that bundles an identity store (`auth.users`). Spring Security is a *framework*: after login it keeps the `OidcUser` **in the session only**.
- By default nothing is written to any database, and when the session expires the user is forgotten.
- One nuance: the provider's **access/refresh tokens** go to `OAuth2AuthorizedClientService`, which is in-memory by default. Spring ships `JdbcOAuth2AuthorizedClientService` plus a schema file (`oauth2-client-schema.sql`) if you want them persisted. That table holds *tokens*, not your user profiles.

**To keep your own user rows** (to attach orders and app roles), do **just-in-time provisioning**: wrap the user service and upsert on every login.

```java
@Service
public class ProvisioningOidcUserService extends OidcUserService {
    private final UserRepository users;
    public ProvisioningOidcUserService(UserRepository users) { this.users = users; }

    @Override
    @Transactional
    public OidcUser loadUser(OidcUserRequest req) throws OAuth2AuthenticationException {
        OidcUser google = super.loadUser(req);                       // Spring does the Google part

        String issuer = google.getIssuer().toString();
        String subject = google.getSubject();                         // ✅ key on (issuer, sub): stable, unique
        AppUser user = users.findByIssuerAndSubject(issuer, subject)  //    (email can change or be re-used)
                .orElseGet(() -> users.save(AppUser.newFromOidc(issuer, subject,
                                                                 google.getEmail(), google.getFullName())));

        Set<GrantedAuthority> authorities = new HashSet<>(google.getAuthorities());
        authorities.addAll(user.getRole().authorities());           // ✅ add YOUR app's roles (§S4.4)
        return new DefaultOidcUser(authorities, google.getIdToken(), google.getUserInfo());
    }
}
```
```java
http.oauth2Login(o -> o.userInfoEndpoint(u -> u.oidcUserService(provisioningOidcUserService)));
// GitHub (plain OAuth2, no 'openid'): extend DefaultOAuth2UserService and use .userService(...)
```

⚠️ Change from the source: it keyed users by **email**. Use the OIDC **`sub` + issuer**. Emails change, and an unverified-email provider can let someone claim another person's account. If you must link by email, require `email_verified == true`.

### S5.4 Hybrid: log in with Google, then issue *your own* JWT to a SPA

With a decoupled SPA or mobile app you may want Google to authenticate the user once, and then your API to work statelessly with your own JWT (§S3.2). Plug a success handler into `oauth2Login`:

```java
@Component
public class OAuth2LoginSuccessHandler implements AuthenticationSuccessHandler {
    private final JwtUtil jwtUtil;
    private final UserDetailsService uds;
    private final RefreshTokenService refreshTokens;
    private final UserRepository users;
    // constructor …

    @Override
    public void onAuthenticationSuccess(HttpServletRequest req, HttpServletResponse res, Authentication auth)
            throws IOException {
        OidcUser oidc = (OidcUser) auth.getPrincipal();
        AppUser user = users.findByIssuerAndSubject(oidc.getIssuer().toString(), oidc.getSubject()).orElseThrow();

        // ✅ refresh token in an HttpOnly cookie; the SPA calls /api/auth/refresh to get an access token
        ResponseCookie cookie = ResponseCookie.from("refresh_token", refreshTokens.issue(user))
                .httpOnly(true).secure(true).sameSite("Strict").path("/api/auth").maxAge(Duration.ofDays(7)).build();
        res.addHeader(HttpHeaders.SET_COOKIE, cookie.toString());
        req.getSession(false).invalidate();                        // the temporary OAuth2 session is no longer needed
        res.sendRedirect("https://app.example.com/login/callback");
    }
}
```
```java
http
  .sessionManagement(s -> s.sessionCreationPolicy(SessionCreationPolicy.IF_REQUIRED)) // a session is needed for the
                                                                                      // OAuth2 redirect round-trip (state)
  .authorizeHttpRequests(a -> a
      .requestMatchers("/oauth2/**", "/login/oauth2/**", "/api/auth/**").permitAll()
      .anyRequest().authenticated())
  .oauth2Login(o -> o.userInfoEndpoint(u -> u.oidcUserService(provisioningOidcUserService))
                     .successHandler(oAuth2LoginSuccessHandler))
  .addFilterBefore(new JwtFilter(jwtUtil), UsernamePasswordAuthenticationFilter.class);
```

⚠️ **The source put the JWT in the redirect URL** (`…/callback?token=eyJ…`). URLs end up in browser history, server and proxy logs, and the `Referer` header sent to third parties, so the token leaks. Use the HttpOnly cookie plus `/refresh` pattern above, or a one-time short-lived code that the SPA exchanges via `POST`.

### S5.5 Pure resource server: `oauth2ResourceServer()` and mapping roles

If users log in **at an external identity provider** (Keycloak, Auth0, Okta, Cognito, Entra ID) and the SPA sends you that provider's JWT, you need **none** of `JwtUtil`, `JwtFilter` or the login controller:

```yaml
spring:
  security:
    oauth2:
      resourceserver:
        jwt:
          issuer-uri: https://login.example.com/realms/main   # Spring discovers jwks_uri via OIDC discovery
```
```java
http
  .csrf(AbstractHttpConfigurer::disable)
  .sessionManagement(s -> s.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
  .authorizeHttpRequests(a -> a.requestMatchers("/api/public/**").permitAll().anyRequest().authenticated())
  .oauth2ResourceServer(o -> o.jwt(Customizer.withDefaults()));   // adds BearerTokenAuthenticationFilter
```
Spring does the following for you:
- fetches and caches the **JWKS public keys**, picking the key by `kid`, so key rotation is handled;
- verifies the signature, `exp`/`nbf` and the issuer (`aud` if you configure it);
- puts a `JwtAuthenticationToken` in the context.

**Authorities:** by default it maps the `scope` / `scp` claim to `SCOPE_read`, `SCOPE_write`, …. If your provider puts roles in a custom claim:

```java
@Bean
JwtAuthenticationConverter jwtAuthenticationConverter() {
    JwtGrantedAuthoritiesConverter roles = new JwtGrantedAuthoritiesConverter();
    roles.setAuthoritiesClaimName("roles");     // read "roles": ["ADMIN","USER"]
    roles.setAuthorityPrefix("ROLE_");          // → ROLE_ADMIN, so hasRole('ADMIN') works
    JwtAuthenticationConverter c = new JwtAuthenticationConverter();
    c.setJwtGrantedAuthoritiesConverter(roles);
    return c;                                   // Boot picks this bean up for .jwt(withDefaults())
}
```
⚠️ Keycloak nests roles (`realm_access.roles`), which `setAuthoritiesClaimName` can't reach. Write a small `Converter<Jwt, Collection<GrantedAuthority>>` for that.

| | Own JWT (§S3) | Resource server (§S5.5) |
|---|---|---|
| Who issues tokens | you | external IdP |
| Code you own | `JwtUtil`, filter, login, refresh | ~5 lines of config |
| Key handling | your secret / your key pair | JWKS fetched and rotated automatically |
| Revocation / MFA / social login | you build it | the IdP provides it |

✅ Default to the **resource server** whenever an identity provider exists. Hand-rolled JWT is for small or self-contained systems.


## S6. CSRF and CORS

### S6.1 CSRF [Q34]

> **Your question:** *"how does spring protect from cross site request forgery (CSRF)? are they used for api server application or web server [i think csrf only happens for web server]?"*

**Your instinct is correct.**

**What CSRF is:** a malicious site tricks a logged-in user's browser into performing an unwanted action on a trusted site — exploiting the fact that **browsers attach cookies automatically** to any request to that origin.
```html
<!-- On evil.com. The victim's bank cookie rides along automatically. -->
<form action="https://bank.com/transfer" method="POST">
  <input type="hidden" name="to" value="attacker"><input type="hidden" name="amount" value="10000">
</form><script>document.forms[0].submit()</script>
```

| | **Web server** (sessions + cookies) | **API server** (stateless, Bearer tokens) |
|---|---|---|
| Auth carried in | a **cookie**, sent automatically | an `Authorization` **header**, sent only by your own JS |
| Vulnerable to CSRF | ✅ **yes — protection is mandatory** | ❌ **no — the attacker's page cannot set a custom header** |
| Spring default | ✅ **enabled** | you disable it |

**For server-rendered HTML (Thymeleaf/JSP):** Spring Security enables CSRF by default and injects a unique token into every form. Thymeleaf's `th:action` adds the hidden field automatically ([§W11.4](03-spring-web.md#w114--configuration-and-production-gotchas)), which is why it "just works."
```html
<!-- generated for you -->
<input type="hidden" name="_csrf" value="a4f8...-..."/>
```

**For a stateless API consumed by a SPA or mobile client with Bearer tokens:** CSRF attacks are **technically impossible**, because browsers do not attach custom `Authorization` headers automatically. So you explicitly disable it:
```java
.csrf(csrf -> csrf.disable())
```

> ⚠️ **[+] The critical nuance the source answer skipped, because getting this wrong is a real vulnerability:**
>
> **"REST API" does not mean "CSRF-safe." "Not using cookies" does.**
>
> If your SPA authenticates with a **session cookie** or a **JWT stored in a cookie** — which many teams do, because `HttpOnly` cookies resist XSS better than `localStorage` — then **you are cookie-authenticated and CSRF applies in full**, JSON endpoints included. Disabling CSRF there is a genuine hole.
>
> **The decision rule:**
> ```
> Is the credential sent automatically by the browser (i.e. a cookie)?
>     YES → CSRF protection REQUIRED, even for a pure-JSON API
>     NO  (Authorization header set by your own code) → safe to disable
> ```
> For the cookie case, use the SPA-friendly configuration rather than switching it off:
> ```java
> .csrf(csrf -> csrf
>     .csrfTokenRepository(CookieCsrfTokenRepository.withHttpOnlyFalse())  // JS reads XSRF-TOKEN
>     .csrfTokenRequestHandler(new SpaCsrfTokenRequestHandler()))          // sends X-XSRF-TOKEN back
> ```
> Add `SameSite=Lax` (Spring Boot's default for the session cookie) as defence in depth — it blocks most cross-site cookie sends, but it is **not** a complete substitute.
>
> 💡 CSRF only applies to **state-changing** methods. Spring ignores `GET`, `HEAD`, `OPTIONS`, `TRACE` — which is exactly why a `GET` endpoint must never modify state.



### S6.2 CORS when Spring Security is on the classpath

🔗 **CORS itself** (what a preflight is, `@CrossOrigin` vs `CorsFilter` vs `WebMvcConfigurer`, how global and per-controller rules *combine*) is covered in depth in [§W9](03-spring-web.md#w9-cors-crossorigin-corsfilter-and-spring-security). This section covers only what Security changes.

**The problem.** A browser's preflight `OPTIONS` request carries **no credentials** (no cookie, no `Authorization` header). If Spring Security sees it first, the request looks anonymous and gets **401/403**. The browser then reports a "CORS error" and the real request is never sent. The docs: *"CORS must be processed before Spring Security, because the pre-flight request does not contain any cookies."* `@CrossOrigin` alone can't help, because it runs inside Spring MVC, *after* the security chain.

**The fix: let Security's `CorsFilter` handle it** (position #5 in [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34), before any authentication):

```java
@Bean
SecurityFilterChain chain(HttpSecurity http, JwtUtil jwtUtil) throws Exception {
    return http
        .cors(Customizer.withDefaults())          // uses the CorsConfigurationSource bean below
        .csrf(AbstractHttpConfigurer::disable)
        .sessionManagement(s -> s.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
        .authorizeHttpRequests(a -> a.requestMatchers("/api/auth/**").permitAll().anyRequest().authenticated())
        .addFilterBefore(new JwtFilter(jwtUtil), UsernamePasswordAuthenticationFilter.class)
        .build();
}

@Bean
UrlBasedCorsConfigurationSource corsConfigurationSource(@Value("${app.cors.allowed-origins}") List<String> origins) {
    CorsConfiguration c = new CorsConfiguration();
    c.setAllowedOrigins(origins);                                   // ✅ from config, e.g. http://localhost:3000
    c.setAllowedMethods(List.of("GET", "POST", "PUT", "PATCH", "DELETE", "OPTIONS"));
    c.setAllowedHeaders(List.of("Authorization", "Content-Type")); // ✅ REQUIRED for a JS-set Bearer header
    c.setAllowCredentials(true);                                    // only if the browser must send COOKIES
    c.setMaxAge(3600L);                                             // cache the preflight for an hour
    UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
    source.registerCorsConfiguration("/**", c);
    return source;
}
```

**Which configuration does `.cors(withDefaults())` use?** (Security 7 docs)
1. If there is a **`CorsConfigurationSource` bean** (e.g. the `UrlBasedCorsConfigurationSource` above), it uses that. The 7.x docs add that Security will *"automatically configure CORS only if a `UrlBasedCorsConfigurationSource` instance is present"*.
2. Otherwise, if Spring MVC is on the classpath, it reuses **Spring MVC's CORS configuration** (`WebMvcConfigurer.addCorsMappings` and `@CrossOrigin`).
3. With **several** `CorsConfigurationSource` beans, nothing is auto-configured. Pass one per chain: `.cors(c -> c.configurationSource(apiSource()))`.

📌 This clears up a mix-up in the source answers. A `UrlBasedCorsConfigurationSource` bean is a **separate, central** configuration: it does **not** read your `@CrossOrigin` annotations. Only option 2 (no source bean) bridges to MVC's settings. Pick one place, and ✅ prefer the central bean for APIs.

**Pitfalls:**

| Pitfall | Truth |
|---|---|
| `allowCredentials(true)` + `allowedOrigins("*")` | Rejected: Spring throws `IllegalArgumentException` when the config is used (browsers also forbid it). Use explicit origins, or `setAllowedOriginPatterns(List.of("https://*.example.com"))`. |
| "`allowCredentials` is required to send the Authorization header" | ❌ It's needed for **cookies** (and browser-managed HTTP auth / client certs). A header your JS sets with `fetch` needs `Authorization` in **`allowedHeaders`**; `credentials: 'include'` + `allowCredentials` is only for cookies. |
| `.requestMatchers(HttpMethod.OPTIONS, "/**").permitAll()` | Harmless but normally **redundant**: Security's `CorsFilter` answers valid preflights itself and stops the chain before authorization. Without `.cors(...)` it "fixes" preflights while leaving the real responses without CORS headers. |
| JWT filter returns 401 when the header is missing | ⚠️ Breaks preflights and `permitAll` paths. A JWT filter must just call `chain.doFilter` when there's no token (§S3.2). |
| Hardcoded `localhost:3000` | Externalize: `app.cors.allowed-origins` per profile ([§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12)). |

## S7. Configuration, debugging, gRPC and docs endpoints

### S7.1 Configuration properties and debugging [Q34, Q38]

> **Your question [Q34]:** *"do we need to make changes in the application.properties file for this? if these, list all the common variables used for this."*

Routing and business rules live in Java beans; **global settings** live in properties:
```properties
# The default single user, when no UserDetailsService exists yet.
# ⚠️ Declaring these REPLACES the random generated password.
spring.security.user.name=admin
spring.security.user.password=super-secret-temporary-password
spring.security.user.roles=ADMIN

# OAuth2 / JWT resource server — where to fetch public keys to validate Bearer tokens
spring.security.oauth2.resourceserver.jwt.issuer-uri=https://your-auth-domain.com
spring.security.oauth2.resourceserver.jwt.jwk-set-uri=https://your-auth-domain.com/.well-known/jwks.json

# OAuth2 login (social / SSO)
spring.security.oauth2.client.registration.google.client-id=${GOOGLE_CLIENT_ID}
spring.security.oauth2.client.registration.google.client-secret=${GOOGLE_CLIENT_SECRET}

# Session cookie hardening (for the cookie-based case)
server.servlet.session.cookie.http-only=true
server.servlet.session.cookie.secure=true
server.servlet.session.cookie.same-site=lax
server.servlet.session.timeout=30m
```
⚠️ Only the trivial cases are properties. **Path rules, roles, filter order and CSRF are Java-only** — unlike FastAPI where nearly everything is code anyway, so this will feel natural.

#### Fine-grained logging [Q38]

> **Your question:** *"we can toggle the log for spring security to debug using application.properties? also i noticed there are various types of logs — spring boot root logs, spring security logs, jpa logs — and we can manage the level individually i.e. application at INFO and spring security at DEBUG at the same time."*

**Exactly right.** Spring Boot uses **Logback**, and log levels are set **per package**, so you can keep the system quiet while one subsystem shouts.

```properties
# 1. Global level — keeps normal output clean
logging.level.root=INFO

# 2. ⭐ Spring Security — prints every filter execution, role check and short-circuit.
#    THIS is how you debug a mysterious 401/403.
logging.level.org.springframework.security=DEBUG

# 3. JPA / Hibernate — the exact parameterized SQL
logging.level.org.hibernate.SQL=DEBUG

# 4. The bound parameter VALUES inside those queries (Hibernate 6 / Boot 3)
logging.level.org.hibernate.orm.jdbc.bind=TRACE
```

> 📌 **On Spring Boot 3 the bind-parameter logger is `org.hibernate.orm.jdbc.bind`.** Boot 3 ships Hibernate 6, which renamed that package. This is worth pinning because a logger name that no longer exists is **not an error** — it silently does nothing, and you sit there wondering why parameter values never appear.

**More you'll want:**
```properties
logging.level.org.springframework.web=DEBUG              # MVC dispatch
logging.level.org.springframework.web.filter.CommonsRequestLoggingFilter=DEBUG
logging.level.com.yourcompany=DEBUG                      # just your own code
logging.level.org.springframework.boot.autoconfigure=DEBUG
debug=true                                               # the full auto-configuration report
```
⚠️ **`org.springframework.security=DEBUG` and `org.hibernate.orm.jdbc.bind=TRACE` log credentials and personal data.** Never in production. Put them in `application-local.yml` only.

💡 **[+] The single most useful line in the whole security debug output** is the startup banner listing your filter chain in order:
```
Will secure any request with [
  DisableEncodeUrlFilter, WebAsyncManagerIntegrationFilter, SecurityContextHolderFilter,
  HeaderWriterFilter, CorsFilter, LogoutFilter, ManualJwtAuthenticationFilter,
  UsernamePasswordAuthenticationFilter, ..., AuthorizationFilter]
```
If your custom filter isn't in that list, it isn't running — and that one glance answers most "my filter never executes" questions.

### S7.2 Securing gRPC [Q34]

> **Your questions:** *"is it the same way for doing grpc as well? how did it get implemented using servlet — is this also applicable to grpc or will this only work for http rest? can we use this for all types of protocol i.e. grpc, rest api?"*

**Not out of the box with standard HTTP filters.** Spring Security's servlet filters depend on the **Jakarta Servlet API** (`HttpServletRequest`/`HttpServletResponse`). Native gRPC runs on a **completely separate runtime**: raw **HTTP/2 frames** over **Netty**, with no servlet anywhere. **There is no `HttpServletRequest` to filter.**

```
REST            socket → Tomcat → HttpServletRequest → FILTER CHAIN ✅ → DispatcherServlet → controller
gRPC            socket → Netty  → HTTP/2 frames → ServerInterceptor ⚠️ → generated stub → service impl
                                                   ^^^^^^^^^^^^^^^^^ the gRPC equivalent
```

**Three paths:**

**1. `ServerInterceptor` — the native answer.** In a pure gRPC microservice you replace the global servlet filter with a `ServerInterceptor` that reads gRPC **Metadata** (the gRPC equivalent of headers) and establishes the security context by hand:
```java
public class JwtServerInterceptor implements ServerInterceptor {
    private static final Metadata.Key<String> AUTH =
            Metadata.Key.of("authorization", Metadata.ASCII_STRING_MARSHALLER);

    @Override
    public <ReqT, RespT> ServerCall.Listener<ReqT> interceptCall(
            ServerCall<ReqT, RespT> call, Metadata headers, ServerCallHandler<ReqT, RespT> next) {

        String token = headers.get(AUTH);
        if (token == null || !token.startsWith("Bearer ")) {
            call.close(Status.UNAUTHENTICATED.withDescription("Missing bearer token"), new Metadata());
            return new ServerCall.Listener<>() {};      // short-circuit — same idea as a filter
        }
        Authentication auth = validateAndBuild(token.substring(7));
        SecurityContext ctx = SecurityContextHolder.createEmptyContext();
        ctx.setAuthentication(auth);
        SecurityContextHolder.setContext(ctx);
        try {
            return next.startCall(call, headers);
        } finally {
            SecurityContextHolder.clearContext();       // ⚠️ MUST clear — the thread is reused
        }
    }
}
```
⚠️ **The hard part is context propagation.** gRPC hands work between threads, so a plain `ThreadLocal` `SecurityContext` can be lost. Use gRPC's `Context` together with `Contexts.interceptCall(...)`, or `DelegatingSecurityContextExecutor`.

**2. Spring gRPC support.** You can run a gRPC server inside a servlet-compatible environment (gRPC's servlet transport); the server translates gRPC calls into structures Spring Security can parse, and the ordinary filter chain applies.

**3. ✅ Method security — the portable answer.** Because `@PreAuthorize` is **AOP on a bean**, not a servlet filter, it works identically on a gRPC service implementation:
```java
@GrpcService
public class OrderGrpcService extends OrderServiceGrpc.OrderServiceImplBase {
    @Override
    @PreAuthorize("hasAuthority('orders:read')")        // ✅ works — AOP, not servlets
    public void getOrder(GetOrderRequest req, StreamObserver<Order> obs) { ... }
}
```

> 💡 **The summary to remember:** **authentication** is transport-specific (filter for HTTP, interceptor for gRPC); **authorization** is transport-agnostic (`@PreAuthorize` everywhere). Put your auth rules in the **service layer** with method security and they hold no matter which protocol calls in. For a gateway that speaks both — such as an API gateway — that's not a nicety, it's the only way to avoid writing your rules twice.

### S7.3 [+] Securing the docs endpoint [Q33]

> **Your question [Q33]:** *"how to secure the /developer-portal path so only authenticated developers can access your API metrics dashboard"*

```java
@Bean
public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
    return http
        .authorizeHttpRequests(auth -> auth
            // Lock the docs to a role — both the UI and the raw spec
            .requestMatchers("/developer-portal/**", "/v3/api-docs/**", "/swagger-ui/**")
                .hasRole("DEVELOPER")
            .requestMatchers("/actuator/health", "/actuator/info").permitAll()
            .requestMatchers("/actuator/**").hasRole("OPS")
            .anyRequest().authenticated())
        .httpBasic(Customizer.withDefaults())
        .build();
}
```
⚠️ **Lock the raw `/v3/api-docs` too, not just the UI.** Securing only `/swagger-ui/**` leaves the complete API surface — every path, parameter and schema — readable by anyone. That's a reconnaissance gift, and it's the mistake almost everyone makes.

✅ **Best of all: don't ship the docs to production.** `springdoc.api-docs.enabled=false` in `application-prod.yml` ([§W12.4](03-spring-web.md#w124-customizing-the-paths-q32)) and publish the spec to an internal portal from CI instead.

### S7.4 Your Q34 checklist — where each sub-question is answered

| Your sub-question | Answered in |
|---|---|
| How to secure a Spring Boot REST API | [§S1.1](#s11-the-mental-shift-from-fastapi), [§S4.2](#s42-declarative-security--the-central-configuration-q34) |
| Is it the same for gRPC? / all protocols? | [§S7.2](#s72-securing-grpc-q34) |
| Protect URLs by role (RBAC) | [§S4.2](#s42-declarative-security--the-central-configuration-q34), [§S4.3](#s43-roles-authorities-and-the-role_-prefix-q36-q40) |
| Does Boot hash/salt/pepper passwords automatically? | [§S2.6](#s26-passwords-hashing-salting-and-the-bcrypt-migration-q34-q37-q14) |
| How it's implemented with servlets | [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34) |
| Declarative vs programmatic | [§S4.2](#s42-declarative-security--the-central-configuration-q34), [§S4.5](#s45-programmatic--method-level-security-q34-q40) |
| Pre-process / post-process per request | [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34) |
| Can the filter reject requests? | [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34) — yes, by not calling `doFilter` |
| What security functionality is provided | [§S1.1](#s11-the-mental-shift-from-fastapi) (defaults), [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34) (the filter table) |
| Do we write the code or is it automatic? | [§S1.1](#s11-the-mental-shift-from-fastapi) |
| The request/response cycle with security | [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34) |
| `application.properties` variables | [§S7.1](#s71-configuration-properties-and-debugging-q34-q38) |
| In-memory / JDBC / LDAP / custom | [§S2.4](#s24-where-users-come-from-the-four-strategies-q34-q36) |
| Split endpoints into public and authenticated (like FastAPI) | [§S2.1](#s21-enablewebsecurity-and-the-securityfilterchain-bean-q35) (multiple chains), [§S4.2](#s42-declarative-security--the-central-configuration-q34) (`permitAll`) |
| What is the security configuration class? Is it a bean? | [§S2.1](#s21-enablewebsecurity-and-the-securityfilterchain-bean-q35) |
| Basic or Bearer by default? | [§S1.1](#s11-the-mental-shift-from-fastapi) |
| Like interceptors / Express / FastAPI middleware? | [§S1.2](#s12-the-architecture-the-servlet-filter-chain-q34) |
| Checks per controller or centrally? | [§S4.5](#s45-programmatic--method-level-security-q34-q40) — both, deliberately |
| CSRF — API server or web server? | [§S6.1](#s61-csrf-q34) |

---

### S7.5 Your security-tutorial notes — where each question is answered

| Your note / question | Answered in |
|---|---|
| DelegatingFilterProxy, "BeanFilter", FilterChainProxy, SecurityFilterChain — are they beans? | [§S1.3](#s13-your-architecture-notes-checked-delegatingfilterproxy--filterchainproxy--securityfilterchain--filters) |
| Default "form" security with user `user` + generated password | [§S1.1](#s11-the-mental-shift-from-fastapi), [§S1.3](#s13-your-architecture-notes-checked-delegatingfilterproxy--filterchainproxy--securityfilterchain--filters) |
| Providers per mechanism, AuthenticationManager / ProviderManager / `supports()` | [§S2.2](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder) |
| UserDetailsService for NoSQL? | [§S2.2](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder), [§S2.4](#s24-where-users-come-from-the-four-strategies-q34-q36) |
| PasswordEncoder: encrypt, decrypt or re-hash? | [§S2.2](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder), [§S2.6](#s26-passwords-hashing-salting-and-the-bcrypt-migration-q34-q37-q14) |
| Authentication object, SecurityContext, SecurityContextHolder, "Principal" | [§S2.2](#s22-the-authentication-engine-authenticationmanager--providermanager--authenticationprovider--userdetailsservice--passwordencoder) |
| SecurityContextHolderFilter — not re-authenticating every request | [§S1.4](#s14-securitycontextholderfilter--remembering-the-user-between-requests) |
| Wrong password; ExceptionTranslationFilter scope; is `@ControllerAdvice` AOP? | [§S1.5](#s15-when-it-goes-wrong-wrong-passwords-and-exceptiontranslationfilter) |
| `@EnableWebSecurity`, `httpBasic` internals, `spring.security.user.*`, `authorizeHttpRequests` | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database) |
| User entity, `GenerationType`, `UserDetails.super…` | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database), [§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-) |
| Is `@Repository` mandatory? | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database) |
| Why not `@Autowired`/`@Bean` the UserDetailsService; beans as `@Bean` params; custom AuthenticationManager | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database) |
| CommandLineRunner seeding — will it run? | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database) |
| `requestMatchers(...).permitAll()`, disabling CSRF | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database), [§S6.1](#s61-csrf-q34) |
| Signup / login API | [§S2.3](#s23-walkthrough-replacing-the-defaults-with-http-basic--users-from-your-database), [§S3.2](#s32-the-complete-jwt-flow-login-endpoint-token-creation-and-the-filter) |
| JWT: skip the chain? authorization manual? jjwt libraries, `compact()`, symmetric vs asymmetric + JWKS, filter position | [§S3.2](#s32-the-complete-jwt-flow-login-endpoint-token-creation-and-the-filter) |
| "We didn't validate expiry?" | [§S3.2](#s32-the-complete-jwt-flow-login-endpoint-token-creation-and-the-filter) |
| Refresh tokens | [§S3.3](#s33-refresh-tokens-short-access-tokens-without-constant-re-login) |
| AuthorizationFilter, AuthorizationManager implementations, `check` vs `authorize`, FastAPI/Express | [§S4.1](#s41-the-authorization-architecture-authorizationfilter--authorizationmanager) |
| Role + Permission enums, requestMatchers, "hundreds of APIs" | [§S4.4](#s44-roles-and-permissions-with-enums-enforced-by-requestmatchers) |
| Method security internals, AOP order, expression handler, EvaluationContext, expressions | [§S4.6](#s46-method-security-under-the-hood-interceptors-expression-handler-evaluationcontext) |
| `@PostAuthorize`, `@PreFilter`, `@PostFilter`, non-collection returns | [§S4.7](#s47-postauthorize-prefilter-postfilter-in-depth) |
| `@HandleAuthorizationDenied`, `@AuthorizeReturnObject`, ProblemDetail 403 | [§S4.8](#s48-graceful-denial-handleauthorizationdenied-authorizereturnobject-and-clean-403-json) |
| OAuth2 login flow, ClientRegistrationRepository, DefaultOAuth2UserService | [§S5.1](#s51-two-different-things-both-called-oauth2), [§S5.2](#s52-the-oauth2login-flow-step-by-step) |
| Does Spring store OAuth2 users in a DB (like Supabase)? | [§S5.3](#s53-does-spring-create-a-db-table-for-users-like-supabase--no-just-in-time-provisioning) |
| Hybrid Google login + own JWT; pure resource server; JwtAuthenticationConverter | [§S5.4](#s54-hybrid-log-in-with-google-then-issue-your-own-jwt-to-a-spa), [§S5.5](#s55-pure-resource-server-oauth2resourceserver-and-mapping-roles) |
| CORS with Spring Security | [§S6.2](#s62-cors-when-spring-security-is-on-the-classpath), [§W9](03-spring-web.md#w9-cors-crossorigin-corsfilter-and-spring-security) |


---

[⬅ 04-spring-data.md](04-spring-data.md) · [🏠 Start here](00-start-here.md) · [06-spring-production.md ➡](06-spring-production.md)
