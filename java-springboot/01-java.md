# Java — Core Language Notes

[⬅ 00-start-here.md](00-start-here.md) · [🏠 Start here](00-start-here.md) · [02-spring-core.md ➡](02-spring-core.md)

> Part of the Java & Spring Boot learning set. Section labels in this file start with **J**. The legend, version landscape, quick revision sheet and glossary live in [00-start-here.md](00-start-here.md).

## Contents

- [J1. Orientation](#j1-orientation)
  - [J1.1 The translation table [+]](#j11-the-translation-table-)
  - [J1.2 The six things that actually trip people up [+]](#j12-the-six-things-that-actually-trip-people-up-)
  - [J1.3 The runtime picture: JDK, JRE, JVM, bytecode, JIT [+]](#j13-the-runtime-picture-jdk-jre-jvm-bytecode-jit-)
  - [J1.4 Build and dependencies: Maven/Gradle vs pip/npm [+]](#j14-build-and-dependencies-mavengradle-vs-pipnpm-)
  - [J1.5 How the `main` method is found and called [Q1]](#j15-how-the-main-method-is-found-and-called-q1)
- [J2. The Java essentials you will hit in week one [+]](#j2-the-java-essentials-you-will-hit-in-week-one-)
  - [J2.1 Primitives vs objects, autoboxing, and the `==` trap](#j21-primitives-vs-objects-autoboxing-and-the--trap)
  - [J2.2 `equals` / `hashCode` — the contract](#j22-equals--hashcode--the-contract)
  - [J2.3 `null` and `Optional`](#j23-null-and-optional)
  - [J2.4 `Optional` in depth: what it is, the methods, and life without it](#j24-optional-in-depth-what-it-is-the-methods-and-life-without-it)
  - [J2.5 Collections in one table](#j25-collections-in-one-table)
  - [J2.6 Generics and type erasure](#j26-generics-and-type-erasure)
  - [J2.7 Interfaces, abstract classes, default methods](#j27-interfaces-abstract-classes-default-methods)
  - [J2.8 Functional interfaces, lambdas and method references — "functions" in Java](#j28-functional-interfaces-lambdas-and-method-references--functions-in-java)
  - [J2.9 Streams — your comprehensions and array methods](#j29-streams--your-comprehensions-and-array-methods)
  - [J2.10 Modern Java syntax you'll see in Spring Boot 3 code](#j210-modern-java-syntax-youll-see-in-spring-boot-3-code)
  - [J2.11 `static`, `final`, access modifiers](#j211-static-final-access-modifiers)
- [J3. String vs StringBuilder vs StringBuffer [Q11]](#j3-string-vs-stringbuilder-vs-stringbuffer-q11)
  - [J3.1 Core differences at a glance [Q11]](#j31-core-differences-at-a-glance-q11)
  - [J3.2 Immutability, and why it matters [Q11]](#j32-immutability-and-why-it-matters-q11)
  - [J3.3 What `+` actually compiles to [+]](#j33-what--actually-compiles-to-)
  - [J3.4 The string pool — why `==` sometimes lies [+]](#j34-the-string-pool--why--sometimes-lies-)
  - [J3.5 StringBuilder internals [+]](#j35-stringbuilder-internals-)
  - [J3.6 Decision table [Q11 + extended]](#j36-decision-table-q11--extended)
  - [J3.7 Cross-language summary [+]](#j37-cross-language-summary-)
  - [J3.8 Gotchas checklist [+]](#j38-gotchas-checklist-)
- [J4. Checked vs unchecked exceptions [Q10]](#j4-checked-vs-unchecked-exceptions-q10)
  - [J4.1 The short answer to the cross-language part [Q10]](#j41-the-short-answer-to-the-cross-language-part-q10)
  - [J4.2 The hierarchy](#j42-the-hierarchy)
  - [J4.3 The comparison table](#j43-the-comparison-table)
  - [J4.4 Why the distinction exists, and why it's contested [Q10 + extended]](#j44-why-the-distinction-exists-and-why-its-contested-q10--extended)
  - [J4.5 The lambda and Streams problem (the modern pain point) [+]](#j45-the-lambda-and-streams-problem-the-modern-pain-point-)
  - [J4.6 `try-with-resources`, multi-catch, `finally` [+]](#j46-try-with-resources-multi-catch-finally-)
  - [J4.7 Design guidance for real services [+]](#j47-design-guidance-for-real-services-)
- [J5. Data carriers: records vs Lombok](#j5-data-carriers-records-vs-lombok)
  - [J5.1 The boilerplate problem, and your `ImmutableConfig` example](#j51-the-boilerplate-problem-and-your-immutableconfig-example)
  - [J5.2 Java records (Java 16+)](#j52-java-records-java-16)
  - [J5.3 Lombok: what it is and how it works internally](#j53-lombok-what-it-is-and-how-it-works-internally)
  - [J5.4 The Lombok annotations you'll actually see](#j54-the-lombok-annotations-youll-actually-see)
  - [J5.5 Record vs Lombok `@Value`](#j55-record-vs-lombok-value)
  - [J5.6 Why we still need Lombok: mutable classes and JPA entities](#j56-why-we-still-need-lombok-mutable-classes-and-jpa-entities)
  - [J5.7 Lombok pros and cons, and what "heavy" really means](#j57-lombok-pros-and-cons-and-what-heavy-really-means)
- [J6. Concurrency and multithreading [Q2–Q9]](#j6-concurrency-and-multithreading-q2q9)
  - [J6.1 Who actually creates and schedules threads? [Q7, Q8]](#j61-who-actually-creates-and-schedules-threads-q7-q8)
  - [J6.2 Python's `threading` module is a port of Java's [Q2]](#j62-pythons-threading-module-is-a-port-of-javas-q2)
  - [J6.3 Creating threads, `start()` vs `run()`, and `join()` [Q2, Q3]](#j63-creating-threads-start-vs-run-and-join-q2-q3)
  - [J6.4 The six thread states [Q4]](#j64-the-six-thread-states-q4)
  - [J6.5 Thread priorities [Q5, Q6] — and what they actually do on Linux](#j65-thread-priorities-q5-q6--and-what-they-actually-do-on-linux)
  - [J6.6 `Thread.yield()` [Q9]](#j66-threadyield-q9)
  - [J6.7 Synchronization: `synchronized`, monitors, and explicit locks [Q2, Q3]](#j67-synchronization-synchronized-monitors-and-explicit-locks-q2-q3)
  - [J6.8 Inter-thread communication: `wait` / `notify` / `notifyAll` [Q2, Q3]](#j68-inter-thread-communication-wait--notify--notifyall-q2-q3)
  - [J6.9 The complete Java ↔ Python method map [Q3]](#j69-the-complete-java--python-method-map-q3)
  - [J6.10 What Java has that Python's `threading` module doesn't [Q3]](#j610-what-java-has-that-pythons-threading-module-doesnt-q3)
  - [J6.11 The Java Memory Model in one page [+]](#j611-the-java-memory-model-in-one-page-)
  - [J6.12 Virtual threads and structured concurrency [+]](#j612-virtual-threads-and-structured-concurrency-)
  - [J6.13 `ThreadLocal`, `InheritableThreadLocal` and `ScopedValue`: per-thread context (vs Python's `ContextVar`)](#j613-threadlocal-inheritablethreadlocal-and-scopedvalue-per-thread-context-vs-pythons-contextvar)
  - [J6.14 Concurrency checklist [+]](#j614-concurrency-checklist-)
- [J7. CompletableFuture: thenApply, thenCompose, exceptionally [Q★]](#j7-completablefuture-thenapply-thencompose-exceptionally-q)
  - [J7.1 The one-sentence answer](#j71-the-one-sentence-answer)
  - [J7.2 Why Java needs two methods and JavaScript needs one](#j72-why-java-needs-two-methods-and-javascript-needs-one)
  - [J7.3 Creating futures](#j73-creating-futures)
  - [J7.4 The full transformation table](#j74-the-full-transformation-table)
  - [J7.5 Error handling: `exceptionally` vs `handle` vs `whenComplete`](#j75-error-handling-exceptionally-vs-handle-vs-whencomplete)
  - [J7.6 The `CompletionException` wrapping gotcha](#j76-the-completionexception-wrapping-gotcha)
  - [J7.7 Which thread runs your callback? (the `*Async` gotcha)](#j77-which-thread-runs-your-callback-the-async-gotcha)
  - [J7.8 Fan-out: the `Promise.all` / `asyncio.gather` equivalent](#j78-fan-out-the-promiseall--asynciogather-equivalent)
  - [J7.9 `join()` vs `get()`](#j79-join-vs-get)
  - [J7.10 Timeouts, retries, and cancellation](#j710-timeouts-retries-and-cancellation)
  - [J7.11 Cross-language cheat sheet](#j711-cross-language-cheat-sheet)
  - [J7.12 The Java 21+ postscript: you may not need any of this](#j712-the-java-21-postscript-you-may-not-need-any-of-this)

---


## J1. Orientation


### J1.1 The translation table [+]

Keep this open for your first month. Most "how do I do X in Java" questions are answered here.

| Concept | Python / FastAPI | Node / Express | Java / Spring Boot |
|---|---|---|---|
| Package manager | `pip` / `uv` | `npm` | **Maven** (`pom.xml`) or **Gradle** |
| Lockfile | `uv.lock` | `package-lock.json` | BOM (`dependencyManagement`) |
| Virtual env | `venv` | local `node_modules` | *none* — deps go on the **classpath** |
| Registry | PyPI | npm | **Maven Central** |
| Entry point | `main.py` | `index.js` | `public static void main(String[])` |
| Run in dev | `uvicorn app:app --reload` | `nodemon index.js` | `mvn spring-boot:run` + devtools |
| Web server | Uvicorn / Gunicorn | Node `http` module | **Tomcat** (embedded in the jar) |
| "App" object | `app = FastAPI()` | `const app = express()` | `DispatcherServlet` (auto-created) |
| Route | `@app.get("/x")` | `app.get("/x", fn)` | `@GetMapping("/x")` |
| Path param | `/{id}` + `id: str` | `/:id` + `req.params.id` | `/{id}` + `@PathVariable String id` |
| Query param | `q: str = None` | `req.query.q` | `@RequestParam(required=false) String q` |
| Request body | Pydantic model param | `req.body` + `express.json()` | `@RequestBody OrderDto dto` |
| Response | `return {...}` | `res.json({...})` | `return dto;` (auto-serialised) |
| Middleware | ASGI middleware | `app.use(fn)` | **`Filter`** (servlet) + **`HandlerInterceptor`** (Spring) |
| Validation | Pydantic (built in) | `zod` / `joi` | **Bean Validation** (`@Valid` + `@NotBlank`) |
| JSON codec | Pydantic / `json` | `JSON.parse` / `stringify` | **Jackson** `ObjectMapper` |
| DI | `Depends()` | manual / Awilix | **Spring IoC container** |
| Config | `.env` + `pydantic-settings` | `.env` + `dotenv` | `application.yml` + `@ConfigurationProperties` |
| ORM | SQLAlchemy | Prisma / TypeORM | **JPA/Hibernate** via Spring Data |
| Templates | Jinja2 | EJS / Pug | **Thymeleaf** / FreeMarker / Mustache |
| Async primitive | `Coroutine` / `Task` | `Promise` | **`CompletableFuture`** |
| `async`/`await` | `async def` / `await` | `async` / `await` | *no keyword* — `.thenCompose(...)`, or **virtual threads** |
| Threads | `threading.Thread` (GIL) | Worker Threads (rare) | `Thread` — **true parallelism** |
| Lock | `threading.Lock` | n/a | `synchronized` / `ReentrantLock` |
| Test framework | pytest | Jest / Vitest | **JUnit 5** |
| Mocking | `unittest.mock` | `jest.mock` | **Mockito** |
| Type checking | mypy (optional) | TypeScript (optional) | **the compiler** (mandatory) |
| Null safety | `Optional[X]` | `undefined` / `null` | `null` + `Optional<T>` (library) |
| Interface | `Protocol` / ABC | TS `interface` | `interface` (runtime-present) |
| Dataclass | `@dataclass` / Pydantic | plain object | **`record`** (Java 16+) or Lombok `@Data` |
| Enum | `enum.Enum` | TS `enum` | `enum` (a real class, can have methods) |
| Comprehension | `[f(x) for x in xs]` | `xs.map(f)` | `xs.stream().map(f).toList()` |
| Dict | `dict` | `Object` / `Map` | `Map<K,V>` |
| f-string | `f"{a} {b}"` | `` `${a} ${b}` `` | `"%s %s".formatted(a, b)` |
| API docs | FastAPI built-in `/docs` | swagger-jsdoc | **springdoc-openapi** |

---

### J1.2 The six things that actually trip people up [+]

**1. Everything lives in a class.** No free functions, no module-level code. A "script" is a class with a `main`. (Java 25 relaxes this — see [§J1.5](#j15-how-the-main-method-is-found-and-called-q1).)

**2. Types are checked at compile time and partially erased at runtime.** Unlike mypy/TypeScript, you *cannot run* code that doesn't typecheck. But unlike TypeScript, class identity and method signatures **survive to runtime** — which is exactly what lets Spring do its reflection-driven magic. **Generics, however, are erased**: `List<String>` and `List<Integer>` are the same class at runtime ([§J2.6](#j26-generics-and-type-erasure)).

**3. Objects compare with `.equals()`, not `==`.** 🟨 JS people already know this for objects (`{} === {}` is `false`) — but JS strings are *primitives*, so `"a" === "a"` is `true`. **In Java `String` is an object**, so `==` is a reference check that *often accidentally works* thanks to the string pool, then breaks in production. ([§J3.4](#j34-the-string-pool--why--sometimes-lies-))

**4. The default concurrency model is real OS threads, not an event loop.** 🟨 Node is one thread; never block it. 🐍 FastAPI is an event loop plus a small threadpool for `def` endpoints. **Spring MVC is thread-per-request with ~200 threads**, and blocking is *normal and correct*. A blocking JDBC call inside a controller is idiomatic Java. This inverts your instincts. ([§W1.5](03-spring-web.md#w15-one-servlet-many-threads--the-concurrency-model-q44), [§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads))

**5. Frameworks wire themselves at *startup*, not at first use.** Spring builds the entire object graph when the app boots. A missing dependency is a **startup crash**, not a 3 a.m. 500. ([§C2.13](02-spring-core.md#c213-what-actually-happens-at-startup-the-mechanism))

**6. Checked exceptions exist and the compiler enforces them.** Nothing in Python or JS is equivalent. ([§J4](#j4-checked-vs-unchecked-exceptions-q10))

---

### J1.3 The runtime picture: JDK, JRE, JVM, bytecode, JIT [+]

```
   Foo.java                  Foo.class                 machine code
 ┌──────────┐   javac      ┌─────────────┐   JVM     ┌───────────────┐
 │  source  │ ───────────► │  BYTECODE   │ ────────► │   interpret   │
 │  (text)  │  (compile)   │  (portable) │  (load)   │      ↓        │
 └──────────┘              └─────────────┘           │  profile hot  │
                                                     │   methods     │
                                                     │      ↓        │
                                                     │  JIT compile  │ ← C1, then C2
                                                     │  to native    │
                                                     └───────────────┘
```

- **JVM** — executes bytecode. Owns memory, GC, threads, JIT.
- **JRE** — JVM + standard library. *Running* only. Oracle stopped shipping a separate JRE with Java 11 (vendors such as Eclipse Temurin still publish JRE-only builds; `jlink` builds a trimmed runtime).
- **JDK** — JRE + `javac`, `jar`, `jshell`, `jlink`, `javap`, profiling tools. **You install a JDK.**
- **Bytecode** — portable instructions in `.class` files. **`javap -c Foo.class` disassembles it** — this is how you *prove* what the compiler did, and we use it in [§J3.3](#j33-what--actually-compiles-to-).
- **JIT** — the JVM interprets first, counts invocations, then compiles hot methods natively (C1 for fast warm-up, C2 for peak throughput). **Java is slow for a few seconds, then very fast.** This is why JVM benchmarks need a warm-up and why a freshly deployed pod briefly looks bad on latency graphs.

🐍🟨 CPython compiles to bytecode too (`.pyc`) but mostly interprets it. V8 *is* a JIT, so Node's execution model is closer to the JVM's than CPython's is.

**Garbage collection in a paragraph.** You never free memory. Generational heap: new objects in **Eden** → survivors copied to **Survivor** → long-lived ones **promoted to Old Gen**. Minor GCs are frequent and cheap; full GCs are rare and expensive. Default collector on modern JVMs is **G1**; **ZGC**/**Shenandoah** are low-pause alternatives. Leaks in Java are *reference* leaks (a `static Map` you never evict from), not missing `free()`.

---

### J1.4 Build and dependencies: Maven/Gradle vs pip/npm [+]

**Maven** (`pom.xml`) is declarative XML with a fixed lifecycle. **Gradle** is a programmable DSL. Both resolve from **Maven Central**. A dependency is identified by **GAV**: `groupId:artifactId:version`.

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <!-- no <version>! inherited from the spring-boot-starter-parent BOM -->
</dependency>
```

| | npm | pip | Maven |
|---|---|---|---|
| Nested versions of one lib | ✅ allowed | ❌ one per env | ❌ **one per classpath** |
| Conflict resolution | nested installs | fails / last wins | **"nearest wins"** (shortest path) |
| Version pinning | lockfile | lockfile | **BOM** |

⚠️ **The single biggest difference:** npm can install two versions of a package side by side. **Java cannot** — one version of a class per classloader, full stop. When two libraries need incompatible versions of a third, you get `NoSuchMethodError` at *runtime*. This is **"JAR hell"**, and it's why BOMs exist: `spring-boot-starter-parent` pins ~300 library versions tested together, so you never write a version number for anything Spring manages.

```bash
mvn dependency:tree                                        # like `npm ls`
mvn dependency:tree -Dincludes=com.fasterxml.jackson.core  # why is THIS version here?
mvn clean package
mvn spring-boot:run
```

---

### J1.5 How the `main` method is found and called [Q1]

> **Your question:** *"how main method will be called if that is inside a class in java?"*

#### The execution flow

```
  $ java MainClass
        │
        ▼
  ┌──────────────────┐
  │ 1. JVM starts    │   launcher creates the VM, sets up heap/threads
  └────────┬─────────┘
           ▼
  ┌──────────────────┐
  │ 2. ClassLoader   │   loads MainClass.class, VERIFIES the bytecode,
  │    loads class   │   prepares static fields, resolves the constant pool
  └────────┬─────────┘
           ▼
  ┌──────────────────┐
  │ 3. Locate main() │   looks for the exact signature
  └────────┬─────────┘
           ▼
  ┌──────────────────┐
  │ 4. Invoke        │   MainClass.main(args)   ← NO instance is created
  └──────────────────┘
```

#### Step by step

```bash
javac MainClass.java   # source → MainClass.class (bytecode)
java  MainClass        # ask the JVM to execute it
```

1. **Compilation** — `javac` produces bytecode.
2. **JVM launch** — `java MainClass` starts the VM.
3. **Class loading** — the ClassLoader loads `MainClass.class` into memory, verifies the bytecode is safe, and initialises static structures.
4. **Lookup** — the JVM searches for a method matching exactly:
   ```java
   public static void main(String[] args)
   ```
5. **Direct call** — because `main` is `static`, **the JVM does not create an instance**. It never does `new MainClass()`. It invokes the method through the class reference:
   ```java
   MainClass.main(new String[] {});
   ```

#### Why every keyword is required (pre-Java 25)

```java
public class MainClass {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }
}
```

| Keyword | Why the JVM needs it |
|---|---|
| `public` | The JVM launcher lives outside your package; it needs access to call the method. |
| `static` | Lets the JVM invoke it **without constructing your class first**. If `main` were an instance method, the JVM wouldn't know which constructor to call or what arguments to pass it. |
| `void` | Tells the JVM nothing is returned. The process **exit status** is separate (`System.exit(int)`). |
| `main` | The exact identifier the launcher searches for, by hardcoded convention. |
| `String[] args` | Receives command-line arguments: `java MainClass arg1 arg2` → `args = ["arg1", "arg2"]`. |

⚠️ Note `args` is `["arg1","arg2"]`, **not** `["MainClass","arg1","arg2"]`. 🐍 Unlike Python's `sys.argv[0]`, the program name is not element 0. 🟨 Unlike Node's `process.argv`, which starts with the node binary and the script path.

#### `main` is just a static method — you can call it yourself [Q1]

```java
public class FirstClass {
    public static void main(String[] args) {
        System.out.println("FirstClass running...");

        // Calling another class's main method manually — nothing special about it
        SecondClass.main(new String[]{"customArg"});
    }
}

class SecondClass {
    public static void main(String[] args) {
        System.out.println("SecondClass received arg: " + args[0]);
    }
}
```
```
FirstClass running...
SecondClass received arg: customArg
```

This is genuinely useful to internalise: **`main` has no magic properties.** The launcher just happens to look for that name. (This is also how Spring Boot works — `SpringApplication.run(App.class, args)` is an ordinary static call made from inside your ordinary `main`.)

#### Java vs Python vs Node [Q1, extended]

| Stage | Java | Python | Node |
|---|---|---|---|
| Entry point | explicit `public static void main(String[])` inside a class | any top-level code, conventionally gated by `if __name__ == "__main__":` | any top-level code in the entry file |
| Code must be in a class? | **Yes** (until Java 25) | No | No |
| Instance created? | No — `static` | No | No |
| Args variable | `args` (no program name) | `sys.argv` (`argv[0]` = script) | `process.argv` (`[0]`=node, `[1]`=script) |
| Multiple entry points | ✅ every class can have a `main` | one per file, via the `__main__` guard | one per file |

#### Java 25 removed all of this ceremony [+]

**JEP 512 "Compact Source Files and Instance Main Methods" was finalised in Java 25** (after four preview rounds starting in Java 21). As of Java 25 this is a complete, legal program in a file called `Hello.java`:

```java
void main() {
    IO.println("Hello, World!");
}
```

What changed:
- **No class needed.** Methods and fields outside any class declaration go into an *unnamed, implicitly declared top-level class* (a "compact source file").
- **`static` is optional.** The launcher now recognises **instance** `main` methods and constructs the object for you.
- **`public` is optional.**
- **`String[] args` is optional** — `void main()` is a valid signature.
- **`java.lang.IO`** (`IO.println`, `IO.readln`) is implicitly available, no import.

You still need the classic form for any real application — Spring Boot's `@SpringBootApplication` class needs to be a named, public class — but if a tutorial written after late 2025 shows a bare `void main()`, this is why.

**Most production services still run Java 17–21**, so the classic form is what you'll write at work.

*Source: [JEP 512](https://openjdk.org/jeps/512), [InfoQ](https://www.infoq.com/news/2025/05/jdk25-instance-main-methods/)*

---
---

## J2. The Java essentials you will hit in week one [+]

Not from your chats, but you will hit every one of these within days. Kept deliberately brief.

### J2.1 Primitives vs objects, autoboxing, and the `==` trap

```java
int    a = 5;      // PRIMITIVE — 4 bytes stored inline (on the stack for a local), cannot be null
Integer b = 5;     // OBJECT wrapper — heap-allocated, CAN be null
```

| Primitive | Wrapper | | Primitive | Wrapper |
|---|---|---|---|---|
| `byte` | `Byte` | | `float` | `Float` |
| `short` | `Short` | | `double` | `Double` |
| `int` | `Integer` | | `char` | `Character` |
| `long` | `Long` | | `boolean` | `Boolean` |

Generics can't hold primitives — `List<int>` doesn't compile; you need `List<Integer>`.

⚠️ **Three traps:**
```java
Integer x = 127, y = 127;   x == y;   // true  — the Integer cache covers -128..127
Integer p = 128, q = 128;   p == q;   // false — outside the cache. USE .equals()

Map<String,Integer> m = new HashMap<>();
int v = m.get("missing");             // NullPointerException — unboxing null

double d = 0.1 + 0.2;                 // 0.30000000000000004 — IEEE-754, same as Python/JS
// For money: BigDecimal.valueOf(0.1).add(BigDecimal.valueOf(0.2))  → exactly 0.3
```

### J2.2 `equals` / `hashCode` — the contract

```java
// If two objects are equal, they MUST have the same hashCode.
// Break this and HashMap/HashSet silently lose your objects.
```
**Always override both together, or neither.** `record` does it for you automatically — another reason to prefer records for data.

### J2.3 `null` and `Optional`

Java has no `?.` optional chaining and no truthiness. `null` is Tony Hoare's "billion-dollar mistake", and it's still here.

```java
Optional<User> u = repo.findById(id);
String name = u.map(User::name).orElse("unknown");
u.ifPresent(this::audit);
u.orElseThrow(() -> new UserNotFoundException(id));
```
**Rules:** use `Optional` as a **return type** for "might not exist". Never as a field, never as a parameter, never in a collection. Never call `.get()` without checking. 🐍 It's `Optional[X]` minus language support.

### J2.4 `Optional` in depth: what it is, the methods, and life without it

> **Your question:** *"what is Optional here and how does it getting used in spring boot and java and common method of Optional and what will happen if we don't use this optional here"*

**What it is.** `java.util.Optional<T>` (Java 8) is a small **box that holds either one non-null value or nothing**. It doesn't remove `null` from Java. It makes "there may be no result" **visible in the method signature**, so the caller is forced to decide what to do in the empty case.

The JDK's own API note states the intended use:

> *"`Optional` is primarily intended for use as a method return type where there is a clear need to represent 'no result,' and where using `null` is likely to cause errors. A variable whose type is `Optional` should never itself be `null`; it should always point to an `Optional` instance."*

```
Optional<User>
 ┌──────────────┐        ┌──────────────┐
 │  [ User ]    │   or   │   [ empty ]  │      never: null itself
 └──────────────┘        └──────────────┘
```

#### In plain Java: return it instead of `null`

```java
// Before: the signature lies. Nothing says this can return null.
public String getUserNickname(String userId) {
    return idExists ? "Ace" : null;
}

// After: the signature tells the truth.
public Optional<String> getUserNickname(String userId) {
    return idExists ? Optional.of("Ace") : Optional.empty();
}
```

#### In Spring Boot: Spring Data hands you one

`findById` is **inherited** from `CrudRepository<T, ID>` and already returns `Optional<T>`. You don't redeclare it (redeclaring it compiles, but adds nothing):

```java
public interface UserRepository extends JpaRepository<User, Long> {
    // Optional<User> findById(Long id);  ← already inherited, no need to write it
    Optional<User> findByEmail(String email);   // derived queries may also return Optional
}

@Service
public class UserService {
    private final UserRepository userRepository;
    public UserService(UserRepository userRepository) { this.userRepository = userRepository; }

    public User getUserOrThrow(Long id) {
        return userRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("User not found with id: " + id));
    }
}
```

The thrown exception is then turned into a 404 by your global handler. 🔗 See [§W8](03-spring-web.md#w8-writing-responses-responsebody-responseentity-message-converters-and-global-error-handling).

Other places Spring accepts `Optional`:
- As an **optional controller argument** (`@RequestParam Optional<String> q`), where Spring treats it like `required = false`.
- As `ObjectProvider` / `Optional<SomeBean>` injection points for optional beans ([§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13)).

These are framework-supported exceptions to the "never as a parameter" rule.

#### The common methods

| Method | Since | What it does | Example |
|---|---|---|---|
| `Optional.of(v)` | 8 | Wraps a value that **must not be null** (throws `NullPointerException` if it is) | `Optional.of("Hello")` |
| `Optional.ofNullable(v)` | 8 | Wraps a value that may be null; null → empty | `Optional.ofNullable(map.get(k))` |
| `Optional.empty()` | 8 | The empty box | `Optional.empty()` |
| `isPresent()` / `isEmpty()` | 8 / **11** | true/false checks | `if (opt.isEmpty()) …` |
| `orElse(default)` | 8 | Value, or the default | `opt.orElse("Guest")` |
| `orElseGet(supplier)` | 8 | Value, or **compute** a default lazily | `opt.orElseGet(() -> fetchDefault())` |
| `orElseThrow()` | **10** | Value, or `NoSuchElementException`. Read it as "a `get()` that admits it can throw" | `opt.orElseThrow()` |
| `orElseThrow(supplier)` | 8 | Value, or **your** exception | `opt.orElseThrow(() -> new NotFound(id))` |
| `ifPresent(consumer)` | 8 | Run code only when present | `opt.ifPresent(System.out::println)` |
| `ifPresentOrElse(c, r)` | **9** | Present → `c`, empty → `r` | `opt.ifPresentOrElse(this::send, this::logMissing)` |
| `map(fn)` | 8 | Transform the value. **If `fn` returns null, you get empty** | `opt.map(String::toUpperCase)` |
| `flatMap(fn)` | 8 | Transform with a function that itself returns `Optional` (no `Optional<Optional<…>>`) | `user.flatMap(User::findManager)` |
| `filter(pred)` | 8 | Keep the value only if it matches | `opt.filter(u -> u.isActive())` |
| `or(supplier)` | **9** | Empty → try another `Optional` | `cache.get(id).or(() -> db.find(id))` |
| `stream()` | **9** | 0- or 1-element stream; flattens a stream of Optionals | `ids.stream().map(repo::findById).flatMap(Optional::stream)` |
| `get()` | 8 | Value or `NoSuchElementException`. ⚠️ Avoid; prefer `orElseThrow()` | — |

⚠️ **`orElse` vs `orElseGet`, the trap that costs real money.** `orElse(x)` evaluates `x` **always**, even when the value is present, because it is an ordinary method argument. `orElse(callExpensiveService())` makes the remote call every time. Use `orElseGet(() -> callExpensiveService())` for anything that isn't a constant.

(`map`/`flatMap` here are the same map/flatMap pair you meet on `Stream` and `CompletableFuture`. See the table in [§J7.2](#j72-why-java-needs-two-methods-and-javascript-needs-one).)

#### What happens if you don't use `Optional`?

Nothing breaks at compile time. You return `null` and rely on every caller remembering to check. Three consequences:

1. **`NullPointerException` at runtime** the first time a caller forgets: `getUser(id).getName()` crashes.
2. **Null-check pyramids:**
   ```java
   User user = userRepository.findUser(id);          // may return null
   if (user != null) {
       Address address = user.getAddress();
       if (address != null) {
           String city = address.getCity();
           if (city != null) { /* do something */ }
       }
   }
   ```
   The `Optional` chain replaces it. Here `findById` returns `Optional`, and `map` turns a `null` from a getter into empty:
   ```java
   String city = userRepository.findById(id)
           .map(User::getAddress)
           .map(Address::getCity)
           .orElse("Unknown");
   ```
   🟨 This is Java's version of `user?.address?.city ?? "Unknown"`. Java has no `?.` operator.
3. **Hidden intent.** `User getUser(String id)` doesn't tell you whether it can return null. `Optional<User> getUser(String id)` does.

#### Where *not* to use it

| Don't | Why | Instead |
|---|---|---|
| Fields | It's not `Serializable`. JPA/Jackson field mapping gets awkward. It's an extra object per field. | A nullable field, and a getter that returns `Optional.ofNullable(field)` |
| Method parameters (your own APIs) | Callers can still pass `null` for the `Optional` itself, so you've gained nothing | Overloads, or a nullable parameter documented with `@Nullable` (Spring 7 uses JSpecify annotations: see [§R2](00-start-here.md#r2-version-landscape--november-2026)) |
| Collections (`List<Optional<X>>`) | Pointless double "emptiness" | An empty list, or filter the empties out |
| Returning `null` from a method typed `Optional` | Defeats the point (the JDK note above says never do this) | `Optional.empty()` |
| Synchronising on it / comparing with `==` | It's a *value-based class*: "should not use instances for synchronization" | `.equals()` |

📌 **Correction to a common claim:** `Optional` does not "eliminate" `NullPointerException`. It eliminates NPEs **for callers who use its API**. `opt.get()` on an empty `Optional` still blows up (with `NoSuchElementException`), and nothing stops a getter inside your `map` from NPE-ing on something else.

### J2.5 Collections in one table

| You want | Interface | Default impl | Python | JS |
|---|---|---|---|---|
| Ordered, indexed | `List<E>` | `ArrayList` | `list` | `Array` |
| Unique | `Set<E>` | `HashSet` (`LinkedHashSet` keeps order) | `set` | `Set` |
| Key→value | `Map<K,V>` | `HashMap` (`LinkedHashMap` keeps order) | `dict` | `Map` |
| FIFO / LIFO | `Deque<E>` | `ArrayDeque` | `collections.deque` | `Array` |
| Sorted | `TreeMap`/`TreeSet` | — | `sortedcontainers` | — |
| Thread-safe map | — | `ConcurrentHashMap` | — | — |

⚠️ `List.of(...)`, `Map.of(...)`, `Set.of(...)` (Java 9+) create **immutable** collections. `.add()` throws `UnsupportedOperationException`. Use `new ArrayList<>(List.of(...))` if you need it mutable.

### J2.6 Generics and type erasure

```java
List<String>  a = new ArrayList<>();
List<Integer> b = new ArrayList<>();
a.getClass() == b.getClass();       // TRUE — both are just ArrayList at runtime
```

Generics are **compile-time only**; the JVM sees raw types. Consequences: no `new T[]`, no `instanceof List<String>`, no overloading on `List<String>` vs `List<Integer>`.

The workaround Spring uses everywhere is **`ParameterizedTypeReference`** / `TypeToken` — capturing the type via an anonymous subclass, because a class's *generic supertype* **is** retained in the bytecode:
```java
restTemplate.exchange(url, GET, null, new ParameterizedTypeReference<List<Order>>() {});
```

**Wildcards** (PECS — *Producer Extends, Consumer Super*):
```java
void readAll (List<? extends Number> src)   // producer — you READ Numbers out
void writeAll(List<? super Integer> dst)    // consumer — you WRITE Integers in
```

### J2.7 Interfaces, abstract classes, default methods

| | `interface` | `abstract class` |
|---|---|---|
| Multiple inheritance | ✅ implement many | ❌ extend one |
| Instance fields | ❌ (only `static final` constants) | ✅ |
| Constructor | ❌ | ✅ |
| Method bodies | ✅ `default` / `static` (Java 8+), `private` (Java 9+) | ✅ |

**Rule:** interface by default; abstract class only when you need shared *state*. 🐍 ≈ `Protocol` vs ABC, but Java interfaces are real runtime types — which is what lets Spring create dynamic proxies for `@Transactional` etc.

A `@FunctionalInterface` has exactly one abstract method and can be a lambda target: `Runnable`, `Supplier<T>`, `Consumer<T>`, `Function<T,R>`, `Predicate<T>`, `BiFunction<T,U,R>`, `Comparator<T>`.

### J2.8 Functional interfaces, lambdas and method references — "functions" in Java

**Why this comes before Streams:** every `.filter(...)`, `.map(...)`, `Optional.map(...)`, Spring callback and gRPC client helper you will read takes a *function-shaped argument*. Java has no free-standing function type; the argument is always an **object whose interface has exactly one abstract method**. Once that clicks, Streams, `Optional`, `CompletableFuture` and typical gRPC client helpers all read the same way.

> **Python / JS anchor.** In Python or JS a function is a value (`fn.length` / `inspect.signature` tell you its shape at *runtime*). In Java the "shape" is fixed at **compile time** by an interface type. `x -> x * 2` has no type of its own: it takes the type of whatever interface the target position demands.

#### The rule (JLS §9.8, verified against the SE 21 spec)

> "A *functional interface* is an interface that is not declared `sealed` and has just one `abstract` method (aside from the methods of `Object`), and thus represents a single function contract."

| Detail | Truth |
|---|---|
| What is excluded from the count | `default` methods, `static` methods, and abstract methods whose signature matches a `public` method of `Object` (that is why `Comparator`, which re-declares `equals`, is still functional) |
| Inherited duplicates | Several inherited abstract methods with **override-equivalent** signatures count as one (JLS Example 9.8-2). Different signatures (`Iterable<String>` vs `Iterable<Integer>`) do not |
| `@FunctionalInterface` | **Optional.** It only makes the compiler reject the interface if it is *not* functional (JLS §9.6.4.9). The spec says it is "not necessary or desirable" to annotate every one |
| Not functional | `io.grpc.stub.StreamObserver` has three abstract methods (`onNext`, `onError`, `onCompleted`), so you can **never** write it as a lambda. That is why gRPC code uses anonymous classes for it |

#### The four you will meet daily (`java.util.function`)

| Interface | Single method | Shape | Typical use | JS/Python feel |
|---|---|---|---|---|
| `Predicate<T>` | `boolean test(T t)` | T → boolean | `filter`, `removeIf` | `arr.filter(fn)` callback |
| `Function<T,R>` | `R apply(T t)` | T → R | `map`, `Optional.map`, `computeIfAbsent` | `arr.map(fn)` callback |
| `Consumer<T>` | `void accept(T t)` | T → nothing | `forEach`, `ifPresent` | `forEach(fn)` |
| `Supplier<T>` | `T get()` | nothing → T | `orElseGet`, lazy defaults | `() => value` thunk |

Related: `Runnable.run()` (no args, no result, no checked exceptions), `Callable<V>.call()` (returns a value, **may throw checked exceptions**), `BiFunction`, `UnaryOperator<T>` (a `Function<T,T>`), `BiConsumer` (used by `CompletableFuture.whenComplete`).

#### Three ways to write the same function

```java
Function<String, Integer> a = new Function<>() {          // 1. anonymous class (pre-Java 8 style)
    @Override public Integer apply(String s) { return s.length(); }
};
Function<String, Integer> b = s -> s.length();             // 2. lambda
Function<String, Integer> c = String::length;              // 3. method reference
```

Four kinds of method reference: `Type::staticMethod`, `instance::method` (bound), `Type::instanceMethod` (first argument becomes the receiver, as with `String::length`), `Type::new` (constructor). **A lambda is not syntactic sugar for an anonymous class at runtime** (it is linked via `invokedynamic`, and `this` inside a lambda is the *enclosing* object), but you can treat it as "an object implementing the interface" when reasoning about types.

#### Closures: capture rules

A lambda can read local variables from its enclosing method only if they are **final or effectively final** (never reassigned). Fields are fine. JS closures capture variables by reference and can mutate them; Java captures the *value*, which is why the rule exists. The usual workaround for "I need a counter" is `AtomicInteger`, or better, restructure with `reduce`/`collect`.

#### Arity vs signature (the `fn.length` question)

- JS: `fn.length` is a runtime property, and extra or missing arguments are tolerated.
- Java: the interface method's parameter list *is* the contract. `(a, b) -> a + b` assigned to a `Function<T,R>` is a **compile error**, not a runtime surprise. Overload resolution also uses this shape, which is why a method taking both `Function` and `Consumer` can be ambiguous for a lambda like `x -> foo(x)`.

#### Higher-order functions and inversion of control

A *higher-order function* takes or returns functions. In Java that just means a method whose parameter or return type is a functional interface. The consequence that matters for frameworks: **you hand over a function and the framework decides when (and on which thread) to call it**. This is the same inversion as passing a handler to `app.get('/x', handler)` in Express. A typical gRPC client base class does exactly this: a `Function<ManagedChannel, Stub> stubFactory` receives `GreeterGrpc::newFutureStub`, and a `Function<Stub, ListenableFuture<ResponseT>>` receives `stub -> stub.sayHello(helloRequest)`.

> **Misconception corrected (from the study notes).** *"`map`, then `filter`, then `forEach` each run as a separate loop over the whole list."* **Wrong for streams.** Intermediate operations are lazy and, for stateless operations, are **fused into a single pass**; each element flows through the whole pipeline before the next one starts. The JDK docs: *"Traversal of the pipeline source does not begin until the terminal operation of the pipeline is executed"* and *"filtering, mapping, and summing can be fused into a single pass on the data."* Stateful operations such as `sorted()` are the exception: they must see all elements first. The per-element trace is drawn in §J2.9 under "Lazy (Java) vs eager (JavaScript)" (and `sorted()` is a barrier: it buffers everything before emitting anything); the eager-loop picture is exactly how JS `Array.prototype.map/filter` behave, which is where the confusion comes from.

### J2.9 Streams — your comprehensions and array methods

```java
List<String> names = users.stream()
        .filter(u -> u.age() >= 18)
        .map(User::name)
        .sorted()
        .toList();

Map<Dept, List<User>> byDept = users.stream().collect(groupingBy(User::dept));
double avg = users.stream().mapToInt(User::age).average().orElse(0);
```

| Python | JS | Java Stream |
|---|---|---|
| `[f(x) for x in xs if p(x)]` | `xs.filter(p).map(f)` | `xs.stream().filter(p).map(f).toList()` |
| `sum(xs)` | `xs.reduce((a,b)=>a+b, 0)` | `xs.stream().mapToInt(i->i).sum()` |
| `any(...)` / `all(...)` | `.some()` / `.every()` | `.anyMatch()` / `.allMatch()` |
| `sorted(xs, key=f)` | `xs.sort(cmp)` | `.sorted(comparing(f))` |
| `itertools.groupby` | — | `.collect(groupingBy(f))` |

#### ⚠️ Lazy (Java) vs eager (JavaScript) — the difference that actually changes behaviour

This is the one place where "`.stream()` is just `.map()/.filter()`" breaks down, and it is worth 60 seconds of your time.

```javascript
// JavaScript — EAGER. Each step builds a complete intermediate array.
[1,2,3,4,5]
  .filter(n => { console.log("filter", n); return n > 2; })   // runs 5 times, builds [3,4,5]
  .map(n    => { console.log("map", n);    return n * 2; })   // then runs 3 times
  .slice(0, 1);                                               // then throws away 2 of them
```
Output: `filter 1..5` (5 lines), then `map 3,4,5` (3 lines). **8 operations, 2 throwaway arrays.**

```java
// Java — LAZY. Elements flow through the whole pipeline one at a time.
Stream.of(1,2,3,4,5)
      .filter(n -> { System.out.println("filter " + n); return n > 2; })
      .map(n    -> { System.out.println("map " + n);    return n * 2; })
      .limit(1)
      .toList();
```
Output: `filter 1`, `filter 2`, `filter 3`, `map 3`. **4 operations, no intermediate collections, and elements 4 and 5 are never touched.**

```
JS (eager, horizontal)              Java (lazy, vertical)
─────────────────────────           ────────────────────────
[1,2,3,4,5]                         1 → filter ✗
   ↓ filter → [3,4,5]   (array)     2 → filter ✗
   ↓ map    → [6,8,10]  (array)     3 → filter ✓ → map → 6 → limit reached, STOP
   ↓ slice  → [6]                   4, 5 never evaluated
```

**Three consequences you will actually hit:**

| | JavaScript | Java Streams |
|---|---|---|
| Intermediate arrays allocated | one per step | **none** |
| `findFirst` / `limit` / `anyMatch` | still processes everything upstream | **short-circuits** — stops early |
| Infinite sequences | impossible | ✅ `Stream.iterate(1, n -> n*2).limit(10)` works |

⚠️ **Nothing runs until a terminal operation.** `list.stream().map(this::sendEmail);` on its own sends **zero** emails — there is no terminal operation, so the pipeline never executes. In JavaScript the equivalent `.map()` would have sent them all. This silently-does-nothing failure is the classic Java-Streams beginner bug.

**Terminal operations** (these trigger execution): `toList()`, `collect()`, `forEach()`, `reduce()`, `count()`, `sum()`, `min()`/`max()`, `findFirst()`/`findAny()`, `anyMatch()`/`allMatch()`/`noneMatch()`, `toArray()`, `iterator()`.
**Intermediate operations** (these only build the pipeline): `filter()`, `map()`, `flatMap()`, `sorted()`, `distinct()`, `limit()`, `skip()`, `peek()`.

💡 **Python is on Java's side here.** A generator expression `(f(x) for x in xs if p(x))` is lazy exactly like a Stream; the list comprehension `[f(x) for x in xs if p(x)]` is eager like JS. So `xs.stream()...toList()` ≈ `list(generator)` — build lazily, materialise once at the end.

⚠️ A stream is **single-use**. Consuming it twice throws `IllegalStateException: stream has already been operated upon or closed`. A JS array can be iterated forever; a Java `Stream` is closer to a Python generator — once exhausted, it is done. If you need it twice, keep the *collection* and call `.stream()` again.


### J2.10 Modern Java syntax you'll see in Spring Boot 3 code

```java
// record — immutable data carrier. equals/hashCode/toString/accessors generated.
public record OrderDto(String id, BigDecimal total, Instant createdAt) {}
// note: accessor is order.id(), NOT order.getId()

// var — local type inference (Java 10+). Locals only, never fields or params.
var orders = new ArrayList<OrderDto>();

// text block (Java 15+)
String json = """
        {"id": "%s", "total": %s}
        """.formatted(id, total);

// switch expression (Java 14); pattern matching in switch arrived in Java 21
String label = switch (status) {
    case NEW, PENDING -> "open";
    case SHIPPED      -> "in transit";
    default           -> "closed";
};

if (obj instanceof OrderDto dto && dto.total().signum() > 0) {  // instanceof pattern matching (Java 16)
    process(dto);
}

// sealed types (Java 17) — an exhaustive, closed hierarchy the compiler can check
public sealed interface Payment permits Card, Wallet, BankTransfer {}
```

⚠️ **Records and JPA don't mix.** A JPA `@Entity` needs a no-arg constructor and mutable fields; a `record` has neither. Use records for **DTOs**, classes for **entities** — which reinforces the DTO/entity separation in [§P5.2](06-spring-production.md#p52-dtos-vs-entities--never-expose-your-entities-).

### J2.11 `static`, `final`, access modifiers

| Modifier | Meaning |
|---|---|
| `static` | Belongs to the **class**, not an instance. One copy. |
| `final` (field) | Assign once. `static final` = a constant. |
| `final` (method) | Cannot be overridden. |
| `final` (class) | Cannot be subclassed (`String` is final). |

| Access | Same class | Same package | Subclass | Anywhere |
|---|---|---|---|---|
| `private` | ✅ | ❌ | ❌ | ❌ |
| *(none)* "package-private" | ✅ | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ | ✅ |

🐍 Java's `private` is **enforced by the compiler and JVM**, not a `_name` convention. ⚠️ Default (no modifier) is **package-private**, not public — a frequent surprise.

---
---

## J3. String vs StringBuilder vs StringBuffer [Q11]

> **Your question:** *"string builder vs string buffer and how they are different from string and when to use what?"*

### J3.1 Core differences at a glance [Q11]

| Feature | `String` | `StringBuilder` | `StringBuffer` |
|---|---|---|---|
| **Mutability** | **Immutable** — cannot be changed | **Mutable** | **Mutable** |
| **Thread safety** | ✅ safe (by nature of immutability) | ❌ **not synchronised** | ✅ every method `synchronized` |
| **Performance** | slow for frequent modification | **fastest** | slower than `StringBuilder` (lock overhead) |
| **Memory storage** | literals → **string pool**; runtime-built → regular heap | heap | heap |
| **Introduced** | Java 1.0 | **Java 5** | Java 1.0 (legacy) |

**One-line rule:**

| Use | When |
|---|---|
| `String` | Default for everything. Values, keys, params, returns. |
| `StringBuilder` | Building a string in a **loop** or across many steps, within one thread. **Your default for dynamic building.** |
| `StringBuffer` | **Effectively never.** Only if one buffer is genuinely shared across threads — and if it is, you probably have a design problem. |

**`StringBuilder` is a drop-in replacement for `StringBuffer`** with the synchronisation removed — same API, same superclass (`AbstractStringBuilder`), typically 10–30 % faster in tight loops because there is no lock acquisition and the JIT can inline more freely.

> 📝 A small refinement to the Q11 table: "Memory Storage: String → String Constant Pool" is only true for **literals** and strings you explicitly `.intern()`. A `String` built at runtime (`new String(...)`, concatenation of variables, a value read from a DB row) lives on the ordinary heap like any other object. This distinction is exactly what causes the `==` trap in [§J3.4](#j34-the-string-pool--why--sometimes-lies-).

### J3.2 Immutability, and why it matters [Q11]

```java
String s = "hello";
s.toUpperCase();          // returns a NEW String; `s` is untouched
System.out.println(s);    // "hello"  ← the classic beginner bug

s = s.toUpperCase();      // correct: reassign the reference
System.out.println(s);    // "HELLO"
```

Q11 puts it exactly right: *"Java does not change the original string. Instead, it discards the original reference, creates a completely new string object in memory, and points your variable to it."*

Immutability is deliberate. It buys:
- **Thread safety for free** — no `String` can be mutated under you, so no synchronisation is ever needed.
- **Safe hash caching** — `String` caches its `hashCode` in a field, which is why `HashMap<String, ?>` is fast.
- **Safe interning** — identical literals can share one object.
- **Security** — a `String` file path or SQL fragment cannot be swapped between a security check and its use (a TOCTOU attack).

🐍 Python strings are immutable for the same reasons. 🟨 JS strings are immutable *primitives*. So the concept isn't new — the **pool** is.

### J3.3 What `+` actually compiles to [+]

This surprises people, and it changed in Java 9.

**Java 8 and earlier** — `javac` desugared `+` into `StringBuilder`:
```java
String r = a + b + c;
// compiled to:
String r = new StringBuilder().append(a).append(b).append(c).toString();
```

**Java 9+ (JEP 280, "Indified String Concatenation")** — `javac` emits a single `invokedynamic` bound to `java.lang.invoke.StringConcatFactory`, which builds an optimal `MethodHandle` chain on first execution (it can pre-size the result array exactly, avoiding intermediate copies).

Prove it yourself:
```bash
javac Demo.java && javap -c Demo.class
# Java 8:   new java/lang/StringBuilder  +  invokevirtual append
# Java 9+:  invokedynamic #N, 0  // makeConcatWithConstants
```

⚠️ **Either way, the loop case is still O(n²):**
```java
String s = "";
for (int i = 0; i < 100_000; i++) {
    s += i;              // a NEW String allocated and the WHOLE prefix copied, every iteration
}
```
The optimisation is *per concatenation expression*, not *across loop iterations*. Iteration *n* copies *n* characters → ~5 × 10⁹ character copies for 100 000 iterations. Fine in a unit test with 10 items; melts in production with 100 000.

```java
StringBuilder sb = new StringBuilder();      // O(n) total — amortised growth
for (int i = 0; i < 100_000; i++) sb.append(i);
String s = sb.toString();
```

🐍 Same rule in Python — `s += x` in a loop is O(n²) (CPython has a refcount-1 in-place hack that sometimes hides it); the idiom is `"".join(parts)`. 🟨 Same in JS in principle, though V8's *ropes* (lazy concatenation trees) make naive `+=` far less catastrophic.

### J3.4 The string pool — why `==` sometimes lies [+]

The JVM keeps a **string pool** (a hash table in the heap since Java 7; in PermGen before). Every `String` **literal** in your source is interned (lazily, the first time that literal is resolved), so identical literals across your whole program are *the same object*.

```java
String a = "hello";
String b = "hello";
a == b;              // true   ← both point at the pooled instance

String c = new String("hello");
a == c;              // false  ← `new` always allocates fresh
a.equals(c);         // true   ← value comparison. THIS is what you want.

String d = c.intern();
a == d;              // true   ← intern() returns the pooled instance

String e = "hel" + "lo";         // folded by javac into the literal "hello"
a == e;                          // true

String part = "hel";             // not `final`, so not a compile-time constant
String f = part + "lo";
a == f;                          // false  ← the trap
```

⚠️ **The #1 Java trap for people coming from JS.** `==` on strings works in your test (literals) and fails in production (strings from request bodies, DB rows, file reads).

```java
if ("ACTIVE".equals(status)) { ... }     // null-safe: constant first can never NPE
if (Objects.equals(status, "ACTIVE")) { ... }   // null-safe both ways — preferred
```

🐍 Python has the identical trap with `is` vs `==` and small-string/small-int interning. If `is` has bitten you in Python, this is the same hazard — except Java spells it `==`, which *looks* like value comparison.

### J3.5 StringBuilder internals [+]

```
StringBuilder sb = new StringBuilder();     // byte[16], count = 0

sb.append("hello");
   ┌───┬───┬───┬───┬───┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
   │ h │ e │ l │ l │ o │  │  │  │  │  │  │  │  │  │  │  │   count = 5, capacity = 16
   └───┴───┴───┴───┴───┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

// overflow → newCapacity = (oldCapacity << 1) + 2   ⇒ amortised O(1) append
// toString() copies the used region into a fresh String (the only copy you pay for)
```

- Backed by `byte[]` since Java 9 (**Compact Strings**, JEP 254) with a `coder` flag: `LATIN1` = 1 byte/char, `UTF16` = 2. A pure-ASCII string uses **half** the memory it did in Java 8. Append one emoji and the whole buffer inflates to UTF16.
- **Pre-size when you can:** `new StringBuilder(expectedLength)` avoids every reallocation.
- Fluent — `append` returns `this`.
- Also: `insert`, `delete`, `replace`, `reverse`, `setLength(0)` (cheap reuse).

### J3.6 Decision table [Q11 + extended]

| Situation | Use |
|---|---|
| Any normal variable, field, parameter, return value | `String` |
| Fixed data: config keys, env var names, DB URLs | `String` |
| Keys in a `HashMap` | `String` (immutability makes the cached hash safe) |
| A handful of concatenations in one expression | `String` with `+` — the compiler handles it |
| Building inside a **loop** | **`StringBuilder`** |
| Building conditionally across many branches | **`StringBuilder`** |
| Joining a collection | `String.join(", ", list)` or `Collectors.joining(", ")` |
| Formatting | `"%s scored %d".formatted(name, score)` |
| Multi-line literal (SQL, JSON, HTML) | **text block** `"""…"""` (Java 15+) |
| Shared mutable buffer across threads | ⚠️ rethink; if you truly must, `StringBuffer` — better, give each thread its own `StringBuilder` and merge |
| Log messages | **neither** — SLF4J placeholders: `log.info("user {} did {}", id, action)`. The string is only built if that level is enabled. |

```java
String csv   = String.join(",", List.of("a", "b", "c"));                // "a,b,c"
String names = users.stream().map(User::name).collect(joining(", "));   // "Ana, Bo"

String sql = """
        SELECT id, name
        FROM users
        WHERE status = ?
        """;
```

### J3.7 Cross-language summary [+]

| | Java | Python | JavaScript |
|---|---|---|---|
| Immutable strings | ✅ `String` | ✅ `str` | ✅ (primitive) |
| Mutable builder | `StringBuilder` | `list` + `"".join()` / `io.StringIO` | array + `.join("")` |
| Interning | auto for literals; `intern()` manual | auto for some literals; `sys.intern()` | engine-internal, not exposed |
| Identity vs value | `==` vs `.equals()` | `is` vs `==` | `===` is value for string primitives |
| Loop `+=` cost | O(n²) | O(n²) | usually fine (ropes) |
| Thread-safe builder | `StringBuffer` | n/a (GIL) | n/a (single-threaded) |

### J3.8 Gotchas checklist [+]

- [ ] Never `==` on strings. `.equals()` / `Objects.equals()`.
- [ ] Never `+=` a string in a loop.
- [ ] Never `log.debug("x = " + expensive())` — use `{}` placeholders.
- [ ] `intern()` is almost never the answer; it can make the string table a bottleneck.
- [ ] `String.split(regex)` takes a **regex**. `"a.b".split(".")` returns an empty array — you need `split("\\.")`.
- [ ] `substring()` copies in Java 7+ (it used to share the backing array and leak memory — old blog posts still warn about this; it's fixed).
- [ ] `isEmpty()` (length 0) ≠ `isBlank()` (Java 11+: length 0 **or** all whitespace).
- [ ] `""` is not `null`, and Java has no truthiness — `if (str)` does not compile.

---

## J4. Checked vs unchecked exceptions [Q10]

> **Your question:** *"checked and unchecked exceptions in java and are they related to js or python i.e are there anything present in python or js like these two"*

### J4.1 The short answer to the cross-language part [Q10]

**No. Python and JavaScript have no equivalent of checked exceptions.** In both, **all exceptions are unchecked** — equivalent to Java's `RuntimeException`. Both are dynamically typed and interpreted; there is no compilation step that could enforce it.

Java is one of very few mainstream languages with this feature, and it remains contested. **C# deliberately rejected it. Kotlin removed it. Scala never enforced it.**

The spiritual successor to the *idea* (make failure visible in the signature) isn't exceptions at all — it's **`Result<T, E>` in Rust** and **`(T, error)` in Go**, which encode failure in the **return type** rather than a side channel. Hold on to that framing; it makes the Java design decision much easier to reason about.

### J4.2 The hierarchy

```
                        Object
                          │
                      Throwable ──────────────────────────┐
                          │                               │
        ┌─────────────────┴───────────────┐               │
        ▼                                 ▼               │
     Error                           Exception            │
  (UNCHECKED)                             │               │
        │                    ┌────────────┴───────────┐   │
  OutOfMemoryError           ▼                        ▼   │
  StackOverflowError   RuntimeException        everything else
  NoClassDefFoundError    (UNCHECKED)             (CHECKED) ◄─┘
  LinkageError                 │                        │
  AssertionError               │                  IOException
                               │                  FileNotFoundException
                    NullPointerException          SQLException
                    IllegalArgumentException      InterruptedException
                    IllegalStateException         ClassNotFoundException
                    IndexOutOfBoundsException     ParseException
                    ArrayIndexOutOfBoundsException  CloneNotSupportedException
                    ClassCastException            TimeoutException
                    NumberFormatException
                    ArithmeticException           (e.g. divide by zero is
                    UnsupportedOperationException  ArithmeticException — UNCHECKED)
                    ConcurrentModificationException
                    DateTimeException
```

**The rule, stated precisely:**
> Everything under `Throwable` is **checked**, *except* the `RuntimeException` subtree and the `Error` subtree.

**Checked = the compiler enforces "handle or declare".** Either `catch` it, or add `throws` to your signature. Neither → **your code does not compile**.

```java
// ❌ does not compile — "unreported exception IOException; must be caught or declared to be thrown"
String read(Path p) {
    return Files.readString(p);
}

// ✅ option A — handle it
String read(Path p) {
    try {
        return Files.readString(p);
    } catch (IOException e) {
        throw new UncheckedIOException("could not read " + p, e);   // translate to unchecked
    }
}

// ✅ option B — declare it, pushing the decision to the caller
String read(Path p) throws IOException {
    return Files.readString(p);
}
```

Unchecked exceptions need neither. `throw new IllegalArgumentException("bad id")` compiles anywhere.

### J4.3 The comparison table

| Feature | Java | Python | JavaScript |
|---|---|---|---|
| Enforced at compile time? | **Yes** (for checked exceptions only) | No | No |
| Syntax requirement | must `try`/`catch` **or** `throws` | optional `try`/`except` | optional `try`/`catch` |
| **File is missing at runtime** | Runtime `FileNotFoundException` *(a runtime error, not a compile error — [§R1 #5](00-start-here.md#5--a-missing-file-is-a-runtime-error-in-java-too-q10))* | Runtime `FileNotFoundError` | Runtime `Error` |
| **You didn't handle/declare the checked exception** | **Compile error** — won't build | nothing; legal | nothing; legal |
| Logical flaw behaviour | Runtime `NullPointerException` | Runtime `AttributeError`/`TypeError` | Runtime `TypeError` |
| Type hierarchy root | `Throwable` | `BaseException` | `Error` |
| Catch all "normal" errors | `catch (Exception e)` | `except Exception as e:` | `catch (e)` |
| Catch everything incl. fatal | `catch (Throwable t)` ⚠️ | `except BaseException:` ⚠️ | same `catch` |
| Multi-catch | `catch (A \| B e)` | `except (A, B) as e:` | one `catch`, then `instanceof` |
| `finally` | ✅ | ✅ | ✅ |
| `else` (runs only if no exception) | ❌ | ✅ `try/except/else` | ❌ |
| Chained cause | `new X("msg", cause)` | `raise X from cause` | `new Error("msg", { cause })` (ES2022) |
| Resource cleanup | `try (var r = open())` | `with open() as f:` | `using r = open()` (ES2026 / TS 5.2) |
| Documented contract | `throws` in the signature — **enforced** | docstring `Raises:` — advisory | JSDoc `@throws` — advisory |

**The code examples from Q10, preserved:**

```python
# Python doesn't force a try-except here.
# If "missing_file.txt" doesn't exist, it crashes AT RUNTIME with FileNotFoundError.
with open("missing_file.txt", "r") as file:
    print(file.read())
```

```javascript
// JavaScript does not force a try-catch here.
// If the fetch fails, it throws a runtime error (or returns a rejected Promise).
fetch('https://invalid-url.xyz')
  .then(response => response.json());
```

### J4.4 Why the distinction exists, and why it's contested [Q10 + extended]

**The intent (1995):** distinguish *recoverable, expected* failures a caller should be forced to think about (a network blip, a missing file — things "outside the programmer's direct control") from *programming bugs* nobody can recover from (a null deref, an off-by-one).

**Why most later languages skipped it** — Q10 named the key reasons; here they are with the mechanics:

1. **`throws` clauses leak up the whole stack.** A low-level `IOException` forces every intermediate method to declare it, coupling layers to each other's implementation details.
2. **It encourages the worst possible code** — the empty catch block, written purely to silence the compiler, which destroys all evidence:
   ```java
   try { risky(); } catch (Exception e) { }   // ⚠️ never, ever
   ```
3. **It doesn't compose with lambdas.** This is the killer in modern Java — [§J4.5](#j45-the-lambda-and-streams-problem-the-modern-pain-point-).
4. **The caller usually can't recover anyway.** In a web service the honest response to a failed DB call is a 500, not a heroic retry at layer 3.

🐍 **Python's counter-philosophy, from Q10:** *"EAFP — Easier to Ask for Forgiveness than Permission."* Run the code, catch exceptions only where handling them is actually meaningful. Contrast with LBYL ("Look Before You Leap"), which Java's checked exceptions nudge you toward.

**Where checked exceptions genuinely help:** at a true API boundary where retry/fallback is real and a caller who ignores it is definitely wrong. `InterruptedException` is the best example in the JDK — swallowing it breaks cancellation for the whole application, and being forced to look at it is a real good.

### J4.5 The lambda and Streams problem (the modern pain point) [+]

*The* practical reason checked exceptions feel dated in 2026.

```java
// ❌ does not compile. Function<T,R>.apply() declares no checked exceptions,
//    so nothing inside a lambda passed to map() may throw one.
List<String> contents = paths.stream()
        .map(p -> Files.readString(p))    // IOException — unreported
        .toList();
```

Three ways out:

```java
// 1. Wrap at the call site (verbose but explicit)
List<String> contents = paths.stream()
        .map(p -> {
            try { return Files.readString(p); }
            catch (IOException e) { throw new UncheckedIOException(e); }
        })
        .toList();

// 2. A reusable adapter (write once, use everywhere)
@FunctionalInterface
interface ThrowingFunction<T, R> { R apply(T t) throws Exception; }

static <T, R> Function<T, R> unchecked(ThrowingFunction<T, R> f) {
    return t -> {
        try { return f.apply(t); }
        catch (RuntimeException e) { throw e; }
        catch (Exception e)        { throw new RuntimeException(e); }
    };
}
List<String> contents = paths.stream().map(unchecked(Files::readString)).toList();

// 3. Lombok's @SneakyThrows — throws a checked exception WITHOUT declaring it.
//    Legal because the JVM does not enforce `throws`; only javac does.
@SneakyThrows
String read(Path p) { return Files.readString(p); }
```

⚠️ Option 3 exposes the real nature of the feature: **checked-ness is a compiler fiction, not a JVM rule.** It's also why Kotlin can call `Files.readString` with no ceremony at all.

### J4.6 `try-with-resources`, multi-catch, `finally` [+]

**`try-with-resources`** is Java's `with`. Anything implementing `AutoCloseable` is closed automatically, in reverse order, even on exception.

```java
try (var in  = Files.newInputStream(src);
     var out = Files.newOutputStream(dst)) {       // out closed first, then in
    in.transferTo(out);
}                                                   // no finally needed
```

🐍 `with open(a) as f, open(b) as g:` — identical semantics. 🟨 `using` (ES2026 explicit resource management, `Symbol.dispose`).

**Suppressed exceptions:** if the body throws *and* `close()` also throws, the body's exception wins and the close exception is attached — `e.getSuppressed()`. Before `try-with-resources`, a hand-written `finally { close(); }` would *lose* the original exception. That's the entire reason the feature exists.

**Multi-catch** (Java 7+):
```java
try { ... }
catch (IOException | TimeoutException e) {    // `e` is effectively final
    log.warn("transient failure", e);
}
```

**`finally` always runs** — including after `return`. ⚠️ Never `return` from a `finally` block: it silently swallows any in-flight exception.

### J4.7 Design guidance for real services [+]

```
                 Can the caller realistically DO something different?
                                     │
                    ┌────────────────┴────────────────┐
                   YES                                NO
                    │                                  │
        Is it part of a stable public                  │
        API boundary where forgetting                  │
        to handle it is definitely a bug?              │
              ┌─────┴─────┐                            │
             YES          NO                           │
              │            │                           │
      CHECKED exception  UNCHECKED             UNCHECKED exception
      (rare — be sure)   exception             (the default; ~95% of cases)
```

1. **Default to unchecked.** Extend `RuntimeException` unless you have a specific reason not to.
2. **Always chain the cause:** `throw new OrderNotFoundException("order " + id, e)`. Losing the cause loses the stack trace.
3. **Translate at layer boundaries.** Don't let `SQLException` reach a controller.
4. **Never swallow.** `catch (Exception e) { }` is always a bug. If you truly intend to ignore it, log at debug with a comment saying why.
5. **Never catch `Throwable`** — you'd catch `OutOfMemoryError` and turn a fatal condition into corrupted state.
6. **`InterruptedException` is special.** Restore the flag:
   ```java
   catch (InterruptedException e) {
       Thread.currentThread().interrupt();   // restore the interrupt status
       throw new ServiceInterruptedException(e);
   }
   ```
7. **Don't use exceptions for control flow.** Constructing one calls `fillInStackTrace()`, which walks the stack — expensive at high frequency. (For a genuine high-rate signalling exception, use the 4-arg `RuntimeException(msg, cause, suppression, writableStackTrace=false)` constructor.)
8. **Put context in the message.** `"order not found"` is useless; `"order not found: id=" + id + ", tenant=" + tenant` is actionable.

**Spring's canonical exception translation** — the most-cited real-world argument in this debate, and directly relevant to everything in Part II:

> JDBC's `SQLException` is **checked**, and its `getErrorCode()` is vendor-specific — so the checked-ness forces you to handle something you cannot meaningfully interpret. Spring catches it and rethrows a member of the **unchecked** `DataAccessException` hierarchy (`DuplicateKeyException`, `OptimisticLockingFailureException`, `DataIntegrityViolationException`…) — *portable across databases* and *not forced on every caller*.

**A custom exception, done properly:**
```java
public class OrderNotFoundException extends RuntimeException {
    private final String orderId;

    public OrderNotFoundException(String orderId) {
        super("Order not found: " + orderId);
        this.orderId = orderId;
    }
    public String orderId() { return orderId; }
}
```
Map it to a 404 with `@ExceptionHandler` — [§W4.11](03-spring-web.md#w411-the-exception-path) and [§W8.8](03-spring-web.md#w88-global-exception-handling-with-problemdetail-).

---


## J5. Data carriers: records vs Lombok

> **Your questions, merged:** *"Lombok, what is this and how it works internally, it's pros and cons, why people say lombok is heavy"* · *"what if i need to have a final class… how to use boilerplate for the final class [using @Value annotation]… can't we use record here, i think that does the same job. what's the difference between using record and lombok @Value annotation"* · *"Java Records vs Lombok"* · *"does it give no arg constructor and allArgsConstructor?"* · *"is Lombok @Value annotation the same as the java record?"*

🐍 The problem this chapter solves is the one `@dataclass` solves in Python: a class that just **holds data** needs a constructor, getters, `equals`, `hashCode` and `toString`, and in plain Java you write all of them by hand. 🟨 In JS you'd just write an object literal.

```
             "I just want a class that carries data"
                              │
            ┌─────────────────┴─────────────────┐
     Must it be mutable?                         │
     (JPA entity, form-backing bean,             │
      builder-heavy legacy code)                 │
            │ YES                                │ NO (DTOs, events, config, values)
            ▼                                    ▼
   Lombok (@Getter/@Setter/…)             Java `record` (16+)  ← default
                                          (Lombok @Value if you need JavaBean
                                           getXxx() names, inheritance, or @Builder ergonomics)
```

### J5.1 The boilerplate problem, and your `ImmutableConfig` example

Your example, with three small fixes: `this.url = url; this.timeout = timeout;` needed a `;` not a `,`, `getTimeout()` must return `int` not `String`, and one stray `}` was removed:

```java
public final class ImmutableConfig {
    private final String url;
    private final int timeout;

    public ImmutableConfig(String url, int timeout) {
        this.url = url;
        this.timeout = timeout;
    }

    public String getUrl()   { return this.url; }
    public int    getTimeout() { return this.timeout; }   // was declared `String` — wouldn't compile
    // + equals(), hashCode(), toString() if you want value semantics — another ~25 lines
}
```

📌 **Correction:** your comment said *"we didn't have the setters because this class is final"*. The two are unrelated:
- **No setters** because the **fields** are `final`. A `final` field can only be assigned once, in the constructor, so a setter couldn't compile.
- The **class** is `final` so nobody can **subclass** it and add mutable state or override a getter, which would quietly break the immutability guarantee.

You need both for a truly immutable type.

### J5.2 Java records (Java 16+)

> *"in java 16 or later, Java introduces its own solution i.e Records. Record is immutable data carrier in java."* Correct. Records were previewed in Java 14 and 15 and became final in **Java 16** (JEP 395).

The same class as above:

```java
public record ImmutableConfig(String url, int timeout) {}
```

What the compiler generates:

| Generated | Detail |
|---|---|
| `private final` fields | one per component (`url`, `timeout`) |
| **Canonical constructor** | `new ImmutableConfig("https://…", 30)`. **Only** this all-components constructor |
| Accessors | `config.url()`, `config.timeout()`. **No `get` prefix.** As you guessed, there are no setters to distinguish them from, so the field name is used |
| `equals` / `hashCode` | value-based, over all components |
| `toString` | `ImmutableConfig[url=https://…, timeout=30]` |
| Class modifiers | implicitly `final`; implicitly `extends java.lang.Record` |

📌 **Correction to your question "does it give a no-arg constructor and an all-args constructor?"** It gives **only** the canonical (all-components) constructor. There is **no no-arg constructor** unless you write one yourself, and any extra constructor must delegate to the canonical one with `this(...)`:

```java
public record ImmutableConfig(String url, int timeout) {
    public ImmutableConfig {                       // "compact" canonical constructor: validation goes here
        Objects.requireNonNull(url, "url");
        if (timeout <= 0) throw new IllegalArgumentException("timeout must be > 0");
    }
    public ImmutableConfig(String url) {           // extra constructor: must call this(...)
        this(url, 30);
    }
}
```

What records **can** do: implement interfaces, have static fields and methods, have instance methods, nest, be generic.
What they **can't** do: extend another class, declare extra *instance* fields, or be made mutable.

⚠️ **Records are only *shallowly* immutable.** `record Order(List<Item> items)` still lets someone call `order.items().add(x)`. Copy defensively in the compact constructor: `items = List.copyOf(items);`.

Where you meet them in Spring: request/response DTOs (Jackson handles records since 2.12), `@ConfigurationProperties` ([§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12)), event payloads ([§C7](02-spring-core.md#c7-spring-application-events)), and Spring Data projections.

### J5.3 Lombok: what it is and how it works internally

> *"it's a java library which reduces boilerplate code for getters, setters, constructors, hash code, loggers… builders at compile time."* Correct. The key words are **at compile time**.

**How it works:**

```
  Foo.java (with @Data)
        │
        ▼
  javac parses source → Abstract Syntax Tree (AST)
        │
        ▼
  javac runs annotation processors (JSR 269) ── Lombok is registered as one
        │                                        (found via META-INF/services)
        │   A *normal* annotation processor may only GENERATE NEW files.
        │   Lombok instead casts into javac's INTERNAL classes
        │   (com.sun.tools.javac.tree.JCTree…) and INSERTS methods
        │   into the existing class's AST.
        ▼
  javac continues on the modified AST → Foo.class
        │
        ▼
  Foo.class contains getX(), setX(), equals()… exactly as if handwritten.
  No Lombok classes are referenced at runtime.
```

So:
- ✅ **Zero runtime cost.** No reflection, no proxies, nothing Lombok-related in the running app. The generated bytecode is equivalent to what you'd write by hand. (The dependency is compile-only: `provided` scope in Maven, `compileOnly` + `annotationProcessor` in Gradle.)
- ⚠️ **It relies on undocumented compiler internals.** That's the "scary" part you noted. Every major JDK release can break it until Lombok ships a fix, and since JDK 16's strong encapsulation of internals, Lombok has had to work around module restrictions to keep reaching into javac.
- IDEs need to understand it too. IntelliJ bundles the Lombok plugin (older versions needed it installed); Eclipse uses a Lombok agent.

### J5.4 The Lombok annotations you'll actually see

| Annotation | Generates | Notes |
|---|---|---|
| `@Getter` / `@Setter` | `getX()` / `setX()` (class- or field-level) | |
| `@ToString` | `toString()` | |
| `@EqualsAndHashCode` | `equals` + `hashCode` | |
| `@NoArgsConstructor` | `Foo()` | needed by JPA ([§J5.6](#j56-why-we-still-need-lombok-mutable-classes-and-jpa-entities)) |
| `@RequiredArgsConstructor` | constructor for all `final` fields (and `@NonNull` uninitialised fields) | **the** idiom for Spring constructor injection |
| `@AllArgsConstructor` | constructor for every field | |
| **`@Data`** | `@Getter` + `@Setter` + `@ToString` + `@EqualsAndHashCode` + **`@RequiredArgsConstructor`** | mutable "bean" |
| **`@Value`** | immutable class: `final` class, `private final` fields, getters, all-args constructor, `equals`/`hashCode`/`toString`, no setters | Lombok docs: equivalent to `final @ToString @EqualsAndHashCode @AllArgsConstructor @FieldDefaults(makeFinal=true, level=PRIVATE) @Getter` |
| `@Builder` | static `builder()` + nested `FooBuilder` class | the Builder pattern without writing it |
| `@With` | `withX(newValue)` returning a modified copy | nice on immutable types |
| `@Slf4j` | `private static final org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(Foo.class);` | then just `log.info(...)` |
| `@SneakyThrows` | throws checked exceptions without declaring them | see [§J4.5](#j45-the-lambda-and-streams-problem-the-modern-pain-point-) |

📌 **Correction:** your note said *"@Data… doesn't include the constructor"*. It **does** include one: `@RequiredArgsConstructor`, which covers the `final` fields. (If the class has no `final` fields that's effectively a no-arg constructor, and none is generated if you wrote a constructor yourself.) What `@Data` doesn't give you is an *all-args* constructor.

`@Slf4j`, before and after, as you described:

```java
// Without Lombok
public class OrderService {
    private static final Logger log = LoggerFactory.getLogger(OrderService.class);
}

// With Lombok
@Slf4j
public class OrderService {
    void place() { log.info("placing order"); }   // `log` is generated
}
```

`@Builder` replaces the hand-written nested builder class you'd otherwise write:

```java
@Value
@Builder
public class ImmutableConfig {
    String url;               // @Value makes these private final
    int timeout;
}

ImmutableConfig cfg = ImmutableConfig.builder().url("https://x").timeout(30).build();
```

Your final class, with Lombok, is just the `@Value` part of that example.

⚠️ **Name clash:** Lombok's `@Value` (`lombok.Value`) and Spring's `@Value` (`org.springframework.beans.factory.annotation.Value`, property injection, [§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12)) are **completely different annotations**. Check the import when one "doesn't work".

### J5.5 Record vs Lombok `@Value`

> *"is Lombok @Value annotation same as the java record?"* Almost the same job, but not identical:

| | Java `record` | Lombok `@Value` |
|---|---|---|
| Part of the language | ✅ no dependency, no IDE plugin, survives every JDK upgrade | ❌ library + compiler hack |
| Immutable fields, all-args constructor, `equals`/`hashCode`/`toString` | ✅ | ✅ |
| Class is `final` | ✅ always | ✅ by default (`@NonFinal` can undo it) |
| Accessor names | `url()` | `getUrl()` (JavaBean style: some older libraries/tools require it) |
| Can extend another class | ❌ (already extends `Record`) | ✅ (it may have a superclass; it just can't *be* subclassed) |
| Extra instance fields | ❌ | ✅ |
| Builder | write it, or put Lombok `@Builder` on the record | `@Builder` |
| Validation in constructor | compact constructor (built in) | write the constructor yourself, or `@NonNull` |
| Pattern matching (`if (o instanceof Point(int x, int y))`) | ✅ record patterns (Java 21) | ❌ |

**Rule of thumb:** for new immutable data types, use a **record**. Reach for Lombok `@Value` when you need JavaBean `getX()` names, a superclass, or you're in a codebase that already standardises on Lombok.

### J5.6 Why we still need Lombok: mutable classes and JPA entities

> *"we still need lombok because immutability isn't always welcome. i.e we might need mutable class eg. in case of jpa entity we need to mutate, setters"* Correct.

A JPA `@Entity` **cannot be a record**:
- The spec requires a public or protected **no-arg constructor**, because Hibernate instantiates first and then fills fields.
- The class and its persistent methods must **not be `final`**, because Hibernate subclasses entities to create lazy-loading proxies.
- Fields are mutated by dirty checking.

A record breaks all three rules. So entities stay ordinary classes, and Lombok removes their boilerplate.

⚠️ **But don't put `@Data` on an entity.** Use the narrower annotations:

```java
@Entity
@Getter @Setter
@NoArgsConstructor(access = AccessLevel.PROTECTED)    // JPA needs it; keep it non-public
public class Order {
    @Id @GeneratedValue private Long id;
    @OneToMany(mappedBy = "order") private List<OrderItem> items = new ArrayList<>();
}
```

Why not `@Data`:
- Its `equals`/`hashCode` use **every field**, including the generated `id` (which changes on persist, so the entity can get "lost" inside a `HashSet`) and lazy collections (touching them outside a transaction → `LazyInitializationException`).
- Its `toString` walks bidirectional relationships forever (`Order → items → order → …` → `StackOverflowError`).

The full entity `equals`/`hashCode` recipe is in the JPA chapter: 🔗 [§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-).

### J5.7 Lombok pros and cons, and what "heavy" really means

| Pros | Cons |
|---|---|
| Removes hundreds of lines of boilerplate | Generated methods are **invisible in source**. You read `@Data` and must *know* what it means. (`delombok` prints the expanded source.) |
| Zero runtime overhead (compile-time only) | Hooks into **javac internals**, so JDK upgrades can break the build until Lombok catches up |
| `@RequiredArgsConstructor` makes constructor injection effortless | Needs IDE support; tooling (static analysis, coverage) must be told the code is generated (`lombok.config`: `lombok.addLombokGeneratedAnnotation = true`) |
| `@Builder`, `@With`, `@Slf4j` are genuinely convenient | Easy to misuse (`@Data` on entities, `@EqualsAndHashCode` on inheritance hierarchies) |

> *"so when people are saying that Lombok is heavy, then it doesn't mean it's heavy at runtime or any performance issue, instead it's considered heavy at compile time, tooling and maintenance level."* Exactly right. "Heavy" is about **coupling**: to compiler internals, to IDE plugins, and to knowledge every reader must carry. It is not about bytes or CPU. That trade-off is why records, which give you the most common Lombok use case natively, are now the preferred default for immutable data.

🔗 Connections: constructor injection with `@RequiredArgsConstructor` → [§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13). Records in `@ConfigurationProperties` → [§C3](02-spring-core.md#c3-configuration-and-environment-variables--the-env-equivalent-q12). Entities → [§D3](04-spring-data.md#d3-jpa-and-hibernate-entity-relationships-).

## J6. Concurrency and multithreading [Q2–Q9]

> **Your questions, merged:** *"is threading module in python (lock, thread, semaphore, event, condition_variable) inspired by java?"* [Q2] · *"do we also need to do .join to wait for that thread, what are the thread states, priorities, how to do thread synchronization, inter thread communication… what are the different method of thread… and what are the other topics which are not there in python multithreading module"* [Q3] · *"explain all states of threads in java with example"* [Q4] · *"explain the usecase of different thread priorities and when should we use them"* [Q5] · *"does priority also affect the thread time allocated by os for cpu execution or it only affect the execution order among them?"* [Q6] · *"multithreading in java is provided by jvm (jre) and not os, and similarly in go and python who provide multithreading?"* [Q7] · *"okay so the thread scheduling is done by jvm?"* [Q8] · *"what is yield method in thread and it's use and is this similar to what we had in python?"* [Q9]

This is the single biggest conceptual gap between your background and Java. 🟨 Node has one thread. 🐍 CPython has a GIL. **Java has real, parallel, OS-level threads, and the entire server model is built on them.**

---

### J6.1 Who actually creates and schedules threads? [Q7, Q8]

> **Your assumption:** *"multithreading in java is provided by jvm (jre) and not os"*

**This is the one thing to un-learn first: no.** For standard Java threads, **the OS kernel creates and schedules them.** The JVM is a middleman that makes a system call and then gets out of the way.

```
Java Code:  new Thread(task).start()
                    │
                    ▼  JVM makes a SYSCALL
            pthread_create()   (Linux/macOS)   |   CreateThread()  (Windows)
                    │
                    ▼  1-to-1 mapping
Host OS:    [ Native OS Kernel Thread ]
                    │
                    ▼
OS Scheduler: decides when to pause, resume, assign CPU time,
              and migrate between cores.  ← the JVM has NO say in this
```

Since **Java 1.3** (over 20 years ago), JVM threads on Linux/Windows/macOS are **1:1 native OS threads**. The green-threads model that existed before that is long gone.

#### The three-language comparison [Q7]

**Java — 1:1 native, OS-scheduled**
```
[ Java Thread Object ] ──── 1:1 Mapping ────► [ Native OS Kernel Thread ]
```
True multi-core parallelism. `new Thread()` costs a real kernel thread (~1 MB of stack reserved by default) — which is why you pool them.

**Python (CPython) — 1:1 native, OS-scheduled, but GIL-serialised**
```
[ Python Thread 1 ] ──┐
[ Python Thread 2 ] ──┼──► [ OS Kernel Threads ] ──► GIL: only 1 active bytecode stream
[ Python Thread 3 ] ──┘
```
`threading.Thread` requests a **real** OS thread via `pthread_create`. The OS genuinely schedules them across cores. But the **Global Interpreter Lock** ensures only one thread executes Python bytecode at any instant. So:
- ✅ Great for **I/O-bound** work — the GIL is released during blocking syscalls.
- ❌ No multi-core speedup for **CPU-bound** work — hence `multiprocessing`.

**Go — M:N, runtime-scheduled**
```
[ Goroutines (100k+) ] ── M:N Multiplexing ──► [ Go Runtime G-M-P Scheduler ] ──► [ Few OS Threads ]
```
🐹 `go doSomething()` makes **no syscall**. The Go runtime places the goroutine (`G`) on a queue, and a small pool of OS worker threads (`M`) — roughly one per logical CPU (`P`) — multiplexes thousands of goroutines across them. Goroutines start with ~2 KB stacks that grow on demand.

#### Summary matrix [Q7]

| Language | Who creates & schedules? | Thread model | CPU execution |
|---|---|---|---|
| **Java** (standard `Thread`) | **OS kernel** | 1:1 (1 JVM thread = 1 OS thread) | True multi-core parallelism |
| **Java** (virtual threads, 21+) | **JVM runtime** (`ForkJoinPool`) | M:N (M virtual → N carrier OS threads) | True multi-core parallelism |
| **Python** (`threading`) | **OS kernel** | 1:1 | Concurrent, but GIL-limited to 1 core for bytecode |
| **Go** (goroutine) | **Go runtime** (G-M-P) | M:N | True multi-core parallelism |

#### The one exception: virtual threads [Q7, Q8]

Java 21's **virtual threads** (Project Loom) are the *only* case where the JVM does its own scheduling:

```
Java Virtual Threads (millions) ──► scheduled by the JVM (ForkJoinPool) ──► few native OS threads
```

- `new Thread()` / `Thread.ofPlatform()` → **OS kernel schedules it.**
- `Thread.ofVirtual()` / `Executors.newVirtualThreadPerTaskExecutor()` → **JVM schedules it.**

Notice this makes Java's virtual threads architecturally **the same model as Go's goroutines**. Full detail in [§J6.12](#j612-virtual-threads-and-structured-concurrency-).

---

### J6.2 Python's `threading` module is a port of Java's [Q2]

> **Your hypothesis:** *"I think python implemented/referenced java configuration and not the other way around"*

**You are correct, and Python says so in its own source.** From CPython's `Lib/threading.py`:

> *"This module is a thin wrapper around the `_thread` module... The design of this module is loosely based on Java's threading model."*
> *"...inherited the convention of camelCase function and method names from that language."*

The history: **Java shipped in 1995 with built-in threading primitives.** Python's high-level `threading` module arrived in **Python 1.5** to mimic Java's object-oriented threading design. That's why Python has `notifyAll()` at all — it is literally Java's `Object.notifyAll()`. PEP 8 later added snake_case aliases (`notify_all()` alongside `notifyAll()`), and in Python 3.10+ the camelCase spellings are deprecated.

**This is genuinely good news for you:** most of Python's `threading` API translates to Java almost 1:1.

#### Core primitive mapping [Q2]

| Concept | Java | Python | How they compare |
|---|---|---|---|
| **Thread** | `java.lang.Thread` | `threading.Thread` | Python mirrors Java's lifecycle exactly: `start()`, `run()`, `join()`. |
| **Mutex / Lock** | `ReentrantLock` or `synchronized` block | `threading.Lock` / `threading.RLock` | **Key difference:** in Java, *every* `Object` has a built-in lock (monitor). In Python, locks are standalone objects you must create. |
| **Semaphore** | `java.util.concurrent.Semaphore` | `threading.Semaphore` | Identical: a counter limiting concurrent access. |
| **Event** | no direct equivalent — `CountDownLatch` (one-shot) or custom `wait`/`notify` | `threading.Event` | Python has a dedicated resettable `Event` with `set()`, `clear()`, `wait()`. Java's `CountDownLatch` is **one-shot** (cannot be reset). |
| **Condition variable** | `Condition` (from `Lock.newCondition()`) or `Object`'s built-in monitor | `threading.Condition` | Java: `await()` / `signal()` / `signalAll()` on a `Condition`, **or** `wait()` / `notify()` / `notifyAll()` on any object monitor. Python: `wait()`, `notify()`, `notify_all()`. |
| **Thread-local** | `ThreadLocal<T>` | `threading.local()` | Same idea. |
| **Barrier** | `CyclicBarrier` | `threading.Barrier` | Same idea. |

---

### J6.3 Creating threads, `start()` vs `run()`, and `join()` [Q2, Q3]

#### The three ways to define a thread in Java

```java
// 1. Extend Thread (the Python-familiar way — mirrors subclassing threading.Thread)
class MyThread extends Thread {
    public void run() { System.out.println("Thread running in Java"); }
}
new MyThread().start();

// 2. Implement Runnable and pass it (PREFERRED — favours composition over inheritance)
Runnable task = () -> System.out.println("running");
new Thread(task).start();

// 3. Don't manage threads at all — use an executor (what you'll actually do)
ExecutorService pool = Executors.newFixedThreadPool(4);
pool.submit(task);
```

🐍 Python equivalent of #1, from Q2 — note how close it is:
```python
import threading

class MyThread(threading.Thread):
    def run(self):
        print("Thread running in Python")

t = MyThread()
t.start()   # spawns new thread, calling run()
t.join()    # main thread waits for t to complete
```

⚠️ **`start()` vs `run()` — the classic interview question and a real bug.**

| | What it does |
|---|---|
| `t.start()` | Asks the OS for a new thread; that new thread executes `run()`. **Returns immediately.** |
| `t.run()` | An **ordinary method call on the current thread.** No new thread. No concurrency. Compiles fine, silently does the wrong thing. |

A `Thread` can only be started **once** — a second `start()` throws `IllegalThreadStateException`. (Same in Python: `RuntimeError: threads can only be started once`.)

#### Do we need `.join()`? [Q3]

> **Your question:** *"okay so do we also need to do .join to wait for that thread"*

**Yes — and it means exactly what it means in Python.**

`start()` runs the thread **asynchronously in the background**. The parent thread continues immediately, without waiting. If you need the child's work to be finished before proceeding, you must `join()`:

```java
Thread t1 = new Thread(() -> { /* heavy work */ });
t1.start();
t1.join();   // main thread BLOCKS here until t1 finishes (main enters WAITING state)
```

`join(long millis)` waits with a timeout (and puts the caller in `TIMED_WAITING`).

⚠️ A raw `Thread` **cannot return a value** from `run()` — `run()` is `void`. You must write into a shared field (and synchronise it). This is precisely the limitation that `Callable`/`Future` solves — see [§J6.10](#j610-what-java-has-that-pythons-threading-module-doesnt-q3).

**Daemon threads** [+]: `t.setDaemon(true)` before `start()` marks a thread as a background thread — **the JVM exits when only daemon threads remain**, without waiting for them. 🐍 Exactly Python's `t.daemon = True`. Use it for schedulers/heartbeats you don't want blocking shutdown; **never** for anything that must finish writing.

---

### J6.4 The six thread states [Q4]

> **Your question:** *"could you please explain all states of threads in java with example"*

#### Four details worth pinning [Q4]

- **There is no separate `RUNNING` state.** `RUNNABLE` covers both "actively executing CPU instructions" *and* "ready, waiting for a CPU time slice from the OS scheduler." It is not about waiting for dependent resources.
- **A thread blocked on a network or disk I/O syscall also shows as `RUNNABLE`**, because the JVM cannot see into the kernel — a frequent source of confusion when reading thread dumps.
- **`BLOCKED` means exactly one thing:** waiting to acquire an intrinsic `synchronized` monitor lock currently held by another thread. Nothing else. `Thread.sleep()` is **`TIMED_WAITING`**; blocking I/O is **`RUNNABLE`**; `WAITING` is `object.wait()` / `thread.join()` / `LockSupport.park()` with **no timeout**.
- **`TIMED_WAITING` does not fail or throw when the timer expires.** The timeout simply wakes the thread automatically, so it returns to `RUNNABLE` without needing another thread to notify it.
- **`TERMINATED` is also entered on an uncaught exception**, and a terminated thread **cannot be restarted**.

#### The six states

| State | What the thread is doing | How it enters | How it exits |
|---|---|---|---|
| **NEW** | Created, not yet running | `new Thread()` | `.start()` |
| **RUNNABLE** | Executing, or ready and waiting for a CPU slice (also: blocked in a kernel I/O syscall) | `.start()`, or returning from a wait/block | scheduler yields, or the thread calls a waiting method |
| **BLOCKED** | Waiting to enter a `synchronized` block/method | contended intrinsic lock | the lock becomes available |
| **WAITING** | Waiting indefinitely to be woken by another thread | `.wait()`, `.join()`, `LockSupport.park()` — **no timeout** | `.notify()`, `.notifyAll()`, `unpark()`, or the joined thread dies |
| **TIMED_WAITING** | Waiting for a bounded period | `Thread.sleep(ms)`, `.wait(t)`, `.join(t)`, `lock.tryLock(t, u)`, `parkNanos` | timeout expires **or** explicit notify |
| **TERMINATED** | Finished | `run()` returns, or an uncaught exception | final state — cannot be revived |

```
             new Thread(...)
                   │
                   ▼
               ┌───────┐
               │  NEW  │
               └───┬───┘
                   │ start()
                   ▼
            ┌─────────────┐◄──────────────────────────────┐
   ┌───────►│  RUNNABLE   │──── synchronized (contended) ──┼──► ┌─────────┐
   │        │ (ready OR   │                                │    │ BLOCKED │
   │        │  running)   │◄───── lock acquired ───────────┼────┴─────────┘
   │        └──────┬──────┘                                │
   │               │                                       │
   │   wait()/join()/park()          sleep(t)/wait(t)/join(t)
   │               │                                       │
   │               ▼                                       ▼
   │        ┌─────────────┐                       ┌────────────────┐
   └────────┤   WAITING   │                       │ TIMED_WAITING  ├───┐
 notify()   └─────────────┘                       └────────────────┘   │
 notifyAll()                                        timeout expires ───┘
                   │
            run() returns / uncaught exception
                   ▼
            ┌──────────────┐
            │  TERMINATED  │   (terminal — cannot restart)
            └──────────────┘
```

#### The demo program from Q4 — and why its output isn't reliable

Q4 gave this program and claimed a fixed output:

```java
public class ThreadStatesDemo {
    private static final Object lock = new Object();
    public static void main(String[] args) throws InterruptedException {
        Thread workerThread = new Thread(() -> {
            try {
                Thread.sleep(1000);              // TIMED_WAITING
                synchronized (lock) {            // BLOCKED
                    lock.wait();                 // WAITING
                }
            } catch (InterruptedException e) { e.printStackTrace(); }
        });

        System.out.println("1. State after creation: " + workerThread.getState());  // NEW
        workerThread.start();
        System.out.println("2. State after start(): " + workerThread.getState());   // RUNNABLE
        Thread.sleep(200);
        System.out.println("3. State during sleep(): " + workerThread.getState());  // TIMED_WAITING
        synchronized (lock) {
            Thread.sleep(1000);
            System.out.println("4. State waiting for lock: " + workerThread.getState()); // BLOCKED
            lock.notify();
        }
        Thread.sleep(200);
        System.out.println("5. State during wait(): " + workerThread.getState());   // WAITING
        synchronized (lock) { lock.notify(); }
        workerThread.join();
        System.out.println("6. State after execution ends: " + workerThread.getState()); // TERMINATED
    }
}
```

⚠️ **Two real problems with that demo:**

1. **Every state read is a race** — the program coordinates by `Thread.sleep()`, which guarantees nothing. Line 2 (`RUNNABLE`) is the worst offender: on a fast machine the worker may already be inside `Thread.sleep(1000)`, so you'd print `TIMED_WAITING`.
2. **The first `lock.notify()` is a lost wakeup.** It fires while the worker is `BLOCKED` (still trying to *enter* the synchronized block), not `WAITING`. A `notify()` with nobody waiting is silently discarded. The program only works because a *second* `notify()` follows later. **This is the single most common `wait`/`notify` bug** — and the reason [§J6.8](#j68-inter-thread-communication-wait--notify--notifyall-q2-q3) insists on a state guard.

#### A deterministic version [+]

Poll for the state you expect instead of sleeping, and pair `notify` with a guard flag:

```java
public class ThreadStatesDemo {
    private static final Object lock = new Object();
    private static boolean ready = false;          // the GUARD — guarded by `lock`

    public static void main(String[] args) throws InterruptedException {
        Thread worker = new Thread(() -> {
            try {
                Thread.sleep(300);                 // → TIMED_WAITING
                synchronized (lock) {              // → BLOCKED (main holds the lock)
                    while (!ready) lock.wait();    // → WAITING  (always loop, never `if`)
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }, "worker");

        print(worker);                                    // NEW          — deterministic

        worker.start();
        await(worker, Thread.State.TIMED_WAITING);
        print(worker);                                    // TIMED_WAITING — deterministic

        synchronized (lock) {
            await(worker, Thread.State.BLOCKED);
            print(worker);                                // BLOCKED       — deterministic
        }                                                 // lock released → worker enters, waits

        await(worker, Thread.State.WAITING);
        print(worker);                                    // WAITING       — deterministic

        synchronized (lock) {
            ready = true;                                 // set the guard BEFORE notifying
            lock.notifyAll();                             // now the wakeup cannot be lost
        }

        worker.join();
        print(worker);                                    // TERMINATED    — deterministic
    }

    /** Spin until the thread reaches the expected state. */
    static void await(Thread t, Thread.State want) {
        while (t.getState() != want) Thread.onSpinWait();
    }
    static void print(Thread t) {
        System.out.println(t.getName() + " -> " + t.getState());
    }
}
```
```
worker -> NEW
worker -> TIMED_WAITING
worker -> BLOCKED
worker -> WAITING
worker -> TERMINATED
```

**`RUNNABLE` is the one state you can't pin down this way** — by definition it's the transient state. To observe it, watch a CPU-spinning thread:
```java
Thread spinner = new Thread(() -> { while (!Thread.currentThread().isInterrupted()) { } });
spinner.start();
await(spinner, Thread.State.RUNNABLE);
print(spinner);          // RUNNABLE
spinner.interrupt();
```

💡 **In production you never call `getState()`** — you take a **thread dump**: `jstack <pid>`, or `jcmd <pid> Thread.print`, or `ThreadMXBean` via JMX. That's how you diagnose a hung service: a wall of threads in `BLOCKED` on the same monitor is a lock convoy; a wall in `WAITING` on a connection pool is pool exhaustion.

🐍 **Python has no equivalent `State` enum.** It exposes only `t.is_alive()`. To inspect blocked Python threads you use `faulthandler.dump_traceback()` or `py-spy dump`.

---

### J6.5 Thread priorities [Q5, Q6] — and what they actually do on Linux

> **Your questions:** *"explain the usecase of different thread priorities and when should we use them?"* [Q5] · *"does priority also affect the thread time allocated by os for cpu execution or it only affect the execution order among them?"* [Q6]

#### The API

```java
Thread t = new Thread(task);
t.setPriority(Thread.MAX_PRIORITY);   // 10
```

| Constant | Value |
|---|---|
| `Thread.MIN_PRIORITY` | 1 |
| `Thread.NORM_PRIORITY` | 5 (default) |
| `Thread.MAX_PRIORITY` | 10 |

A new thread inherits its **creator's** priority by default, not `NORM_PRIORITY`.

#### What `setPriority()` actually does on Linux

Priorities are only ever a hint — and **on a default JVM on Linux, `setPriority()` does essentially nothing at all.** Three reasons stack up:

1. **HotSpot's default is `-XX:ThreadPriorityPolicy=0`.** In that mode, on Linux, the JVM does **not** call `setpriority()` for ordinary priority changes. The call returns success and changes nothing.
2. **Linux `SCHED_OTHER`** — the only scheduling class available to a non-root, non-realtime process — **has no static priority.** There is nothing for a "priority" to map onto except the nice value.
3. **Raising priority = lowering nice, which requires root** (`CAP_SYS_NICE`). `-XX:ThreadPriorityPolicy=1` ("aggressive") maps Java 1–10 across the full native range, but **requires root on Linux**, and Oracle's own docs warn it can degrade whole-system performance.

| Platform | Does `setPriority()` do anything? |
|---|---|
| **Linux** (default JVM, non-root) | ❌ **Effectively nothing.** |
| **Linux** (`-XX:ThreadPriorityPolicy=1` **as root**) | ✅ maps to nice values |
| **Windows** | ✅ maps to Windows thread priorities — preemption and longer quanta are real here |
| **Solaris** | ✅ (historically the best-supported platform for this) |

**What this means for you:** in a container on Linux — every backend service you will deploy — treat `setPriority()` as documentation, not behaviour.

*Sources: [Oracle Thread Priorities](https://docs.oracle.com/javase/8/docs/technotes/guides/vm/thread-priorities.html), [JDK-5096173](https://bugs.java.com/bugdatabase/view_bug.do?bug_id=5096173), [javamex](https://www.javamex.com/tutorials/threads/priority_what.shtml)*

#### The mechanism, for the platforms where it *does* work [Q6]

Your question — order vs. time allocation — has a precise answer: **both, but via different mechanisms.**

**1. Execution order (scheduling frequency)** — the primary effect:
- **Preemption:** if a low-priority thread is running and a high-priority thread becomes `RUNNABLE`, the scheduler kicks the low-priority one off the core immediately.
- **Run-queue preference:** when a core frees up, the scheduler picks from the higher-priority pool first.
- **Frequency:** over a 10-second window, a high-priority thread is *dispatched* more often.

**2. Time-slice (quantum) duration** — platform-dependent:
- **Windows:** assigns **dynamic quanta** — higher-priority threads get longer slices *in addition to* being picked first.
- **Linux CFS:** no fixed time slices; it tracks *virtual runtime* weighted by nice value. A lower nice value accumulates vruntime more slowly, so the thread holds the CPU longer before being switched out. *(True of nice values — but as above, the JVM doesn't set them by default.)*
- **Fixed-quantum systems:** priority affects only *how often* a thread is picked, not how long each turn lasts.

So on a platform where priorities work, the net CPU share is skewed by **both** longer turns **and** more turns.

#### The conceptual priority ladder [Q5]

Worth keeping as a mental model of *intent*, even though the mechanism is unreliable:

```
   Priority 10 (MAX_PRIORITY)   ──► UI Rendering, Real-Time Audio/Video
   Priority  7–9                ──► High-Priority Worker Tasks
   Priority  5 (NORM_PRIORITY)  ──► Standard Application Logic
   Priority  2–4                ──► Background I/O, File Downloads
   Priority  1 (MIN_PRIORITY)   ──► Metrics, Telemetry, Log Flushing
```

**High (8–10)** — latency-critical work where lag directly ruins UX:
- UI event processing & rendering (60 FPS animations while heavy compute runs behind)
- Real-time media: audio playback/recording, video frame buffers that stutter if delayed by milliseconds
- Heartbeat / keep-alive pings — a delayed Kafka or ZooKeeper heartbeat can get a healthy node falsely marked dead

**Normal (5)** — the default. Business logic, HTTP request handlers, ordinary DB queries.

**Low (1–3)** — housekeeping that should only run when the system is otherwise idle:
- Secondary cleanup tasks
- Telemetry & metrics batching to Datadog/Prometheus
- Pre-fetching, indexing, cache warming
- Asynchronous log flushing to disk

The Q5 example, preserved:
```java
public class PriorityDemo {
    public static void main(String[] args) {
        Thread audioThread = new Thread(() -> { while (true) processAudioBuffer(); });
        audioThread.setPriority(Thread.MAX_PRIORITY);   // 10

        Thread loggingThread = new Thread(() -> { while (true) flushLogsToFile(); });
        loggingThread.setPriority(Thread.MIN_PRIORITY); // 1

        audioThread.start();
        loggingThread.start();
    }
    private static void processAudioBuffer() { /* real-time work */ }
    private static void flushLogsToFile()   { /* background work */ }
}
```
⚠️ On Linux this program's two threads get **equal** CPU share.

#### When to use priorities — and what to use instead [Q5]

| Problem | `setPriority()`? | Use instead |
|---|---|---|
| Executing tasks in a specific **order** | ❌ No | `CountDownLatch`, `CompletableFuture` chaining, `join()` |
| Stopping background tasks from hogging CPU | 🟡 weak hint at best | **Fixed-size thread pools**, or `PriorityBlockingQueue` |
| Prioritising user requests over background jobs | 🟡 hint only | **Two separate `ExecutorService` pools** (interactive + background) |
| Thread safety / avoiding races | ❌ No | `synchronized`, `ReentrantLock`, atomics |

> **Rule of thumb:** *never rely on thread priorities for core application logic or task ordering. Use concurrent primitives for correctness, and thread priorities purely for performance-tuning hints.* On Linux, drop even the hint.

#### The reliable alternative: `PriorityBlockingQueue` [Q5]

This works identically on every OS, because the ordering happens **in your queue**, not in the kernel:

```java
import java.util.concurrent.*;

class PriorityTask implements Runnable, Comparable<PriorityTask> {
    private final int priority;
    private final String name;

    public PriorityTask(int priority, String name) {
        this.priority = priority;
        this.name = name;
    }

    @Override
    public int compareTo(PriorityTask other) {
        return Integer.compare(other.priority, this.priority);   // high numbers first
    }

    @Override
    public void run() { System.out.println("Executing: " + name); }
}

public class PriorityQueueDemo {
    public static void main(String[] args) {
        ThreadPoolExecutor executor = new ThreadPoolExecutor(
            1, 1, 0L, TimeUnit.MILLISECONDS,
            new PriorityBlockingQueue<Runnable>()
        );
        executor.prestartAllCoreThreads();   // see the trap below — without this, the FIRST task skips the queue

        executor.execute(new PriorityTask(1,  "Low Priority Log Task"));       // execute, NOT submit — see below
        executor.execute(new PriorityTask(10, "CRITICAL: User Payment Processing"));
        executor.execute(new PriorityTask(5,  "Medium Priority Email Task"));
        executor.shutdown();
    }
}
```
```
Executing: CRITICAL: User Payment Processing      (typical; see the caveat on timing below)
Executing: Medium Priority Email Task
Executing: Low Priority Log Task
```

⚠️ **Three traps in the original Q5 snippet** (which used `submit` and no pre-start, and claimed the output above):
1. **`submit()` wraps your `Runnable` in a `FutureTask`, which is not `Comparable`.** `PriorityBlockingQueue` casts every element to `Comparable`, so `submit()` fails with a `ClassCastException` as soon as a task is queued (it doesn't "silently" mis-order). Use `execute(task)`, or give the queue a `Comparator` that unwraps the task.
2. **The first task bypasses the queue.** While the pool has fewer than `corePoolSize` threads, `ThreadPoolExecutor` starts a new worker and hands it that task *directly* as its first task. Without `prestartAllCoreThreads()` the low-priority task runs first.
3. **Timing.** Even pre-started, the idle worker may grab the first task before the other two are queued. Priority ordering only applies among tasks *waiting in the queue at the same time*, which is exactly the situation it's designed for: a backlog.

🐍 **Python has no thread priorities at all** — your instinct in Q3 was right. The Python idiom is exactly this pattern: `queue.PriorityQueue` feeding a worker pool. So the *correct* Java answer and the *only* Python answer converge.

---

### J6.6 `Thread.yield()` [Q9]

> **Your question:** *"what is yield method in thread and it's use and is this similar to what we had in python?"*

`Thread.yield()` is a **static** method: a voluntary hint to the scheduler that the current thread is willing to give up its remaining CPU slice so other threads of equal (or higher) priority can run.

What happens:
1. The thread goes from *running* back to **`RUNNABLE`** (Java has no separate RUNNING state, so `getState()` shows no change).
2. It moves to the back of the ready queue for its priority level.
3. The scheduler picks another `RUNNABLE` thread — **possibly the same one again** if nothing else is ready.

```java
public class YieldExample implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println(Thread.currentThread().getName() + " running: " + i);
            Thread.yield();     // hint the scheduler to let another thread take the CPU
        }
    }

    public static void main(String[] args) {
        new Thread(new YieldExample(), "Thread-A").start();
        new Thread(new YieldExample(), "Thread-B").start();
    }
}
```

#### Three characteristics that matter [Q9]

1. **It's only a HINT.** The scheduler is free to ignore it entirely. On some OSes/architectures it does literally nothing.
2. ⚠️ **It does NOT release locks.** If the yielding thread holds a `synchronized` monitor, it keeps it. Threads waiting on that lock stay `BLOCKED`. *(This is the difference from `wait()`, which **does** release the monitor — see [§J6.8](#j68-inter-thread-communication-wait--notify--notifyall-q2-q3).)*
3. **It's non-blocking.** Unlike `Thread.sleep(ms)` or `wait()`, it doesn't suspend for a duration — it returns to the ready queue immediately.

#### When to use it [Q9]

Rare in modern code, but real:
- **Busy-spin / spin-wait loops** — in lock-free data structures (`java.util.concurrent` internals do this), yielding inside a spin loop stops it burning 100 % of a core.
- **Forcing interleavings in tests** — inserting `yield()` to provoke race conditions and verify thread safety.

**Avoid it in application logic.** Behaviour depends entirely on the OS scheduler, so relying on it for correctness or timing produces non-deterministic bugs. Use `CountDownLatch`, `Semaphore`, or `ReentrantLock` instead.

💡 **Modern replacement** [+]: since Java 9, **`Thread.onSpinWait()`** is the right call inside a spin loop. It emits a CPU `PAUSE` instruction (x86) / `YIELD` (ARM), telling the *processor* — not the OS — that this is a spin-wait, which reduces power and memory-order violation penalties. It does not give up the time slice. Use `onSpinWait()` for short spins, `yield()` never, `park()`/a real lock for long waits. *(The deterministic demo in [§J6.4](#j64-the-six-thread-states-q4) uses `onSpinWait()`.)*

#### The Python comparison [Q9]

🐍 **Python threads:** there is no `threading.yield()`. The idiom is `time.sleep(0)`:
```python
import time, threading

def worker():
    for i in range(5):
        print(f"{threading.current_thread().name} running: {i}")
        time.sleep(0)   # yields the slice and drops the GIL
```

⚠️ **`time.sleep(0)` is a best-effort hint, not a guaranteed switch** — exactly like `Thread.yield()`. It *does* release the GIL, but since **Python 3.2** thread switching is governed by `sys.setswitchinterval()` (default **5 ms**), not a bytecode counter, so another thread may not actually be scheduled.

🐍 **Python asyncio:** `await asyncio.sleep(0)` yields control back to the **event loop**. This one *is* a guaranteed switch — cooperative multitasking has no OS scheduler to disagree with you.
```python
async def worker(name):
    for i in range(5):
        print(f"{name} running: {i}")
        await asyncio.sleep(0)   # guaranteed yield to the event loop
```
*(Note: Python's `yield` **keyword** in generators is unrelated — that's producing values and pausing a function, not thread scheduling.)*

| Feature | Java `Thread.yield()` | Python `time.sleep(0)` | Python `await asyncio.sleep(0)` |
|---|---|---|---|
| Target | OS thread scheduler | OS scheduler / CPython GIL | asyncio event loop |
| Guarantee | best-effort hint, can be ignored | releases the GIL; switch **not** guaranteed | **guaranteed** switch |
| Lock behaviour | **retains all held locks** | retains Python locks, releases GIL | yields control to the loop |

---

### J6.7 Synchronization: `synchronized`, monitors, and explicit locks [Q2, Q3]

When multiple threads read and write shared data, you get **race conditions**. Synchronization enforces mutual exclusion.

#### A. Intrinsic locks and `synchronized` [Q3]

Java builds mutual exclusion **into the language**, using the **intrinsic lock (monitor)** that every Java object carries.

```java
// Method-level: locks `this`
public synchronized void increment() { count++; }

// Static method: locks the CLASS object (MyClass.class), not an instance
public static synchronized void incrementGlobal() { total++; }

// Block-level: locks a specific object — PREFERRED, narrower critical section
private final Object lockObject = new Object();
public void update() {
    synchronized (lockObject) {
        // critical section
    }
}
```

⚠️ Prefer a **private final lock object** over `synchronized` on `this`. If you lock on `this`, any external code holding a reference to your object can `synchronized (yourObject)` and deadlock you.

Java's monitors are **reentrant**: a thread already holding a lock can re-acquire it (so a synchronized method can call another synchronized method on the same object).

#### B. Explicit locks: `ReentrantLock` [Q2, Q3]

```java
import java.util.concurrent.locks.ReentrantLock;

ReentrantLock lock = new ReentrantLock();

lock.lock();
try {
    // critical section
} finally {
    lock.unlock();     // ALWAYS in finally — an exception must not leak the lock
}
```

🐍 Python's equivalent, and the ergonomic difference:
```python
import threading
lock = threading.Lock()

with lock:                 # context manager releases automatically
    pass                   # critical section
```
Python's `with` is strictly nicer here — Java has no `with` for locks, which is exactly why `synchronized` (which *can't* leak) is preferred for the simple case.

**Why `ReentrantLock` over `synchronized`?** It can do things the keyword cannot:

| Capability | `synchronized` | `ReentrantLock` |
|---|---|---|
| Auto-release on exception | ✅ built in | ❌ you must `finally { unlock(); }` |
| `tryLock()` — give up instead of blocking | ❌ | ✅ |
| `tryLock(5, SECONDS)` — timed acquisition | ❌ | ✅ |
| `lockInterruptibly()` — cancellable wait | ❌ | ✅ |
| Fairness (FIFO) option | ❌ | ✅ `new ReentrantLock(true)` |
| Multiple `Condition`s per lock | ❌ one wait-set | ✅ `lock.newCondition()` — e.g. separate `notFull`/`notEmpty` |
| Works with virtual threads without pinning | ✅ since JDK 24 | ✅ always |

**Default to `synchronized`**; reach for `ReentrantLock` when you need timeouts, interruptibility, fairness, or multiple condition queues.

#### C. The two divergences from Python [Q2]

**1. Object monitors vs. standalone lock objects**
- **Java:** *every* `java.lang.Object` is a built-in mutex + monitor. You can call `.wait()` / `.notify()` on **any object** inside a `synchronized` block. This is why `wait`/`notify` live on `Object` rather than on a `Lock` class.
- **Python:** plain objects have no lock. You must explicitly create a `threading.Lock()` or `threading.Condition()`.

**2. True parallelism vs. the GIL**
- **Java:** native OS threads running in genuine parallel across cores. **Both I/O-bound and CPU-bound work scale.**
- **Python (CPython):** native OS threads, but the GIL means only one executes bytecode at a time. **Great for I/O-bound; no multi-core speedup for CPU-bound** — that's what `multiprocessing` is for.

> 💡 This is the single most important practical consequence: **in Java, threads are the answer for CPU-bound work.** `parallelStream()`, `ForkJoinPool`, and a fixed pool sized to `availableProcessors()` all genuinely use all your cores. Coming from Python, you'll be tempted to reach for processes. Don't.
>
> *(Footnote: PEP 703 free-threaded CPython — the GIL-optional build, officially supported from Python 3.14 — is changing this on the Python side. It doesn't change anything about Java.)*

---

### J6.8 Inter-thread communication: `wait` / `notify` / `notifyAll` [Q2, Q3]

Condition variables let threads coordinate on **state changes** rather than just mutual exclusion — the classic producer/consumer problem.

#### Java, using the object monitor [Q2]

```java
class SharedResource {
    private boolean ready = false;

    public synchronized void waitForCondition() throws InterruptedException {
        while (!ready) {       // ALWAYS a `while`, never an `if`  ← see below
            wait();            // releases the monitor lock, sleeps, re-acquires on wake
        }
    }

    public synchronized void setReady() {
        this.ready = true;     // change state BEFORE notifying
        notifyAll();           // wake ALL waiting threads
    }
}
```

#### Java, using an explicit `Condition` [Q3]

```java
ReentrantLock lock = new ReentrantLock();
Condition condition = lock.newCondition();
boolean ready = false;

// Thread 1: wait for signal
lock.lock();
try {
    while (!ready) {
        condition.await();      // releases the lock and sleeps
    }
} finally {
    lock.unlock();
}

// Thread 2: signal
lock.lock();
try {
    ready = true;
    condition.signalAll();      // wakes waiting threads
} finally {
    lock.unlock();
}
```

#### Python, side by side [Q2]

```python
import threading

cond = threading.Condition()
ready = False

def worker():
    global ready
    with cond:
        while not ready:
            cond.wait()          # releases the lock, waits for notification

def producer():
    global ready
    with cond:
        ready = True
        cond.notify_all()        # or the legacy cond.notifyAll()
```

The structure is **identical**. That's the Java inheritance showing through.

#### The three rules that make `wait`/`notify` actually work [+]

These cause more production bugs than anything else in this section.

1. **You must hold the monitor to call `wait()`/`notify()`.** Otherwise: `IllegalMonitorStateException`.
2. **Always `while`, never `if`.** Two reasons: (a) *spurious wakeups* — the JVM is permitted to wake a waiting thread for no reason at all, and the spec explicitly says so; (b) with `notifyAll()`, several threads wake but only one can win the race, so the others must re-check.
   ```java
   while (!condition) wait();   // ✅ re-checks after every wake
   if    (!condition) wait();   // ❌ proceeds on a spurious wake with the condition false
   ```
3. **Set the state guard *before* calling `notify()`, and notify *while holding* the lock.** A `notify()` with nobody currently waiting is **silently discarded** — the *lost wakeup* problem. This is exactly the bug in the Q4 demo ([§J6.4](#j64-the-six-thread-states-q4)).

**`notify()` vs `notifyAll()`:** `notify()` wakes **exactly one arbitrary** waiting thread. If threads are waiting on *different* conditions in the same wait-set, you can wake the wrong one and deadlock. **Default to `notifyAll()`** unless you can prove all waiters are interchangeable.

💡 **In real code, don't write this at all.** Use `BlockingQueue` (`ArrayBlockingQueue`, `LinkedBlockingQueue`) for producer/consumer, or `CountDownLatch`/`Semaphore`/`CyclicBarrier` for coordination. The `java.util.concurrent` authors already got the `wait`/`notify` right; you probably won't.

---

### J6.9 The complete Java ↔ Python method map [Q3]

> **Your question:** *"what does run, start, wait on condition variable, notify_all, notify(n), condition variable wait, wait for, set, wait, clear etc implemented as"*

| Concept | Java | Python | What it does |
|---|---|---|---|
| `run()` | `public void run()` | `def run(self)` | The thread's entry point — the code that executes. **Never call directly.** |
| `start()` | `thread.start()` | `thread.start()` | Spawns the OS thread and calls `run()` on it. |
| `join()` | `thread.join()` / `join(ms)` | `thread.join()` / `join(timeout)` | Block until the thread finishes. |
| `wait()` | `object.wait()` or `condition.await()` | `condition.wait()` | Release the lock and sleep until notified. |
| `notify()` | `object.notify()` or `condition.signal()` | `condition.notify(n=1)` | Wake **1** waiter (Java) / **n** waiters (Python — Java has no `notify(n)`). |
| `notifyAll()` | `object.notifyAll()` or `condition.signalAll()` | `condition.notify_all()` | Wake **all** waiters. |
| `wait_for(pred)` | ❌ **none** — write `while (!pred) await();` by hand | `condition.wait_for(predicate)` | 🐍 **Python-only convenience.** Waits until a boolean predicate is true. Java makes you write the loop — which is why rule #2 above matters so much in Java. |
| Event `set()` | `CountDownLatch.countDown()` / `CompletableFuture.complete()` | `event.set()` | Flip a flag, releasing all waiters. |
| Event `wait()` | `latch.await()` / `future.get()` | `event.wait()` | Block until the flag is set. |
| Event `clear()` | ❌ **none** — `CountDownLatch` is **one-shot** | `event.clear()` | 🐍 Reset the flag to false. Java has no resettable latch; you allocate a new one, or use a `Phaser`/`Semaphore`. |
| `sleep()` | `Thread.sleep(ms)` (static) | `time.sleep(s)` | Suspend for a duration. Java uses **milliseconds**, Python **seconds**. |
| `yield()` | `Thread.yield()` (static) | `time.sleep(0)` | Hint: give up the CPU slice. |
| `is_alive()` | `thread.isAlive()` | `thread.is_alive()` | Has it started and not yet finished? |
| current thread | `Thread.currentThread()` | `threading.current_thread()` | Reference to the running thread. |
| name | `t.setName()` / `t.getName()` | `t.name` | ⚠️ **Always name your threads** — thread dumps are unreadable otherwise. |
| daemon | `t.setDaemon(true)` | `t.daemon = True` | JVM/interpreter exits without waiting for it. |
| thread-local | `ThreadLocal<T>` | `threading.local()` | Per-thread storage. |
| priority | `t.setPriority(1..10)` | ❌ **none** | See [§J6.5](#j65-thread-priorities-q5-q6--and-what-they-actually-do-on-linux) — and note it barely works in Java either. |
| state | `t.getState()` → 6-value enum | ❌ only `is_alive()` | See [§J6.4](#j64-the-six-thread-states-q4). |
| interrupt | `t.interrupt()` | ❌ **none** | Java has cooperative cancellation; Python has no way to interrupt a thread. |

---

### J6.10 What Java has that Python's `threading` module doesn't [Q3]

> **Your question:** *"what are the other topics which are not there in python multithreading module"*

`java.util.concurrent` (the "JUC" package, designed by Doug Lea) is vastly larger than Python's `threading`, precisely because Java's threads are genuinely parallel and therefore worth optimising.

#### 1. `Callable` and `Future` — return values from threads

A `Thread`'s `run()` is `void` — it **cannot return a value**. `Callable<T>` can, and can throw checked exceptions.

```java
ExecutorService executor = Executors.newSingleThreadExecutor();
Future<Integer> future = executor.submit(() -> {
    return 42;                      // Callable<Integer> — can return a value!
});
Integer result = future.get();      // blocks, returns 42
executor.shutdown();
```
🐍 Python got this later and separately, in `concurrent.futures` (not `threading`).

#### 2. Thread pools and `ExecutorService`

You almost never write `new Thread()` in production — creating an OS thread costs ~1 MB of reserved stack and a syscall.

```java
ExecutorService pool = Executors.newFixedThreadPool(8);
ScheduledExecutorService sched = Executors.newScheduledThreadPool(2);
sched.scheduleAtFixedRate(task, 0, 30, TimeUnit.SECONDS);

pool.shutdown();                                    // no new tasks; finish queued ones
pool.awaitTermination(30, TimeUnit.SECONDS);        // wait for drain
pool.shutdownNow();                                 // interrupt running tasks
```
Java's pooling is far more configurable than Python's `ThreadPoolExecutor` — you control core size, max size, keep-alive, the queue implementation, the `ThreadFactory`, and the `RejectedExecutionHandler`.

#### 3. Atomic variables — lock-free concurrency

```java
AtomicInteger count = new AtomicInteger(0);
count.incrementAndGet();        // thread-safe with NO lock at all
count.compareAndSet(5, 10);     // CAS — the hardware primitive underneath
```
Backed by CPU **compare-and-swap** instructions. Also `AtomicLong`, `AtomicReference<T>`, `AtomicBoolean`, and `LongAdder` (better than `AtomicLong` under heavy contention).
🐍 No equivalent — the GIL makes simple operations *look* atomic, so Python never needed them. ⚠️ But Python's apparent atomicity is a trap too: `x += 1` is **not** atomic in Python either.

#### 4. Read/write locks

```java
ReentrantReadWriteLock rwLock = new ReentrantReadWriteLock();
rwLock.readLock().lock();     // MANY readers can hold this simultaneously
rwLock.writeLock().lock();    // exclusive — blocks all readers and writers
```
Huge win for read-heavy caches. 🐍 No equivalent in `threading`.
[+] Java also has `StampedLock`, which adds **optimistic reads** (read without locking, then validate) — faster still, but not reentrant and easy to misuse.

#### 5. `CountDownLatch` and `CyclicBarrier`

```java
CountDownLatch latch = new CountDownLatch(3);   // ONE-SHOT
// workers: latch.countDown();
latch.await();                                   // main blocks until count hits 0

CyclicBarrier barrier = new CyclicBarrier(3, () -> System.out.println("all arrived"));
// each worker: barrier.await();                 // REUSABLE — resets automatically
```
- **`CountDownLatch`** — wait until N operations complete elsewhere. Cannot be reset.
- **`CyclicBarrier`** — N threads all wait for each other at a rendezvous point, then all proceed. Resets automatically for the next round.

🐍 Python has `threading.Barrier` (≈ `CyclicBarrier`) but **no `CountDownLatch`**; you emulate it with an `Event` plus a counter.

#### 6. Fork/Join and parallel streams

```java
List<Integer> numbers = List.of(1, 2, 3, 4, 5);
numbers.parallelStream().forEach(n -> process(n));   // uses ALL CPU cores automatically
```
The **Fork/Join framework** recursively splits large computations and uses **work stealing** — idle threads take tasks from busy threads' queues.

⚠️ Three cautions: `parallelStream()` uses the shared `ForkJoinPool.commonPool()`; it's only worth it for genuinely CPU-bound work over large collections; and **never do blocking I/O in a parallel stream** — you'll starve the common pool for the whole JVM.

🐍 Impossible in Python's `threading` because of the GIL. The nearest equivalent is `multiprocessing.Pool`, which pays serialisation costs Java doesn't.

#### 7. Concurrent collections [+]

| Instead of | Use |
|---|---|
| `HashMap` + `synchronized` | **`ConcurrentHashMap`** (lock-striped; `compute`, `merge`, `computeIfAbsent` are atomic) |
| `ArrayList` in a read-heavy, write-rare case | `CopyOnWriteArrayList` |
| a hand-rolled producer/consumer | **`BlockingQueue`** (`ArrayBlockingQueue`, `LinkedBlockingQueue`, `SynchronousQueue`) |
| sorted concurrent access | `ConcurrentSkipListMap` |

⚠️ The old `Hashtable`, `Vector` and `Collections.synchronizedMap()` lock the **whole** structure. Never use them in new code.

#### 8. Virtual threads (Java 21+) [Q3, Q7]

Lightweight threads scheduled **by the JVM**, not the OS. Millions on one machine, near-zero memory overhead. See [§J6.12](#j612-virtual-threads-and-structured-concurrency-).

#### 9. `CompletableFuture` [+]

Composable async pipelines — Java's `Promise`. Covered in detail in [§J7](#j7-completablefuture-thenapply-thencompose-exceptionally-q).

---

### J6.11 The Java Memory Model in one page [+]

Not in your chats, but you cannot write correct Java concurrency without it. 🐍🟨 **Neither Python nor Node forces you to learn this** — Python has the GIL, Node has one thread. Java gives you real parallel memory access and you must reason about it.

**The core problem:** each CPU core has its own caches, and both the compiler and the CPU may **reorder** instructions. Without synchronization, a write by thread A may **never become visible** to thread B — not "eventually", *never*.

```java
class Worker implements Runnable {
    private boolean stopped = false;          // ⚠️ NOT volatile

    public void run() {
        while (!stopped) { /* work */ }       // JIT hoists the read out of the loop:
    }                                          //   if (!stopped) while (true) { }
    public void stop() { stopped = true; }     // ← may NEVER be seen. Infinite loop.
}
```

This program runs forever in production and works fine in your IDE — because the JIT only optimises after the method gets hot.

**The fix — `volatile`:**
```java
private volatile boolean stopped = false;     // ✅ every read sees the latest write
```

| Tool | Guarantees |
|---|---|
| **`volatile`** | **Visibility** + **ordering** (a happens-before edge on every read/write). ❌ **NOT atomicity** — `volatile int i; i++` is still broken (read-modify-write is three operations). |
| **`synchronized`** | Mutual exclusion **+** visibility. Releasing a monitor flushes writes; acquiring it invalidates caches. |
| **Atomics** (`AtomicInteger`…) | Visibility **+** atomicity, lock-free via CAS. **This is what you want for counters.** |
| **`final` fields** | Safe publication — correctly-constructed `final` fields are visible to all threads without synchronization. A strong argument for immutable objects. |

**Happens-before**, informally: if action A happens-before action B, everything A wrote is visible to B. Edges are created by unlocking→locking the same monitor, writing→reading the same `volatile`, `Thread.start()`, `Thread.join()`, and every `java.util.concurrent` handoff.

⚠️ **Double-checked locking requires `volatile`.** The famous broken idiom:
```java
private static volatile Singleton instance;   // ← the `volatile` is MANDATORY
public static Singleton get() {
    if (instance == null) {
        synchronized (Singleton.class) {
            if (instance == null) instance = new Singleton();
        }
    }
    return instance;
}
```
Without `volatile`, another thread can see a **non-null but not-yet-constructed** object, because `new` is (allocate, construct, assign) and those can be reordered. *(In Spring you never write this — the container gives you singletons. But you will read it in library code.)*

---

### J6.12 Virtual threads and structured concurrency [+]

**Project Loom**, delivered in **Java 21**, is the biggest change to Java concurrency in 20 years — and it makes Java's model converge with Go's.

```java
// A platform thread: 1:1 with an OS thread, ~1 MB stack. Expensive. Pool it.
Thread.ofPlatform().start(task);

// A virtual thread: scheduled by the JVM on a small carrier pool. ~KB. Create millions.
Thread.ofVirtual().start(task);

// The idiomatic form — a NEW virtual thread per task, no pooling needed
try (var executor = Executors.newVirtualThreadPerTaskExecutor()) {
    for (var id : orderIds) {
        executor.submit(() -> fetchOrderBlocking(id));   // blocking code is FINE
    }
}   // close() waits for all tasks
```

**Why it matters:** when a virtual thread blocks on I/O, the JVM **unmounts** it from its carrier OS thread and mounts another. You write straightforward blocking code and get event-loop-like scalability.

| | Platform threads | Virtual threads |
|---|---|---|
| Backed by | 1 OS thread each | JVM scheduler (`ForkJoinPool`) over few OS threads |
| Cost | ~1 MB stack, syscall to create | ~KB, pure heap |
| Practical count | thousands | **millions** |
| Pool them? | **yes, always** | **no — never pool them.** Create one per task |
| Blocking I/O | occupies an OS thread | unmounts; costs nothing |

🐹 This is Go's goroutine model, ~15 years later. 🐍🟨 And it's how Java answers `async`/`await` without adding the keywords — no function colouring, no `async` infecting every caller.

⚠️ **Caveats:**
- **Pinning:** a virtual thread inside a `synchronized` block used to pin to its carrier thread and defeat the whole mechanism. **[JEP 491 fixed this in JDK 24.]** On **Java 21–23**, prefer `ReentrantLock` over `synchronized` around blocking calls.
- Thread-local-heavy libraries can bloat memory when you have a million threads.
- Virtual threads don't make CPU-bound work faster — they only help when you're **blocked on I/O**.

**In Spring Boot 3.2+**: one property switches Tomcat to one virtual thread per request.
```properties
spring.threads.virtual.enabled=true
```
See [§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads).

**Structured concurrency** (`StructuredTaskScope`) binds task lifetimes to a lexical scope — if one subtask fails, siblings are cancelled automatically. Still a **preview feature as of Java 25 (JEP 505)**, so check your JDK before using it.

### J6.13 `ThreadLocal`, `InheritableThreadLocal` and `ScopedValue`: per-thread context (vs Python's `ContextVar`)

> **Your questions, merged:** *"what is ThreadLocal in spring boot?"* · *"is this similar to contextVar in python?"* · *"…will it have data even if we start new thread inside the one thread which has been assigned at the request, using virtual thread at the start?"*

#### What it is

`ThreadLocal<T>` is **plain Java** (`java.lang.ThreadLocal`, since 1.2), not a Spring feature. It's a variable where **each thread sees its own independent value**:

```java
private static final ThreadLocal<String> TENANT = new ThreadLocal<>();

TENANT.set("acme");      // only the CURRENT thread sees "acme"
TENANT.get();            // "acme" on this thread, null on every other thread
TENANT.remove();         // clear it for this thread
ThreadLocal<SimpleDateFormat> fmt = ThreadLocal.withInitial(() -> new SimpleDateFormat("yyyy-MM-dd"));
```

Under the hood each `Thread` object owns a small map (`ThreadLocalMap`), and the `ThreadLocal` is the key. So the value lives **on the thread**, and it survives exactly as long as the thread does, unless you remove it.

```
 Thread http-nio-8080-exec-1           Thread http-nio-8080-exec-2
 ┌──────────────────────────┐          ┌──────────────────────────┐
 │ ThreadLocalMap           │          │ ThreadLocalMap           │
 │   TENANT  → "acme"       │          │   TENANT  → "globex"     │
 │   SecurityContext → alice│          │   SecurityContext → bob  │
 └──────────────────────────┘          └──────────────────────────┘
      same static TENANT key, different value per thread
```

#### Why Spring leans on it

Spring MVC on a servlet container runs **one request on one thread from start to finish** (thread-per-request, [§W1](03-spring-web.md#w1-servlets-and-the-servlet-container-q42-q43-q44)). Beans are **singletons shared by all threads**, so per-request data can't live in bean fields. A `ThreadLocal` gives "request-scoped" storage without passing a parameter through every method:

| Spring piece | What it keeps in a `ThreadLocal` | Where it's covered |
|---|---|---|
| `SecurityContextHolder` (default strategy) | the logged-in user's `Authentication` | [§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext) |
| `TransactionSynchronizationManager` | the DB connection/session bound to the current `@Transactional` method, so every repository call joins the same transaction | [§D4](04-spring-data.md#d4-transactions-and-query-performance-in-production) |
| `RequestContextHolder`, `LocaleContextHolder` | the current `HttpServletRequest`, the user's `Locale` | [§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder) |
| SLF4J/Logback **MDC** | log fields like a trace ID | [§P5](06-spring-production.md#p5-production-grade-concerns-) |

#### ⚠️ The pool leak, and the fix

Tomcat **reuses** threads. When `exec-1` finishes user A's request it returns to the pool and later serves user B. Anything you `set()` and forget to `remove()` is **still there for user B**. That's a data leak between users (and a memory leak, and a classloader leak on redeploy).

```java
public class TenantContext {
    private static final ThreadLocal<String> CURRENT_TENANT = new ThreadLocal<>();
    public static void setTenantId(String id) { CURRENT_TENANT.set(id); }
    public static String getTenantId()        { return CURRENT_TENANT.get(); }
    public static void clear()                { CURRENT_TENANT.remove(); }   // 🔥 mandatory
}

// Always pair set with remove in a finally (or an interceptor's afterCompletion):
TenantContext.setTenantId(header);
try {
    chain.doFilter(req, res);
} finally {
    TenantContext.clear();
}
```

In Spring the natural place is a filter (`finally`) or a `HandlerInterceptor` (`preHandle` sets, `afterCompletion` clears). `afterCompletion` runs even when the handler threw, but only for interceptors whose `preHandle` returned `true`. The full interceptor version is in 🔗 [§W5](03-spring-web.md#w5-filters-vs-handlerinterceptors).

#### Does a new thread see the value? (your virtual-thread question)

**No, not by default.** A `ThreadLocal` belongs to the thread that set it. Any new thread starts with an **empty** value, and that includes a virtual thread started from your request thread.

| How the child thread is created | Plain `ThreadLocal` | `InheritableThreadLocal` |
|---|---|---|
| `new Thread(...)` / `Thread.ofPlatform()` | ❌ empty | ✅ **copied once, at creation** |
| `Thread.ofVirtual()` / `newVirtualThreadPerTaskExecutor()` | ❌ empty | ✅ copied at creation. Virtual threads inherit by default (`Thread.Builder.inheritInheritableThreadLocals`: "The default is to inherit") |
| Task submitted to an **existing pool** thread (`ExecutorService`, `@Async`, `parallelStream`) | ❌ empty | ⚠️ **wrong value**: the pool thread copied whatever the thread that *created it* had, maybe minutes ago, for another user |

So `InheritableThreadLocal` is fine for threads created per task, and dangerous with pools. The copy happens at thread *creation*, not at task *submission*.

📌 **Correction to the pasted answer:** it said virtual threads in Spring are "typically managed by an executor pool… recycled". Virtual threads are **not pooled**: the idiom is one new virtual thread per task, and Spring Boot's virtual-thread executor (`SimpleAsyncTaskExecutor`) creates a new one each time. Pooled *platform* threads are where inheritance goes wrong.

**The robust fix for pools is to copy context at submission time.** Wrap each task so it captures the caller's values and restores/clears them around the run:

```java
Runnable wrap(Runnable task) {
    String tenant = TenantContext.getTenantId();        // captured on the SUBMITTING thread
    return () -> {
        TenantContext.setTenantId(tenant);              // restored on the WORKER thread
        try { task.run(); } finally { TenantContext.clear(); }
    };
}
```

Spring packages this pattern as a **`TaskDecorator`** on its executors. Framework 6.1+ adds `ContextPropagatingTaskDecorator` (Javadoc: `@since 6.1`), built on Micrometer's context-propagation library. Boot 4.1+ can register it for you with `spring.task.execution.propagate-context=true`. That's covered with `@Async` in 🔗 [§P3](06-spring-production.md#p3-background-work-scheduled-and-async).

⚠️ Never hand the `HttpServletRequest` itself to a background thread. Once the response completes, the container recycles the request object, and the background thread reads garbage or another request's data. Copy the values you need first.

#### `ScopedValue`: the modern replacement (final in Java 25)

`ScopedValue` was an incubator API in Java 20 (JEP 429), a preview in Java 21–24 (JEPs 446, 464, 481, 487), and is **final in Java 25** (JEP 506). JEP 506 made one change on finalising: `ScopedValue.orElse` no longer accepts `null`. The JDK javadoc lists the three problems it fixes in `ThreadLocal`:

> 1. "ThreadLocal does not prevent code in a faraway callee from setting a new value."
> 2. "A ThreadLocal has an unbounded lifetime and thus continues to have a value after a method completes, unless explicitly removed."
> 3. "Inheritance is expensive — the map of thread-locals to values must be copied when creating each child thread."

```java
private static final ScopedValue<String> TENANT = ScopedValue.newInstance();

ScopedValue.where(TENANT, "acme").run(() -> {
    service.handle();          // anywhere below: TENANT.get() == "acme"
});                            // binding ends here — nothing to remove, nothing to leak
```

- **Immutable** inside the scope: there's no `set()`. A nested `where(...)` can rebind for an inner scope only.
- **Bounded lifetime**: the binding exists only while `run`/`call` is executing.
- **Inheritance only through structured concurrency:** *"When using a StructuredTaskScope, scoped value bindings are captured when creating a StructuredTaskScope and inherited by all threads started in that task scope with the fork method."* `StructuredTaskScope` is still a **preview API in Java 25**.

📌 **Corrections to the pasted answer:**
- It said "Java 21 introduced Scoped Values". Java 21 had them only as a **preview**; they are final in 25.
- It said they are "automatically inherited by child threads". **Not** by `new Thread(...)` or by executor tasks: only by `StructuredTaskScope.fork(...)` subtasks.

If your services run Java 17–21, in practice it's `ThreadLocal` + `TaskDecorator` at work today.

#### vs Python's `contextvars.ContextVar`

> *"is this similar to contextVar in python?"* Same **purpose** (implicit per-request state without threading a parameter through every call), different **unit of isolation**:

| | Java `ThreadLocal` | Java `ScopedValue` | Python `ContextVar` (3.7+, PEP 567) |
|---|---|---|---|
| Value is bound to | a **thread** | a **dynamic scope** (a `run(...)` call) | a **context**; each asyncio **Task** runs in its own copy |
| Typical runtime | thread-per-request (Spring MVC) | virtual threads + structured concurrency | event loop (FastAPI/asyncio) |
| Set | `tl.set(v)` | `ScopedValue.where(sv, v).run(...)` | `token = var.set(v)` |
| Clear | `tl.remove()` (**mandatory** with pools) | automatic at scope end | `var.reset(token)` / automatic per task |
| Mutable after set? | ✅ | ❌ | ✅ |
| Child work sees it? | ❌ (✅ with `InheritableThreadLocal`, copied at thread creation) | only `StructuredTaskScope.fork` | a new **Task** gets a copy of the creator's context; `asyncio.to_thread` copies it into the worker thread; a plain `threading.Thread` / `ThreadPoolExecutor` does not |
| Closest Spring idea | `SecurityContextHolder`, `RequestContextHolder` | (future direction) | — |

Why Python needed `contextvars`: with asyncio, **one thread interleaves many requests**, so `threading.local()` would leak values between concurrent requests on the same thread. Java's thread-per-request model never had that problem, which is why `ThreadLocal` has been "good enough" for Spring MVC for 20 years.

Your analogy is exactly right:
- **`ThreadLocal`:** *"Give me a locker, and tie the key to this **worker**."*
- **`ContextVar`:** *"Tie the key to this **job**, even if different workers take turns on it."*
- **`ScopedValue`:** *"Tie the key to this **block of work**, and lock the locker when the block ends."*

🔗 How Spring's holders use this, and what happens to `RequestContextHolder` in `@Async` code → [§W10](03-spring-web.md#w10-request-scoped-context-requestcontextholder-and-localecontextholder).

---

### J6.14 Concurrency checklist [+]

- [ ] Never call `t.run()` when you mean `t.start()`.
- [ ] Always **name** your threads — `new Thread(task, "order-poller")`. Unnamed threads make dumps useless.
- [ ] Use an `ExecutorService`; don't hand-roll `new Thread()` per task.
- [ ] **Always `shutdown()` your executor** — a non-daemon pool thread keeps the JVM alive forever.
- [ ] `wait()` goes in a `while`, never an `if`.
- [ ] Set the state guard **before** `notify()`, and notify **while holding the lock**.
- [ ] Prefer `notifyAll()` to `notify()`.
- [ ] `lock.unlock()` goes in a `finally`.
- [ ] Never swallow `InterruptedException` — restore the flag.
- [ ] Shared mutable flags need `volatile`; shared counters need an atomic.
- [ ] Prefer immutability — a `record` with `final` fields needs no synchronization at all.
- [ ] `ConcurrentHashMap`, not `Hashtable` / `synchronizedMap`.
- [ ] ⚠️ **Spring singleton beans are shared across all request threads — keep them stateless.** ([§C2.9](02-spring-core.md#c29-scopes-and-the-bean-lifecycle))
- [ ] Don't rely on `setPriority()` — it is a no-op on Linux ([§J6.5](#j65-thread-priorities-q5-q6--and-what-they-actually-do-on-linux)).
- [ ] Don't do blocking I/O in `parallelStream()` or on `ForkJoinPool.commonPool()`.

---

## J7. CompletableFuture: thenApply, thenCompose, exceptionally [Q★]

> **Your question (from your Google AI Mode link — no answer text was recoverable, so this section is written from scratch):** *"thenapply vs thencompose and .exceptionally in java? how and when to use them?"*

`CompletableFuture<T>` is Java's `Promise`. If you know `Promise` in JS or `asyncio` in Python, you know 80 % of this — but Java forces one distinction the other two hide, and that distinction is exactly your question.

### J7.1 The one-sentence answer

| Method | Your function returns | You get back | JS equivalent |
|---|---|---|---|
| **`thenApply`** | a **plain value** `U` | `CompletableFuture<U>` | `.then(v => u)` — **map** |
| **`thenCompose`** | **another future** `CompletionStage<U>` | `CompletableFuture<U>` | `.then(v => promise)` — **flatMap** |
| **`exceptionally`** | a fallback value on failure | `CompletableFuture<T>` | `.catch(err => fallback)` |

**Use `thenApply` for a synchronous transformation. Use `thenCompose` when the next step is itself asynchronous. Use `exceptionally` to recover from a failure.**

### J7.2 Why Java needs two methods and JavaScript needs one

This is the heart of it.

```java
CompletableFuture<User> userFuture = fetchUser(id);

// ❌ thenApply with an async function → a NESTED future. Almost never what you want.
CompletableFuture<CompletableFuture<Order>> nested =
        userFuture.thenApply(user -> fetchOrdersAsync(user));   // returns CF<Order>

// ✅ thenCompose FLATTENS it
CompletableFuture<Order> flat =
        userFuture.thenCompose(user -> fetchOrdersAsync(user));
```

🟨 **In JavaScript this problem cannot occur.** The Promise resolution algorithm **auto-unwraps thenables**: if your `.then()` callback returns a promise, the outer promise adopts it. `Promise<Promise<T>>` is not a constructible type. That is why JS needs only `.then()`.

🐍 **In Python it cannot occur either**, because `await` is explicit and unwraps one level at a time: `await g(await f())` reads naturally.

**Java's `CompletableFuture` is an ordinary generic class**, so `CompletableFuture<CompletableFuture<String>>` is a perfectly legal type that the compiler will happily build for you. Hence two methods.

💡 **The pattern is everywhere in Java, under inconsistent names — memorise this row:**

| Container | map (plain value) | flatMap (nested container) |
|---|---|---|
| `Optional<T>` | `map` | `flatMap` |
| `Stream<T>` | `map` | `flatMap` |
| `CompletableFuture<T>` | **`thenApply`** | **`thenCompose`** |
| `Mono<T>` / `Flux<T>` (WebFlux) | `map` | `flatMap` |

If you internalise "`thenApply` = map, `thenCompose` = flatMap", you will never get it wrong again.

### J7.3 Creating futures

```java
// Run a Supplier on a pool, get its result
CompletableFuture<String> a = CompletableFuture.supplyAsync(() -> loadFromDb());
CompletableFuture<String> b = CompletableFuture.supplyAsync(() -> loadFromDb(), myExecutor);  // ✅ preferred

// Run a Runnable — no result
CompletableFuture<Void> c = CompletableFuture.runAsync(() -> sendMetric());

// Already-finished futures
CompletableFuture<String> d = CompletableFuture.completedFuture("cached");
CompletableFuture<String> e = CompletableFuture.failedFuture(new TimeoutException());  // Java 9+

// Manual control — the split-apart form of `new Promise((res, rej) => ...)`
CompletableFuture<String> f = new CompletableFuture<>();
someCallbackApi.onSuccess(f::complete);
someCallbackApi.onError(f::completeExceptionally);
```

⚠️ **`supplyAsync(supplier)` without an executor runs on `ForkJoinPool.commonPool()`**, whose parallelism is `availableProcessors() - 1`. In a small container (1–2 CPUs) that parallelism is ≤ 1, and `CompletableFuture` then falls back to **creating a brand-new thread per task** (its `ThreadPerTaskExecutor`). So the behaviour silently changes with the CPU limit of the pod. Never put blocking I/O on the default — **always pass your own `Executor`** for anything that blocks.

### J7.4 The full transformation table

| Method | Signature of your function | Returns | Notes |
|---|---|---|---|
| `thenApply(fn)` | `T → U` | `CF<U>` | map |
| `thenCompose(fn)` | `T → CompletionStage<U>` | `CF<U>` | flatMap |
| `thenAccept(fn)` | `T → void` | `CF<Void>` | consume the result |
| `thenRun(fn)` | `() → void` | `CF<Void>` | ignores the result |
| `thenCombine(other, fn)` | `(T, U) → V` | `CF<V>` | **zip two independent futures** — they run in parallel |
| `thenAcceptBoth(other, fn)` | `(T, U) → void` | `CF<Void>` | |
| `runAfterBoth(other, fn)` | `() → void` | `CF<Void>` | |
| `applyToEither(other, fn)` | `T → U` from whichever finishes first | `CF<U>` | ≈ `Promise.race` |
| `allOf(cf...)` | — | `CF<Void>` ⚠️ | completes when **all** complete. **Returns `Void`** — see below |
| `anyOf(cf...)` | — | `CF<Object>` | completes when **any** completes |

📌 **Every one of these methods has three forms** — this is a uniform rule, not a per-method quirk:

| Form | Runs your function on |
|---|---|
| `thenApply(fn)` | the thread that completed the future, or the caller if it is already complete |
| `thenApplyAsync(fn)` | `ForkJoinPool.commonPool()` |
| `thenApplyAsync(fn, executor)` | **your** executor ✅ |

Substitute any method name — `thenCompose`/`thenComposeAsync`, `thenCombine`/`thenCombineAsync`, `whenComplete`/`whenCompleteAsync`, `handle`/`handleAsync`. See [§J7.7](#j77-which-thread-runs-your-callback-the-async-gotcha) for why the choice matters.

⚠️ **`thenApply` vs `thenAccept` vs `thenRun` — a three-way distinction JS collapses into one `.then()`:**

```java
cf.thenApply(u  -> u.name())   // takes the value, RETURNS a value  → CF<String>
  .thenAccept(n -> log.info(n))// takes the value, returns nothing  → CF<Void>
  .thenRun(()  -> cleanup());  // IGNORES the value entirely        → CF<Void>
```
The driver is Java's functional-interface types: `Function<T,U>`, `Consumer<T>`, `Runnable`. JavaScript has one callback shape, so `.then()` covers all three.

### J7.5 Error handling: `exceptionally` vs `handle` vs `whenComplete`

```java
CompletableFuture<Order> f = fetchOrderAsync(id);

// 1. exceptionally — runs ONLY on failure. Recover with a fallback value. ≈ .catch()
f.exceptionally(ex -> Order.EMPTY);

// 2. handle — runs ALWAYS. Exactly one of (value, throwable) is non-null.
//    Can turn failure into success OR success into failure (by throwing).
f.handle((order, ex) -> ex != null ? Order.EMPTY : order.withTax());

// 3. whenComplete — runs ALWAYS, but passes the result through UNCHANGED.
//    ≈ .finally() with visibility into both outcomes. For side effects only.
f.whenComplete((order, ex) -> {
    if (ex != null) log.error("order fetch failed", ex);
    else            log.info("fetched {}", order.id());
});

// 4. exceptionallyCompose (Java 12+) — the flatMap of exceptionally: recover ASYNCHRONOUSLY
f.exceptionallyCompose(ex -> fetchFromBackupServiceAsync(id));
```

| | Runs on success | Runs on failure | Can change the result? |
|---|---|---|---|
| `exceptionally` | ❌ | ✅ | ✅ recovers to a value |
| `handle` | ✅ | ✅ | ✅ both directions |
| `whenComplete` | ✅ | ✅ | ❌ **passes through** |

⚠️ If the lambda inside `whenComplete` itself throws, that exception **replaces** the original — a nasty way to lose your real error. Keep `whenComplete` bodies trivial.

### J7.6 The `CompletionException` wrapping gotcha

This catches everyone once.

```java
CompletableFuture.supplyAsync(() -> { throw new IllegalStateException("boom"); })
    .exceptionally(ex -> {
        ex.getClass();            // → CompletionException, NOT IllegalStateException!
        ex.getCause();            // → IllegalStateException
        return fallback;
    });
```

**The precise rule** (verifiable in the `CompletableFuture` source):
- A supplier or function that **throws** has its exception wrapped: `encodeThrowable()` stores `new CompletionException(x)`.
- `completeExceptionally(ex)` called directly stores the exception **raw, unwrapped**.
- So whether you see the wrapper depends on how the future failed and how many stages deep you are.

**Therefore: always unwrap defensively.**
```java
static Throwable unwrap(Throwable t) {
    return (t instanceof CompletionException || t instanceof ExecutionException)
            && t.getCause() != null ? t.getCause() : t;
}

f.exceptionally(ex -> {
    Throwable cause = unwrap(ex);
    if (cause instanceof NotFoundException) return Order.EMPTY;
    throw new CompletionException(cause);      // rethrow what you can't handle
});
```

### J7.7 Which thread runs your callback? (the `*Async` gotcha)

**The #1 real production bug with `CompletableFuture`.**

| Call | Where the function runs |
|---|---|
| `thenApply(fn)` | If the future is **already complete**: on the **calling thread**, inline & synchronously. If not: on **whichever thread completes the future**. |
| `thenApplyAsync(fn)` | On `ForkJoinPool.commonPool()`. |
| `thenApplyAsync(fn, executor)` | On **your** executor. ✅ **This is what you want in a server.** |

Why it bites:
```java
httpClient.sendAsync(req, handler)              // completes on the HTTP client's I/O thread
          .thenApply(resp -> heavyBlockingDbCall(resp));   // ⚠️ runs ON THAT I/O THREAD
```
You have just done a blocking database call on a Netty/HttpClient event-loop thread. Under load, every HTTP response in the JVM stalls behind it. The fix is one word plus an executor:
```java
          .thenApplyAsync(resp -> heavyBlockingDbCall(resp), dbExecutor);   // ✅
```

**Rule of thumb:** `thenApply` for cheap, pure, non-blocking transforms. `thenApplyAsync(fn, yourExecutor)` for anything else.

### J7.8 Fan-out: the `Promise.all` / `asyncio.gather` equivalent

`allOf` returns `CompletableFuture<Void>` — it can't return a typed list, because the inputs may have different types. The idiom:

```java
List<CompletableFuture<Order>> futures = ids.stream()
        .map(id -> fetchOrderAsync(id, executor))
        .toList();

CompletableFuture<List<Order>> all = CompletableFuture
        .allOf(futures.toArray(CompletableFuture[]::new))          // CF<Void>, completes when all do
        .thenApply(v -> futures.stream()
                               .map(CompletableFuture::join)        // safe — all are complete
                               .toList());
```

🟨 `Promise.all(promises)` · 🐍 `await asyncio.gather(*coros)` — both do this in one call. Java makes you do the two-step because of type erasure.

⚠️ `allOf` fails fast on the **first** failure. For "collect successes and failures" (≈ `Promise.allSettled`), give each future its own `.handle(...)` before the `allOf`.

### J7.9 `join()` vs `get()`

```java
String s1 = future.join();     // throws UNCHECKED CompletionException
String s2 = future.get();      // throws CHECKED ExecutionException + InterruptedException
```
**Prefer `join()`** — it composes with lambdas and streams (`get()` does not, because of [§J4.5](#j45-the-lambda-and-streams-problem-the-modern-pain-point-)). Use `get(timeout, unit)` when you need a bounded wait.

⚠️ **Both block the calling thread.** Calling `.join()` inside a Spring MVC controller undoes the point of being async. Either return the `CompletableFuture<T>` from the controller (Spring MVC supports that natively and frees the Tomcat thread — [§W4.15](03-spring-web.md#w415-threading-model-thread-per-request-async-webflux-virtual-threads)), or just write blocking code on a virtual thread.

### J7.10 Timeouts, retries, and cancellation

```java
// Java 9+
future.orTimeout(3, TimeUnit.SECONDS);                    // fail with TimeoutException
future.completeOnTimeout(Order.EMPTY, 3, TimeUnit.SECONDS); // fall back to a default
```

```java
// Retry (immediately, no backoff — add a delay with CompletableFuture.delayedExecutor if you need one)
static <T> CompletableFuture<T> retry(Supplier<CompletableFuture<T>> op, int attempts) {
    return op.get().exceptionallyCompose(ex ->
        attempts <= 1 ? CompletableFuture.failedFuture(ex) : retry(op, attempts - 1));
}
```

⚠️ **`cancel(true)` does NOT interrupt the running task.** The Javadoc says `mayInterruptIfRunning` "has no effect in this implementation". A cancelled `supplyAsync` task keeps running to completion; only the *future* is marked cancelled. If you need real cancellation, use `Future` from an `ExecutorService`, or virtual threads with structured concurrency.

### J7.11 Cross-language cheat sheet

| Task | Java `CompletableFuture` | JS `Promise` | Python `asyncio` |
|---|---|---|---|
| Start async work | `supplyAsync(fn, exec)` | `new Promise(...)` / `async fn()` | `asyncio.create_task(coro())` |
| Transform (sync) | `thenApply(fn)` | `.then(v => u)` | `u = f(await t)` |
| Chain (async) | **`thenCompose(fn)`** | `.then(v => promise)` | `u = await g(await t)` |
| Side effect | `thenAccept(fn)` | `.then(v => {...})` | — |
| Two in parallel | `thenCombine(other, fn)` | `Promise.all([a,b])` | `asyncio.gather(a, b)` |
| N in parallel | `allOf(...)` + join ([§J7.8](#j78-fan-out-the-promiseall--asynciogather-equivalent)) | `Promise.all(arr)` | `asyncio.gather(*arr)` |
| First to finish | `anyOf(...)` / `applyToEither` | `Promise.race(arr)` | `asyncio.wait(..., FIRST_COMPLETED)` |
| Catch | **`exceptionally(fn)`** | `.catch(fn)` | `try/except` around `await` |
| Finally | `whenComplete(fn)` | `.finally(fn)` | `finally:` |
| Always, transforming | `handle(fn)` | `.then(ok, err)` | `try/except/else` |
| Await the value | `join()` (blocks!) | `await p` | `await t` |
| Timeout | `orTimeout(3, SECONDS)` | `Promise.race` + timer | `asyncio.wait_for(t, 3)` |

### J7.12 The Java 21+ postscript: you may not need any of this

```java
// CompletableFuture style — composable but hard to read and debug
CompletableFuture<Invoice> f = fetchUserAsync(id)
    .thenCompose(user -> fetchOrdersAsync(user.id()))
    .thenCombine(fetchPricingAsync(), Invoice::new)
    .exceptionally(ex -> Invoice.EMPTY);

// Virtual-thread style — plain blocking code, run on a virtual thread
// (e.g. the request thread itself when spring.threads.virtual.enabled=true)
Invoice loadInvoice(String id) {
    try {
        var user    = fetchUser(id);          // blocks — and that's FINE on a virtual thread
        var orders  = fetchOrders(user.id()); // blocks
        var pricing = fetchPricing();         // blocks (sequential here; fan out with an executor if it must run in parallel)
        return new Invoice(orders, pricing);
    } catch (Exception ex) {
        return Invoice.EMPTY;
    }
}
```

Stack traces are readable again, debuggers step normally, and `try/catch/finally` just works. **`CompletableFuture` remains essential** for genuine fan-out/fan-in, for library APIs, and for pre-21 codebases — and Spring's `@Async` returns one — but for straight-line sequential I/O on Java 21+, plain blocking code on a virtual thread is now the better default.

---



---

[⬅ 00-start-here.md](00-start-here.md) · [🏠 Start here](00-start-here.md) · [02-spring-core.md ➡](02-spring-core.md)
