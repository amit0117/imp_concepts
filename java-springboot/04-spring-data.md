# Spring Data — Relational Design, JDBC, JPA and Transactions

[⬅ 03-spring-web.md](03-spring-web.md) · [🏠 Start here](00-start-here.md) · [05-spring-security.md ➡](05-spring-security.md)

> Part of the Java & Spring Boot learning set. Section labels in this file start with **D**. The legend, version landscape, quick revision sheet and glossary live in [00-start-here.md](00-start-here.md).

## Contents

- [D1. Relational design: normalization (1NF, 2NF, 3NF, BCNF)](#d1-relational-design-normalization-1nf-2nf-3nf-bcnf)
  - [D1.1 The vocabulary you need first](#d11-the-vocabulary-you-need-first)
  - [D1.2 Quick comparison](#d12-quick-comparison)
  - [D1.3 1NF — atomic values](#d13-1nf--atomic-values)
  - [D1.4 2NF — no partial dependencies](#d14-2nf--no-partial-dependencies)
  - [D1.5 3NF — no transitive dependencies](#d15-3nf--no-transitive-dependencies)
  - [D1.6 BCNF — every determinant is a superkey](#d16-bcnf--every-determinant-is-a-superkey)
  - [D1.7 One table, all the way from unnormalized to BCNF (worked example)](#d17-one-table-all-the-way-from-unnormalized-to-bcnf-worked-example)
  - [D1.8 Why the foreign key lives on the "many" side](#d18-why-the-foreign-key-lives-on-the-many-side)
- [D2. Connecting to a database: JDBC drivers, DataSource and connection pools](#d2-connecting-to-a-database-jdbc-drivers-datasource-and-connection-pools)
  - [D2.1 The layer cake](#d21-the-layer-cake)
  - [D2.2 What the driver actually does](#d22-what-the-driver-actually-does)
  - [D2.3 Why you need a pool](#d23-why-you-need-a-pool)
  - [D2.4 HikariCP in Spring Boot](#d24-hikaricp-in-spring-boot)
  - [D2.5 Where Spring Data repositories fit, and is `@Repository` needed?](#d25-where-spring-data-repositories-fit-and-is-repository-needed)
  - [D2.6 Connecting to more than one database [+]](#d26-connecting-to-more-than-one-database-)
  - [D2.7 Cheat sheet](#d27-cheat-sheet)
- [D3. JPA and Hibernate entity relationships [+]](#d3-jpa-and-hibernate-entity-relationships-)
  - [D3.1 The core mismatch, stated precisely [+]](#d31-the-core-mismatch-stated-precisely-)
  - [D3.2 Primary keys: `@Id` and `@GeneratedValue` strategies](#d32-primary-keys-id-and-generatedvalue-strategies)
  - [D3.3 The four relationship types at a glance [+]](#d33-the-four-relationship-types-at-a-glance-)
  - [D3.4 Owning side vs inverse side — and what `mappedBy` actually does [+]](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-)
  - [D3.5 Your `mappedBy` questions, answered one by one](#d35-your-mappedby-questions-answered-one-by-one)
  - [D3.6 `@JoinColumn` — every attribute, and the default-name rule [+]](#d36-joincolumn--every-attribute-and-the-default-name-rule-)
  - [D3.7 `@OneToOne` — and the lazy trap that catches everyone [+]](#d37-onetoone--and-the-lazy-trap-that-catches-everyone-)
  - [D3.8 `@ManyToOne` and `@OneToMany` — the pairing you will actually use [+]](#d38-manytoone-and-onetomany--the-pairing-you-will-actually-use-)
  - [D3.9 `@ManyToMany` and `@JoinTable` [+]](#d39-manytomany-and-jointable-)
  - [D3.10 `CascadeType` — the complete list [+]](#d310-cascadetype--the-complete-list-)
  - [D3.11 `orphanRemoval` vs `CascadeType.REMOVE` [+]](#d311-orphanremoval-vs-cascadetyperemove-)
  - [D3.12 `FetchType`, proxies, and lazy loading [+]](#d312-fetchtype-proxies-and-lazy-loading-)
  - [D3.13 The N+1 problem, and every way to fix it [+]](#d313-the-n1-problem-and-every-way-to-fix-it-)
  - [D3.14 `JOIN FETCH` in depth [+]](#d314-join-fetch-in-depth-)
  - [D3.15 `@EntityGraph` [+]](#d315-entitygraph-)
  - [D3.16 `equals` and `hashCode` for entities [+]](#d316-equals-and-hashcode-for-entities-)
  - [D3.17 Schema generation: who creates the tables? [+]](#d317-schema-generation-who-creates-the-tables-)
  - [D3.18 Advanced mappings [+]](#d318-advanced-mappings-)
  - [D3.19 Serializing bidirectional entities to JSON [+]](#d319-serializing-bidirectional-entities-to-json-)
  - [D3.20 The decision checklist [+]](#d320-the-decision-checklist-)
- [D4. Transactions and query performance in production](#d4-transactions-and-query-performance-in-production)
  - [D4.1 Transactions [+]](#d41-transactions-)
  - [D4.2 Which repository methods are transactional by default — and the `deleteBy…` trap](#d42-which-repository-methods-are-transactional-by-default--and-the-deleteby-trap)
  - [D4.3 The N+1 query problem [+]](#d43-the-n1-query-problem-)
- [D5. Spring Data REST [Q22–Q26, Q29–Q31]](#d5-spring-data-rest-q22q26-q29q31)
  - [D5.1 The mental shift, and the two architectural flows [Q22, Q24]](#d51-the-mental-shift-and-the-two-architectural-flows-q22-q24)
  - [D5.2 How routing happens with no `@RequestMapping` [Q22]](#d52-how-routing-happens-with-no-requestmapping-q22)
  - [D5.3 Naming conventions and irregular plurals [Q29]](#d53-naming-conventions-and-irregular-plurals-q29)
  - [D5.4 How Spring knows which field is the primary key [Q24]](#d54-how-spring-knows-which-field-is-the-primary-key-q24)
  - [D5.5 Adding business logic beyond CRUD [Q22, Q24]](#d55-adding-business-logic-beyond-crud-q22-q24)
  - [D5.6 Controlling path variables and query parameters [Q25, Q26]](#d56-controlling-path-variables-and-query-parameters-q25-q26)
  - [D5.7 Projections [Q30] — and what they actually optimise](#d57-projections-q30--and-what-they-actually-optimise)
  - [D5.8 Projections vs DTOs [Q31]](#d58-projections-vs-dtos-q31)
  - [D5.9 Associations and `AggregateReference` [Q26]](#d59-associations-and-aggregatereference-q26)
  - [D5.10 Hiding endpoints, rels, Jackson and CORS [Q26]](#d510-hiding-endpoints-rels-jackson-and-cors-q26)
  - [D5.11 Configuration properties [Q29]](#d511-configuration-properties-q29)
  - [D5.12 When to use it, and when not to [Q22]](#d512-when-to-use-it-and-when-not-to-q22)
- [D6. HATEOAS, HAL and Querydsl [Q27, Q28]](#d6-hateoas-hal-and-querydsl-q27-q28)
  - [D6.1 What HATEOAS is [Q27]](#d61-what-hateoas-is-q27)
  - [D6.2 Why it's required [Q27]](#d62-why-its-required-q27)
  - [D6.3 What HAL is, and why it helps [Q28]](#d63-what-hal-is-and-why-it-helps-q28)
  - [D6.4 Pagination and metadata for collections [Q28]](#d64-pagination-and-metadata-for-collections-q28)
  - [D6.5 The real-world debate: should you actually follow `_links`? [Q28]](#d65-the-real-world-debate-should-you-actually-follow-_links-q28)
  - [D6.6 [+] Spring HATEOAS without Spring Data REST](#d66--spring-hateoas-without-spring-data-rest)
  - [D6.7 Querydsl [Q28]](#d67-querydsl-q28)

---


## D1. Relational design: normalization (1NF, 2NF, 3NF, BCNF)

> **Your question:** *"first normal form, second normal form, third normal form, BCNF"*

**Why this chapter comes first:** every JPA rule in [§D3](#d3-jpa-and-hibernate-entity-relationships-) — "the FK lives on the many side", "many-to-many needs a join table", "use `@ElementCollection` for a list of values" — is a consequence of designing tables this way. Learn the tables, and the annotations stop looking arbitrary.

**Normalization** is the process of structuring relational tables through progressive rules — 1NF, 2NF, 3NF, BCNF — to minimise redundancy and prevent *update anomalies*. Each form builds on the previous one: a table must satisfy all lower forms before it can be in a higher one.

### D1.1 The vocabulary you need first

| Term | Meaning | Example (table `Enrollment(student_id, course_id, student_name, grade)`) |
|---|---|---|
| **Functional dependency** `X → Y` | knowing X *determines* Y: two rows with the same X always have the same Y | `student_id → student_name` |
| **Superkey** | any set of columns that uniquely identifies a row | `{student_id, course_id}`, `{student_id, course_id, grade}` |
| **Candidate key** | a *minimal* superkey (remove any column and it stops being unique) | `{student_id, course_id}` |
| **Primary key** | the candidate key you chose | `(student_id, course_id)` |
| **Prime attribute** | a column that is part of *any* candidate key | `student_id`, `course_id` |
| **Non-prime attribute** | a column in no candidate key | `student_name`, `grade` |

**The three anomalies normalization prevents:**

| Anomaly | What goes wrong |
|---|---|
| **Update** | a fact stored in many rows; you change one copy and the copies now disagree |
| **Insert** | you cannot record a fact without inventing an unrelated one (no course row exists yet, so you can't store a new student's name) |
| **Delete** | deleting one fact destroys another (delete the last enrollment and the student's name vanishes) |

🐍 If you have used Pydantic, a functional dependency is like saying "given `user_id`, `user_name` is fixed". Storing `user_name` on every order row is the database version of copy-pasting a constant.

### D1.2 Quick comparison

| Normal form | Prerequisite | Core rule (precise) | Problem eliminated |
|---|---|---|---|
| **1NF** | — | every cell holds a single **atomic** value; no repeating groups; rows are uniquely identifiable | multi-valued cells, repeating column groups |
| **2NF** | 1NF | no **non-prime** attribute depends on a **proper subset of any candidate key** | partial dependencies on composite keys |
| **3NF** | 2NF | for every non-trivial `X → A`: **X is a superkey, or A is prime** | transitive dependencies (non-key → non-key) |
| **BCNF** | 3NF | for every non-trivial `X → Y`: **X is a superkey** — no exceptions | the remaining case: a non-superkey determining a *prime* attribute |

📌 The mnemonic for 3NF: every non-key attribute must depend on **"the key, the whole key, and nothing but the key"** (1NF, 2NF, 3NF respectively).

### D1.3 1NF — atomic values

**Rule:** every column holds one indivisible value, there are no repeating groups (`phone1`, `phone2`, `phone3`), and every row is uniquely identifiable (a primary key). A column should also hold one kind of value.

**Violation:** an `Employee` table whose `phone_numbers` cell holds `"555-1234, 555-5678"`.

**Fix:** move the phones into their own table, one row per phone, linked by `employee_id`:

```
employee(employee_id PK, name)              employee_phone(employee_id FK, phone, PK(employee_id, phone))
  1 | Ada                                     1 | 555-1234
                                              1 | 555-5678
```

🔗 This is exactly what JPA's `@ElementCollection` generates for a `Set<String> phoneNumbers` ([§D3.18](#d318-advanced-mappings-)), and why `@ManyToMany` always needs a join table ([§D3.9](#d39-manytomany-and-jointable-)).

### D1.4 2NF — no partial dependencies

**Rule:** every non-prime column must depend on the **whole** of every candidate key, not on part of it.

**Violation:** `Enrollment(student_id, course_id, student_name, grade)` with key `(student_id, course_id)`. `student_name` depends only on `student_id` — a *partial* dependency. Rename a student and you must update every enrollment row.

**Fix:**

```
student(student_id PK, student_name)
enrollment(student_id FK, course_id FK, grade, PK(student_id, course_id))
```

📌 A 1NF table is automatically in 2NF when **every candidate key is a single column**, because there is no "part of a key" to depend on. (Saying "when the primary key is a single column" is not quite enough: a table can have a single-column PK *and* another, composite candidate key.)

### D1.5 3NF — no transitive dependencies

**Rule:** a non-key column must not depend on another non-key column. If `A → B` and `B → C`, where A is the key and B, C are non-prime, then C depends on A only *through* B. That is a transitive dependency.

**Violation:** `Student(student_id PK, zip_code, city)`. `student_id → zip_code` and `zip_code → city`. Ten students in one zip store the city ten times.

**Fix:**

```
student(student_id PK, zip_code FK)
location(zip_code PK, city)
```

⚠️ **The real-world caveat.** The zip → city example is the textbook one, but in many countries a postal code does not determine exactly one city. Normalization follows the *actual* dependencies in your domain. Ask whether the dependency is really true before splitting.

### D1.6 BCNF — every determinant is a superkey

BCNF (sometimes called "3.5NF") closes the one gap 3NF leaves open. 3NF allows `X → A` when A is a *prime* attribute, even if X is not a key. BCNF forbids it. The gap only appears when a table has **multiple overlapping composite candidate keys**.

**Violation:** `CourseAssignment(student_id, subject, professor)`:
- a student takes a subject with exactly one professor: `{student_id, subject} → professor`
- each professor teaches exactly one subject: `professor → subject` (a subject can have many professors)

Candidate keys are `{student_id, subject}` **and** `{student_id, professor}`, so every column is prime. It is in 3NF, because `subject` is prime. It violates BCNF because `professor` determines `subject` and `professor` is not a superkey. The anomaly: a professor's subject is repeated for every student. Change it in one row and the rows disagree.

**Fix:** decompose into

```
student_professor(student_id, professor, PK(student_id, professor))
professor_subject(professor PK, subject)
```

⚠️ **The trade-off the usual explanation leaves out.** This decomposition is lossless (joining the two tables gives the original rows back), but it is **not dependency-preserving**. The rule "one professor per student per subject" (`{student_id, subject} → professor`) now spans two tables, and no single-table key or constraint can enforce it. That is why designers often *stop at 3NF*: 3NF decomposition can always preserve dependencies, BCNF cannot.

### D1.7 One table, all the way from unnormalized to BCNF (worked example)

Start with a spreadsheet-style order sheet:

```
order_id | customer | customer_city | items
101      | Ada      | Pune          | "Pen x2, Book x1"
102      | Ada      | Pune          | "Pen x5"
```

| Step | Problem spotted | Change |
|---|---|---|
| **→ 1NF** | `items` holds a list | one row per item: `order_line(order_id, product, qty, customer, customer_city)`, key `(order_id, product)` |
| **→ 2NF** | `customer` and `customer_city` depend only on `order_id` (part of the key) | split: `orders(order_id PK, customer, customer_city)`, `order_line(order_id, product, qty)` |
| **→ 3NF** | `customer → customer_city` (non-key → non-key) | split: `customer(customer PK, city)`, `orders(order_id PK, customer FK)` |
| **BCNF?** | every determinant (`order_id`, `customer`, `(order_id, product)`) is a key of its table | ✅ already BCNF |

Final schema: `customer`, `orders`, `order_line`. Notice each "split" created a **foreign key on the many side**, which is the next section.

📌 In practice: aim for 3NF/BCNF in your write model, then **denormalize deliberately** (caches, read models, reporting tables) when a measured query needs it. Denormalization is a choice you make knowing the anomaly you accept. An accident is different.

### D1.8 Why the foreign key lives on the "many" side

> **Your question:** *"why is this — 'In a database, a Foreign Key (FK) column can only exist on the "Many" side of a relationship'? is this due to keeping the db in normalized form?"*

**Partly. The root cause is 1NF atomicity: a column holds exactly one value.**

Take "one department has many employees":

- Put `dept_id` on **employee** (the many side): each employee row needs to point at exactly **one** department. One value per cell. ✅
- Put the link on **department** (the one side): a department row would need to point at **many** employees. A cell cannot hold a list, so you have two bad options:
  1. pack the ids into one cell (`emp_ids = "1,2,3"`) — violates **1NF**, cannot be indexed or constrained as a foreign key;
  2. repeat the department row once per employee (`101 | Engineering | 1`, `101 | Engineering | 2`, …) — now the department's own facts (`dept_name`) are duplicated, which is the update anomaly 2NF/3NF exist to remove, and `dept_id` is no longer a key of the department table.

```
❌ department(dept_id, dept_name, emp_id)       ✅ department(dept_id PK, dept_name)
   101 | Engineering | 1                             101 | Engineering
   101 | Engineering | 2     ← name repeated     employee(emp_id PK, emp_name, dept_id FK)
   101 | Engineering | 3                             1 | Alice   | 101
                                                     2 | Bob     | 101
```

📌 **Correction:** so "normalization" is the right family of reasons, but the precise one is *one value per cell*. Put that way, the other cases follow:

| Relationship | Where the link goes | Why |
|---|---|---|
| one-to-many | FK on the **many** side | each many-row points at exactly one parent |
| one-to-one | FK on **either** side, plus a **UNIQUE** constraint | each row points at at most one row in either direction. The UNIQUE constraint is what stops it being one-to-many |
| many-to-many | a **join table** with two FKs | neither side can hold a list, so the pairs become rows |

🔗 JPA mirrors this exactly: the entity mapped to the table holding the FK is the **owning side** (`@ManyToOne` / `@JoinColumn`), and the other side uses `mappedBy`. See [§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-) and the Q&A in [§D3.5](#d35-your-mappedby-questions-answered-one-by-one).

---

## D2. Connecting to a database: JDBC drivers, DataSource and connection pools

> **Your question:** *"what is a database driver and a JDBC driver, and what does it do? does it handle the network-level things like opening the TCP connection and managing the connection pool, or what?"*

**Short answer:** the driver opens and speaks over the **TCP connection**. It does **not** pool connections. Pooling is a separate layer (HikariCP in Spring Boot) that sits *above* the driver.

### D2.1 The layer cake

```
 Your code:   orderRepository.findByStatus("NEW")
      │
      ▼
 ┌─────────────────────────────┐  Spring Data JPA — generates the repository implementation (a proxy)
 │ Spring Data repository      │
 └──────────────┬──────────────┘
                ▼
 ┌─────────────────────────────┐  JPA / Hibernate — entities ↔ rows, JPQL → SQL, dirty checking
 │ EntityManager (Hibernate)   │
 └──────────────┬──────────────┘
                ▼  asks for a java.sql.Connection
 ┌─────────────────────────────┐  javax.sql.DataSource implemented by HikariCP:
 │ DataSource = connection pool│  keeps N connections open, lends them out, takes them back
 └──────────────┬──────────────┘
                ▼  only when the pool needs a NEW physical connection
 ┌─────────────────────────────┐  JDBC driver (e.g. org.postgresql:postgresql, mysql-connector-j):
 │ JDBC driver                 │  TCP socket, TLS, auth handshake, wire protocol, ResultSet parsing
 └──────────────┬──────────────┘
                ▼
           Database server
```

| Layer | Java type(s) | Who provides it | Owns |
|---|---|---|---|
| **JDBC API** | `java.sql.Connection`, `PreparedStatement`, `ResultSet`, `javax.sql.DataSource` | the JDK (interfaces only) | the *contract*, so your code is vendor-neutral |
| **JDBC driver** | an implementation of `java.sql.Driver` | the database vendor (a `.jar`) | network I/O + protocol translation |
| **Connection pool** | a `DataSource` implementation (`HikariDataSource`) | HikariCP (Boot's default) | reusing connections, limits, timeouts, health |
| **ORM** | `EntityManager` | Hibernate | object ↔ row mapping, SQL generation |
| **Repository abstraction** | `JpaRepository<T, ID>` | Spring Data JPA | generated CRUD/query methods |

🐍 Python analogy: `psycopg2` is the driver; `psycopg2.pool` or SQLAlchemy's engine pool is the pool; SQLAlchemy ORM is Hibernate; the DB-API 2.0 (PEP 249) is the JDBC API. 🟨 Node: `pg` is the driver, `pg.Pool` is the pool, Prisma/TypeORM is the ORM.

### D2.2 What the driver actually does

| Task | Handled by the driver? |
|---|---|
| Open a TCP socket to `host:port` | ✅ |
| TLS handshake, authentication (password, SCRAM, IAM token) | ✅ |
| Translate `executeQuery("SELECT …")` into the vendor's binary wire protocol | ✅ |
| Parse the bytes coming back into a `ResultSet` | ✅ |
| Close the socket when `connection.close()` is called on a *raw* connection | ✅ |
| Keep connections open and reuse them | ❌ the pool does this |
| Limit concurrent connections, time out waiting callers | ❌ the pool does this |

📌 Modern drivers are **"Type 4"** (pure Java, speak the database's network protocol directly). The older types (JDBC-ODBC bridge, native-library drivers) are historical.

📌 **How the driver gets found:** since JDBC 4.0 a driver jar registers itself through `META-INF/services/java.sql.Driver` (the `ServiceLoader` mechanism). The old `Class.forName("com.mysql.jdbc.Driver")` line from tutorials is no longer needed. Spring Boot also infers the driver class from the `spring.datasource.url` prefix (`jdbc:postgresql:` → the PostgreSQL driver).

### D2.3 Why you need a pool

`DriverManager.getConnection(url, user, pass)` asks the driver for a **brand-new physical connection** every time: TCP handshake + TLS + authentication, typically several milliseconds, plus a server-side process or thread per connection. Doing that per HTTP request wastes time and can exhaust the database.

A pool opens connections up front and lends them out:

```java
try (Connection c = dataSource.getConnection()) {   // borrow from the pool (microseconds)
    // use it
}                                                   // close() RETURNS it to the pool; the socket stays open
```

📌 That `close()` is the key trick: the pool hands you a *wrapper* whose `close()` means "give it back", not "close the socket".

### D2.4 HikariCP in Spring Boot

Spring Boot picks a pool automatically. Its preference order is **HikariCP**, then Tomcat JDBC pool, then Commons DBCP2, then Oracle UCP (if available on the classpath). `spring-boot-starter-data-jpa` and `spring-boot-starter-jdbc` bring in HikariCP, so in practice you get Hikari.

```yaml
spring:
  datasource:
    url: jdbc:postgresql://db:5432/orders
    username: app
    password: ${DB_PASSWORD}
    hikari:
      maximum-pool-size: 10        # Hikari's default is 10
      minimum-idle: 10             # defaults to maximum-pool-size
      connection-timeout: 30000    # ms a caller waits for a free connection before failing (default 30s)
      max-lifetime: 1800000        # retire connections before the DB/network kills them (default 30 min)
```

⚠️ **Pool size is not "bigger is better".** Every connection is a session on the database. 50 pods × 20 connections = 1,000 sessions. Size the pool to what the database can serve, not to your thread count. When all connections are borrowed, callers block for `connection-timeout` and then fail with `SQLTransientConnectionException: … Connection is not available, request timed out`. The usual cause is holding a connection during slow work. See network calls inside `@Transactional` in [§D4.1](#d41-transactions-).

🔗 Who uses those threads: Tomcat's ~200 request threads ([§W1](03-spring-web.md#w1-servlets-and-the-servlet-container-q42-q43-q44)) share these ~10 connections. That ratio is fine only because each request holds a connection briefly.

### D2.5 Where Spring Data repositories fit, and is `@Repository` needed?

> **Your question:** *"will this repository also work even if we don't mark it with `@Repository`? is the `@Repository` annotation optional or mandatory to make a class a repository class?"*

**For a Spring Data interface (`extends JpaRepository<User, Long>`): optional.** Spring Data finds every interface extending `Repository` under the scanned packages (Boot enables `@EnableJpaRepositories` for you, starting from the `@SpringBootApplication` package). It builds a proxy implementation at runtime and registers it as a bean. `@Repository` on the interface changes nothing.

**Exception translation still happens.** Spring Data adds a persistence-exception-translation interceptor to its repository proxies, so a vendor exception such as Hibernate's `ConstraintViolationException` surfaces as Spring's `DataAccessException` hierarchy (for example `DataIntegrityViolationException`) either way.

**For a class you write yourself** (a hand-written DAO using `EntityManager` or `JdbcTemplate`): use `@Repository`. It makes the class a bean (it is a `@Component`), and it marks it for `PersistenceExceptionTranslationPostProcessor`, which Boot auto-configures. Raw provider exceptions thrown from it are then translated into `DataAccessException`.

| | Spring Data interface | Your own DAO class |
|---|---|---|
| Becomes a bean without `@Repository`? | ✅ (repository scanning) | ❌ (needs `@Repository`/`@Component`) |
| Exception translation without `@Repository`? | ✅ (built into the proxy) | ❌ (`@Repository` is the trigger) |

🔗 The stereotype annotations side by side: [§C2](02-spring-core.md#c2-inversion-of-control-and-dependency-injection-q13).

### D2.6 Connecting to more than one database [+]

**The question:** can you just put two sets of credentials in `application.properties` and have Spring Boot wire both, the way it wires one?

**No.** Boot's auto-configuration binds exactly one prefix — `spring.datasource.*` — and builds exactly one `DataSource`, one `EntityManagerFactory` and one `TransactionManager`. It has no way to know which entities and repositories belong to which database. The moment you need two, you write the configuration yourself.

#### The official recipe

Spring Boot's own how-to guide gives this shape. Two details do the real work:

```java
@Configuration(proxyBeanMethods = false)
public class SecondDataSourceConfiguration {

    @Qualifier("second")
    @Bean(defaultCandidate = false)                       // ← keeps auto-config for the FIRST one alive
    @ConfigurationProperties("app.datasource")
    public DataSourceProperties secondDataSourceProperties() {
        return new DataSourceProperties();
    }

    @Qualifier("second")
    @Bean(defaultCandidate = false)
    @ConfigurationProperties("app.datasource.configuration")
    public HikariDataSource secondDataSource(
            @Qualifier("second") DataSourceProperties props) {
        return props.initializeDataSourceBuilder().type(HikariDataSource.class).build();
    }
}
```

```yaml
spring:
  datasource:                 # the primary — still fully auto-configured
    url: "jdbc:mysql://localhost/first"
    username: "dbuser"
    password: "dbpass"
    configuration:
      maximum-pool-size: 30
app:
  datasource:                 # the second — bound by the class above
    url: "jdbc:mysql://localhost/second"
    username: "dbuser"
    password: "dbpass"
```

⚠️ **The `jdbc-url` trap.** If you bind `@ConfigurationProperties` straight onto a `DataSourceBuilder` instead of going through `DataSourceProperties`, the `url` key silently fails and you get:

```
java.lang.IllegalArgumentException: dataSource or dataSourceClassName or jdbcUrl is required
```

The docs state the cause plainly: *"Unfortunately, this basic setup does not work because Hikari has no `url` property. Instead, it has a `jdbc-url` property."* Two fixes — rename the key to `jdbc-url`, or (better) use `DataSourceProperties.initializeDataSourceBuilder()`, which *"takes care of the `url` to `jdbc-url` translation"* and keeps your YAML portable across pool implementations.

📌 `@Bean(defaultCandidate = false)` is the modern mechanism (Spring Boot 3.4+): it registers the bean so `@Qualifier` can find it, while hiding it from unqualified injection — *"This prevents the auto-configured `DataSource` from backing off."* On older versions you instead mark the primary set with `@Primary` ([§C2.11](02-spring-core.md#c211-resolving-ambiguity)) and qualify the rest.

#### Adding JPA on top

A second `DataSource` is not yet a second persistence unit. For JPA you must also split the `EntityManagerFactory`, the `TransactionManager`, and — critically — the **package** each one scans:

```java
@Configuration
@EnableTransactionManagement
@EnableJpaRepositories(
    basePackages          = "com.example.repository.secondary",   // repositories for DB 2
    entityManagerFactoryRef = "secondaryEntityManagerFactory",
    transactionManagerRef   = "secondaryTransactionManager")
public class SecondaryJpaConfig {

    @Bean
    public LocalContainerEntityManagerFactoryBean secondaryEntityManagerFactory(
            EntityManagerFactoryBuilder builder,
            @Qualifier("second") DataSource dataSource) {
        return builder.dataSource(dataSource)
                      .packages("com.example.entity.secondary")    // entities for DB 2
                      .persistenceUnit("secondary")
                      .build();
    }

    @Bean
    public PlatformTransactionManager secondaryTransactionManager(
            @Qualifier("secondaryEntityManagerFactory") EntityManagerFactory emf) {
        return new JpaTransactionManager(emf);
    }
}
```

⚠️ **Entities and repositories must be in disjoint packages**, one tree per database. There is no annotation that says "this entity belongs to DB 2" — the package is the only signal, and an entity in the wrong tree fails at startup or, worse, resolves against the wrong database.

⚠️ **`@Transactional` now needs a name:** `@Transactional("secondaryTransactionManager")`. The unqualified form silently uses the primary manager, so writes to DB 2 end up outside any transaction. This is the most common bug in two-database services.

📌 **A transaction still does not span both databases.** Two `DataSource`s means two independent transactions; a failure after committing the first leaves you inconsistent. Real distributed transactions need XA/JTA, which is heavyweight and rarely worth it — the usual answer is to design so that one logical operation only writes to one database, and reconcile asynchronously otherwise.

↔ [§C2.11](02-spring-core.md#c211-resolving-ambiguity) for `@Primary` and `@Qualifier`; [§D3](#d3-jpa-and-hibernate-entity-relationships-) for what you then do with those entities.

### D2.7 Cheat sheet

| Question | Answer |
|---|---|
| Who opens the TCP connection? | the JDBC driver |
| Who pools connections? | HikariCP (a `DataSource`), not the driver |
| Do I write `Class.forName(...)`? | no (JDBC 4 service loading; Boot infers the driver from the URL) |
| What does `connection.close()` do with a pool? | returns the connection; the socket stays open |
| What does Hibernate need? | a `DataSource`. It never talks to the driver directly |
| `javax.sql` vs `jakarta`? | `java.sql`/`javax.sql` are JDK packages and did **not** move to `jakarta`. Only `javax.persistence` → `jakarta.persistence` changed (Boot 3+) |

---

## D3. JPA and Hibernate entity relationships [+]

This section exists because [§D5](#d5-spring-data-rest-q22q26-q29q31) and [§D6](#d6-hateoas-hal-and-querydsl-q27-q28) sit on top of it. Spring Data REST auto-exposes *entities*; entities are only interesting once they have *relationships*. Everything here is plain JPA/Hibernate — it applies whether or not you ever touch Spring Data REST.

**Versions this was verified against:** Jakarta Persistence 3.1 (the `jakarta.persistence.*` package used by Spring Boot 3+; Spring Boot 2.x used `javax.persistence.*`), Hibernate ORM 6.x as the default provider.

**The one sentence to carry:** a database relationship is *one* foreign key column living in *one* table; a Java relationship can be navigated from both ends. Almost every rule in this section exists to reconcile those two facts.

---

### D3.1 The core mismatch, stated precisely [+]

Take "a company has many employees."

**In the database** there is exactly one artefact expressing this:

```sql
CREATE TABLE companies (
    id   BIGINT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255)
);
CREATE TABLE employees (
    id         BIGINT AUTO_INCREMENT PRIMARY KEY,
    name       VARCHAR(255),
    company_id BIGINT,                              -- ← the entire relationship is this column
    FOREIGN KEY (company_id) REFERENCES companies(id)
);
```

Note what is **not** there: the `companies` table has no column referring to employees. The relationship is *unidirectional in storage*. To answer "who works at company 5?" the database scans `employees` for `company_id = 5`.

**In Java** you want both directions:

```java
employee.getCompany();    // easy — follow the FK
company.getEmployees();   // there is no column for this
```

JPA lets you have both. The cost is that you must tell it which Java field corresponds to the real column. That is the entire job of `mappedBy`.

📌 **Consequences that follow from this one fact**, each covered below:
- One side *owns* the relationship (holds the FK); the other is a mirror ([§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-)).
- Only changes to the owning side produce SQL ([§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-)).
- You must keep both Java fields in sync yourself ([§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-)).
- Navigating from the non-FK side may cost an extra query ([§D3.12](#d312-fetchtype-proxies-and-lazy-loading-)).

---

### D3.2 Primary keys: `@Id` and `@GeneratedValue` strategies

> **Your question:** *"`@GeneratedValue(strategy = GenerationType.IDENTITY)` — what are the other types of GenerationType, why did we use IDENTITY here, and when should we use which?"*

`@Id` marks the primary-key field. `@GeneratedValue` says "the database or the provider assigns it; don't set it yourself". The `strategy` says **how**. `jakarta.persistence.GenerationType` has five constants:

| Strategy | How the id is produced | When the id is known | Typical databases | Use when |
|---|---|---|---|---|
| `IDENTITY` | the database's auto-increment column (`AUTO_INCREMENT`, `SERIAL`/`IDENTITY`) | only **after** the `INSERT` runs | MySQL, PostgreSQL, SQL Server | the default choice on MySQL; simple and matches existing schemas |
| `SEQUENCE` | a database **sequence** object (`nextval`) | **before** the insert; Hibernate can pre-allocate ids in blocks (`allocationSize`, default 50) | PostgreSQL, Oracle, SQL Server 2012+, H2 | high-volume inserts on a database with sequences |
| `TABLE` | a separate table simulating a sequence, row-locked to hand out values | before the insert | any | ⚠️ avoid: lock contention. Only for databases with neither sequences nor identity columns |
| `AUTO` (the default if you write just `@GeneratedValue`) | the provider picks | depends | any | prototypes; in production, say what you mean |
| `UUID` (**new in Jakarta Persistence 3.1**, i.e. Boot 3+/Hibernate 6) | a `java.util.UUID` generated by the provider | before the insert | any | ids must be unguessable or generated across services |

**Why `IDENTITY` costs you batching.** Hibernate must put a newly persisted entity in its persistence context *keyed by its id*. With `IDENTITY` the id exists only after the row is inserted, so Hibernate executes the `INSERT` **immediately at `persist()`** instead of queueing it until flush. The Hibernate user guide states the consequence: *"Hibernate will not be able to batch INSERT statements for the entities using the IDENTITY generation."* With `SEQUENCE` the id is fetched first (and usually from a pre-allocated block), so 1,000 inserts can be sent as a few JDBC batches.

**What `AUTO` means in Hibernate 6.** For numeric ids, Hibernate uses its `SequenceStyleGenerator`, which uses a real **sequence** if the database supports one and otherwise falls back to a table. For a `UUID`-typed id it uses a UUID generator. ⚠️ On MySQL (no sequences) `AUTO` therefore means the *table* strategy (a `hibernate_sequence` table), which surprises people who expected auto-increment. That's one more reason to name the strategy.

```java
@Id
@GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "order_seq")
@SequenceGenerator(name = "order_seq", sequenceName = "order_seq", allocationSize = 50)
private Long id;

@Id
@GeneratedValue(strategy = GenerationType.UUID)   // Jakarta Persistence 3.1+ (Boot 3+)
private UUID id;
```

📌 **Why the tutorial used `IDENTITY`.** It is the simplest option on MySQL/PostgreSQL and needs no extra database object. For a users table with modest insert rates it is perfectly fine.

⚠️ **Boot 2.7 (Hibernate 5.6, `javax.persistence`)** has no `GenerationType.UUID`. Use `@GeneratedValue(generator = "uuid2")` with `@GenericGenerator(name = "uuid2", strategy = "uuid2")`, or assign `UUID.randomUUID()` in the constructor.

🔗 The `id` being null before persist is also why entity `equals`/`hashCode` need care: [§D3.16](#d316-equals-and-hashcode-for-entities-).

---

### D3.3 The four relationship types at a glance [+]

| Annotation | Meaning | Where the FK lives | Default `fetch` | Can take `mappedBy`? | Can take `orphanRemoval`? |
|---|---|---|---|---|---|
| `@OneToOne` | one ↔ one | in the owning entity's table | **`EAGER`** | ✅ (inverse side) | ✅ |
| `@ManyToOne` | many → one | **always** in this entity's table | **`EAGER`** | ❌ never | ❌ |
| `@OneToMany` | one → many | in the *other* table | **`LAZY`** | ✅ (inverse side) | ✅ |
| `@ManyToMany` | many ↔ many | in a separate **join table** | **`LAZY`** | ✅ (inverse side) | ❌ |

**Source for the defaults** — the Jakarta Persistence 3.1 javadoc declares them literally:

| Element | `@OneToMany` | `@ManyToOne` | `@OneToOne` | `@ManyToMany` |
|---|---|---|---|---|
| `targetEntity` | `void.class` | `void.class` | `void.class` | `void.class` |
| `cascade` | `{}` | `{}` | `{}` | `{}` |
| `fetch` | `LAZY` | `EAGER` | `EAGER` | `LAZY` |
| `optional` | — | `true` | `true` | — |
| `mappedBy` | `""` | — | `""` | `""` |
| `orphanRemoval` | `false` | — | `false` | — |

⚠️ **Memorise the asymmetry: the `*ToOne` annotations default to `EAGER`, the `*ToMany` ones to `LAZY`.** This is the single most consequential default in JPA and it is almost always the wrong one for `*ToOne` — see [§D3.12](#d312-fetchtype-proxies-and-lazy-loading-) and [§D3.13](#d313-the-n1-problem-and-every-way-to-fix-it-).

📌 **`cascade` defaults to `{}` — nothing is cascaded unless you ask.** The javadoc is explicit: *"By default no operations are cascaded."*

---

### D3.4 Owning side vs inverse side — and what `mappedBy` actually does [+]

**Definition, from the Jakarta Persistence spec:** *"The inverse side of a bidirectional relationship must refer to its owning side by use of the `mappedBy` element of the `OneToOne`, `OneToMany`, or `ManyToMany` annotation."* The owning side is the one that "determines the updates to the relationship in the database."

**Owning side** = the entity whose table holds the foreign key. Uses `@JoinColumn`. Never has `mappedBy`.
**Inverse side** = the mirror. Has `mappedBy`. Contributes *no* column to its own table.

```java
// ── OWNING SIDE ── the employees table has the company_id column
@Entity
@Table(name = "employees")
public class Employee {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @ManyToOne(fetch = FetchType.LAZY)          // override the EAGER default
    @JoinColumn(name = "company_id")            // ← the real database column
    private Company company;
}

// ── INVERSE SIDE ── the companies table gains nothing
@Entity
@Table(name = "companies")
public class Company {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @OneToMany(mappedBy = "company")            // ← "company" is the FIELD NAME in Employee
    private List<Employee> employees = new ArrayList<>();
}
```

#### What `mappedBy` is matching on

`mappedBy = "company"` is a **Java field name on the owning entity**, resolved by reflection. It is *not* a table name, *not* a column name, and *not* an SQL identifier.

Hibernate resolves it in three steps:
1. Read the generic type of the collection — `List<Employee>` → the other end is `Employee`.
2. Look inside `Employee` for a field (or property) literally named `company`.
3. Read the `@JoinColumn` on that field to learn the real column: `company_id`.

⚠️ Because it is a reflective string lookup, **renaming the field in `Employee` without updating the `mappedBy` string breaks the mapping at startup, not at compile time.** Your IDE will usually catch it; the compiler will not.

#### The rule that actually bites: only the owning side writes

Because the FK lives in `employees`, Hibernate can only change the relationship by issuing SQL against `employees`. Therefore:

```java
company.getEmployees().add(employee);   // ❌ no SQL. The collection is mappedBy — Hibernate ignores it for writes.
employee.setCompany(company);           // ✅ UPDATE employees SET company_id = ? WHERE id = ?
```

📌 This is not a quirk, it is arithmetic: there is no column in `companies` that *could* be updated. `mappedBy` is Hibernate telling you "I have no write path from this side."

**Therefore: always write synchronization helpers.** Vlad Mihalcea's guidance is blunt — *"You should always provide these methods whenever you are working with a bidirectional association as, otherwise, you risk very subtle state propagation issues."*

```java
// on Company
public void addEmployee(Employee e) {
    employees.add(e);        // keeps the Java object graph correct (for this transaction, and for JSON)
    e.setCompany(this);      // ← the line that actually causes SQL
}

public void removeEmployee(Employee e) {
    employees.remove(e);
    e.setCompany(null);
}
```

⚠️ **Why the first line still matters even though it writes nothing.** Within the same persistence context, Hibernate returns the *same* Java object you already hold. If you set only the owning side, `company.getEmployees()` keeps returning the stale list for the rest of the transaction — your code sees data that disagrees with the database it is about to write. Set both, always.

#### 🏢 This exact pattern in real production code

A typical production entity is a textbook bidirectional `@OneToMany`, helper method included (names changed):

```java
@OneToMany(mappedBy = "playlist", fetch = FetchType.EAGER, cascade = CascadeType.ALL)
@JsonBackReference
public List<Track> getTracks() { return tracks; }

public void addTrack(Track track) {
    track.setPlaylist(this);                     // ← the owning side, written first
    if (getTracks() == null) { tracks = new ArrayList<Track>(); }
    // …
}
```

and the owning side, in `Track`:

```java
@ManyToOne
@JoinColumn(name = "PLAYLIST_ID")
public Playlist getPlaylist() { return playlist; }
```

Three real details worth noticing in that code:

1. **The annotations are on getters, not fields.** JPA decides *access type* from where you put `@Id`. `@Id` on a field → field access for the whole entity; `@Id` on a getter → property access. You must be consistent within an entity hierarchy; mixing silently ignores one set of annotations.
2. **`@JsonBackReference`** breaks the infinite JSON recursion you get when serializing a bidirectional pair — see [§D3.19](#d319-serializing-bidirectional-entities-to-json-).
3. **`fetch = FetchType.EAGER`** on a collection is the pattern [§D3.12](#d312-fetchtype-proxies-and-lazy-loading-) warns about. In a large production codebase I checked, the ratio was **101 `FetchType.LAZY` to 17 `FetchType.EAGER`**, so real code overwhelmingly agrees with the guidance — this is one of the exceptions.

---

### D3.5 Your `mappedBy` questions, answered one by one

You asked four connected questions. [§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-) above has the mechanics; this subsection answers each question directly, keeping your wording, and links to the depth.

> **Your question:** *"what is mappedBy and orphanRemoval?"*

- **`mappedBy`** goes on the **inverse** side of a *bidirectional* relationship. It names the **Java field** on the other entity that owns the foreign key: "the mapping is over there, don't create anything for this field". The owning side is the entity whose table holds the FK column (`@JoinColumn`).
- **`orphanRemoval = true`** goes on a `@OneToMany` or `@OneToOne` parent. It means: when a child is disconnected from this parent (removed from the collection, or the reference set to `null`), **delete the child row**. Full comparison with `CascadeType.REMOVE` in [§D3.11](#d311-orphanremoval-vs-cascadetyperemove-).

The `Order`/`Item` example, corrected to include the helper methods that make the bidirectional pair consistent:

```java
@Entity
@Table(name = "orders")            // ⚠️ ORDER is a reserved SQL word; name the table explicitly
public class Order {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    // Inverse side: "order" is the FIELD NAME inside Item
    @OneToMany(mappedBy = "order", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Item> items = new ArrayList<>();

    public void addItem(Item i)    { items.add(i);    i.setOrder(this); }
    public void removeItem(Item i) { items.remove(i); i.setOrder(null); }
}

@Entity
public class Item {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    // Owning side: this entity's table has the order_id column
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "order_id")
    private Order order;
}
```

```java
@Transactional
public void dropFirstItem(Long orderId) {
    Order order = orderRepository.findById(orderId).orElseThrow();
    order.removeItem(order.getItems().get(0));
    // at commit, because of orphanRemoval: DELETE FROM item WHERE id = ?
}
```

📌 **Correction to the answer you were given:** it said "by default (without orphanRemoval) Hibernate will set the FK to NULL but keep the row". For a **bidirectional `mappedBy`** collection like this one, removing from the list without `orphanRemoval` produces **no SQL at all**: the inverse collection has no write path. The FK becomes NULL only if you also null the owning field (`item.setOrder(null)`, which `removeItem` does), or in the unidirectional `@OneToMany` + `@JoinColumn` mapping. The full table is in [§D3.11](#d311-orphanremoval-vs-cascadetyperemove-).

📌 **Also:** without `mappedBy`, a `@OneToMany` alone gives you a **join table** (`order_items`), as the answer said. But a bidirectional `@OneToOne` without `mappedBy` gives you **two foreign-key columns**, one in each table, describing two unrelated relationships. It does not create a join table. Either way, the fix is to declare `mappedBy` on the side without the FK.

> **Your question:** *"doesn't mappedBy get used on ManyToMany / ManyToOne?"*

| Annotation | `mappedBy`? | Why |
|---|---|---|
| `@ManyToOne` | ❌ the attribute **does not exist** on this annotation | the many side always holds the FK, so it is always the owner and uses `@JoinColumn` |
| `@OneToMany` | ✅ on the parent, pointing at the child's `@ManyToOne` field | the parent's table has no column for a list |
| `@ManyToMany` | ✅ on the inverse side, pointing at the owner's `@ManyToMany` field | the owner configures the `@JoinTable`; the inverse reuses it ([§D3.9](#d39-manytomany-and-jointable-)) |
| `@OneToOne` | ✅ on the side whose table has **no** FK | either table *could* hold the FK; you pick one with `@JoinColumn`, the other gets `mappedBy` |

> **Your question:** *"if the foreign key is only placed on the Many side, then why and how is it used in one-to-one mapping? And since in ManyToOne the many side is the default owning side, we don't need to figure out where to put mappedBy — isn't that similar to OneToMany, where the second part also sounds like the owning table? so why should we use mappedBy in OneToMany or OneToOne mapping?"*

1. **One-to-one:** the "FK only on the many side" rule is about one-to-many. In one-to-one, *either* table may hold the FK. A **UNIQUE** constraint on that column is what makes it one-to-one instead of many-to-one ([§D1.8](#d18-why-the-foreign-key-lives-on-the-many-side), [§D3.7](#d37-onetoone--and-the-lazy-trap-that-catches-everyone-)). Because the database doesn't force a side, *you* must: `@JoinColumn` on the side whose table has the column, `mappedBy` on the other.
2. **Why `mappedBy` is needed at all:** the database stores *one* link; Java has *two* fields (`user.getPassport()` and `passport.getUser()`). Without `mappedBy`, Hibernate cannot know the two fields describe the same link, so it maps each one independently. That gives a join table for `@OneToMany`, and a second FK column for `@OneToOne`.

> **Your question:** *"i'm confused: in ManyToOne we don't use mappedBy but in OneToMany we do. why? isn't ManyToOne similar to OneToMany, just with the first and second entity interchanged? are you assuming that the second one (in ManyToOne the 'One' part, in OneToMany the 'Many' part) is the entity where we put mappedBy?"*

Yes: they are the **same relationship seen from its two ends**. The difference is which **class file** you are annotating:

```
 Employee.java (table HAS dept_id)            Department.java (table has NO employee column)
 @ManyToOne                                    @OneToMany(mappedBy = "department")
 @JoinColumn(name = "dept_id")                 private List<Employee> employees;
 private Department department;                       │
        ▲                                             │ "go read the field named 'department'
        └─────────────────────────────────────────────┘  in Employee for the real mapping"
```

📌 **Correction to the "second entity" idea:** `mappedBy` does not go on "the second word of the annotation". It goes on the **entity whose table lacks the FK**. In a one-to-many pair that is always the "one" side, which carries `@OneToMany`. So the rule is fixed:

| Class | Annotation | Has |
|---|---|---|
| the "many" side (FK in its table) | `@ManyToOne` | `@JoinColumn` — never `mappedBy` |
| the "one" side | `@OneToMany` | `mappedBy = "<field in the many-side class>"` |

If you make the relationship **unidirectional** (only `Employee.department` exists), there is no `@OneToMany` field and therefore no `mappedBy` anywhere. That is a perfectly good design ([§D3.8](#d38-manytoone-and-onetomany--the-pairing-you-will-actually-use-)).

---

### D3.6 `@JoinColumn` — every attribute, and the default-name rule [+]

`@JoinColumn` declares the **foreign key column** in the owning entity's table.

| Attribute | Default | What it does |
|---|---|---|
| `name` | `""` → derived, see below | the FK column name in *this* entity's table |
| `referencedColumnName` | `""` → the target's PK | which column in the *target* table the FK points at |
| `nullable` | `true` | emits `NOT NULL` in generated DDL when `false` |
| `unique` | `false` | emits a unique constraint — this is what turns a `@ManyToOne` shape into a one-to-one |
| `insertable` | `true` | include the column in generated `INSERT`s |
| `updatable` | `true` | include the column in generated `UPDATE`s |
| `table` | `""` | for entities mapped across secondary tables |
| `foreignKey` | `@ForeignKey(PROVIDER_DEFAULT)` | control or suppress the generated FK constraint |
| `columnDefinition` | `""` | raw SQL fragment for the column in generated DDL |

#### The default name is not what most tutorials say

The Jakarta Persistence spec states the default is *"the concatenation of the following: the name of the referencing relationship property or field of the referencing entity or embeddable class; `"_"`; the name of the referenced primary key column."*

So for `private UserProfile userProfile;` pointing at a target whose PK column is `id`, the JPA-implicit name is **`userProfile_id`** — derived from the *field name*, not the target class name.

Then Spring Boot applies its own physical naming strategy on top: it configures Hibernate's `CamelCaseToUnderscoresNamingStrategy` by default, which lowercases and inserts underscores at camel-case boundaries. Net result in a normal Spring Boot app: **`user_profile_id`**.

📌 Two lessons: (a) the derivation is from the *field* name, so renaming a field silently renames a column under `ddl-auto=update`; (b) always set `name` explicitly on anything you intend to keep.

#### `nullable = false` vs `optional = false`

These look interchangeable and are not:

| | `@JoinColumn(nullable = false)` | `@ManyToOne(optional = false)` |
|---|---|---|
| Layer | **database schema** | **JPA runtime** |
| Effect | `NOT NULL` in generated DDL | provider may validate before flushing, and may enable better fetch plans |
| If violated | database throws on flush | provider may throw earlier |
| Works with `ddl-auto=none` | ❌ nothing generated — the constraint only exists if your migration created it | ✅ still enforced by the provider |

Set **both** when the association is genuinely mandatory. `optional = false` additionally tells Hibernate the target always exists, which lets it use an inner join instead of an outer join.

---

### D3.7 `@OneToOne` — and the lazy trap that catches everyone [+]

#### Unidirectional (prefer this)

```java
@Entity @Table(name = "users")
public class User {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String username;

    @OneToOne(fetch = FetchType.LAZY, cascade = CascadeType.ALL, orphanRemoval = true)
    @JoinColumn(name = "profile_id", referencedColumnName = "id", unique = true)
    private UserProfile profile;
}
```

```sql
CREATE TABLE users (
    id         BIGINT AUTO_INCREMENT PRIMARY KEY,
    username   VARCHAR(255),
    profile_id BIGINT UNIQUE,
    FOREIGN KEY (profile_id) REFERENCES user_profiles(id)
);
```

📌 The `unique = true` is what makes it *one*-to-one rather than many-to-one. Without it the schema permits two users pointing at one profile.

#### Bidirectional — and why the inverse side cannot be lazy

```java
@Entity @Table(name = "user_profiles")
public class UserProfile {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String bio;

    @OneToOne(mappedBy = "profile", fetch = FetchType.LAZY)   // ⚠️ the LAZY here is ignored
    private User user;
}
```

⚠️ **The `fetch = FetchType.LAZY` on the `mappedBy` side of a `@OneToOne` does not work.** Loading a `UserProfile` always triggers a second `SELECT` against `users`, whatever you write.

**Why**, precisely: a proxy must carry the target's identifier, and `user_profiles` has no column containing the `users` id. The only way to discover whether a `User` exists for this profile — and what its id is — is to query. As Vlad Mihalcea puts it: *"the child identifier must be known when loading the parent entity, and the only way to find the associated `post_details` primary key is to execute a secondary query."* Hibernate cannot even decide between `null` and a proxy without asking the database.

**Three real fixes:**

| Fix | How | Trade-off |
|---|---|---|
| **Make it unidirectional** | delete the `mappedBy` field; query `userRepository.findByProfileId(id)` when you need the reverse | simplest and fastest; you lose `profile.getUser()` |
| **`@MapsId` (shared primary key)** | the child's PK *is* the FK, so both rows share an id | best performance; a schema decision you must make up front |
| **Bytecode enhancement** | enable Hibernate's build-time enhancement plugin | works, but adds a build step and surprises the next reader |

```java
// @MapsId — the profile's id IS the user's id. No extra column, no extra query.
@Entity
public class UserProfile {
    @Id private Long id;                  // same value as the User's id

    @OneToOne(fetch = FetchType.LAZY)
    @MapsId                               // "my PK is this association's FK"
    @JoinColumn(name = "id")
    private User user;
}
```

📌 Real code agrees with the "rare" verdict. In a large production codebase I checked, `@OneToOne` appears in **10** files, against **70** for `@ManyToOne` and **49** for `@OneToMany`. When you think you need `@OneToOne`, check whether the two tables should just be one table.

---
### D3.8 `@ManyToOne` and `@OneToMany` — the pairing you will actually use [+]

`@ManyToOne` is the **only** relationship annotation that is always on the owning side, always holds the FK, and never takes `mappedBy`. If you learn one mapping, learn this one: in the codebase above it is the most common (**70** files).

#### Bidirectional (recommended)

Exactly the `Company`/`Employee` pair from [§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-). The SQL is optimal:

```sql
-- persist a new employee attached to company 1
insert into employees (company_id, name, id) values (1, 'Ada', 2)
-- remove one
delete from employees where id = 2
```

#### Unidirectional `@OneToMany` — two variants, both worse

**Variant A — `@OneToMany` alone.** ⚠️ **This silently creates a join table.**

```java
@OneToMany(cascade = CascadeType.ALL, orphanRemoval = true)
private List<Review> reviews = new ArrayList<>();
```

Hibernate generates a third table `course_review(course_id, reviews_id)` and, for one parent with three children, issues **1 + 3 + 3 = 7** statements. Vlad Mihalcea's assessment: *"For a DBA, this looks more like a many-to-many database association than a one-to-many relationship, and it's not very efficient either."*

**Variant B — `@OneToMany` + `@JoinColumn`.** Removes the join table, but not the inefficiency.

```java
@OneToMany(cascade = CascadeType.ALL, orphanRemoval = true)
@JoinColumn(name = "course_id")     // puts the FK in the reviews table
private List<Review> reviews = new ArrayList<>();
```

The FK column now lives in `reviews` as you wanted, but Hibernate inserts the child **without** the FK and then updates it:

```sql
insert into review (id, text) values (2, 'Great')
update review set course_id = 1 where id = 2        -- ← extra statement per child
```

and removal is worse — two statements where one would do:

```sql
update review set course_id = null where course_id = 1 and id = 2
delete from review where id = 2
```

📌 **Verdict:** a unidirectional `@OneToMany` is legal, commonly taught, and the pattern you should reach for *last*. Prefer the bidirectional pair; if you genuinely do not want a back-reference field, prefer a plain `@ManyToOne` on the child and query the children when you need them.

#### Answering the two worked cases

**"A course has many reviews; deleting the course must delete the reviews."** Lifecycle is strictly owned → use `orphanRemoval = true` and `CascadeType.ALL`, and make it bidirectional:

```java
@Entity
public class Course {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @OneToMany(mappedBy = "course", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Review> reviews = new ArrayList<>();

    public void addReview(Review r) { reviews.add(r); r.setCourse(this); }
    public void removeReview(Review r) { reviews.remove(r); r.setCourse(null); }
}

@Entity
public class Review {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String text;

    @ManyToOne(fetch = FetchType.LAZY, optional = false)
    @JoinColumn(name = "course_id", nullable = false)
    private Course course;
}
```

**"A course has many instructors; both exist independently."** ⚠️ This is **not** one-to-many. An instructor who can teach two courses is a *many-to-many* — see [§D3.9](#d39-manytomany-and-jointable-). If an instructor really can only ever teach one course, it is one-to-many with **no** cascade and **no** `orphanRemoval`:

```java
@OneToMany(mappedBy = "course")      // no cascade, no orphanRemoval
private List<Instructor> instructors = new ArrayList<>();
```

Deleting the course then fails on the FK constraint unless you first null out the children — which is correct behaviour: you are being told that deleting a course would orphan real people.

⚠️ **Never put `cascade = CascadeType.REMOVE` (or `ALL`) on a `@ManyToOne`.** `employee.setCompany(c)` with `CascadeType.ALL` means deleting one employee deletes the company — and then every other employee, if they cascade too. Cascade flows parent → child. `@ManyToOne` points child → parent.

---

### D3.9 `@ManyToMany` and `@JoinTable` [+]

#### Do you always need a join table? Yes.

A relational table cell holds one value. There is no way to store "student 1 is in courses 3, 7 and 9" in a column without violating first normal form. The link must be its own table, one row per pair.

#### The annotation

```java
@Entity @Table(name = "students")
public class Student {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToMany(cascade = {CascadeType.PERSIST, CascadeType.MERGE})   // ⚠️ never ALL — see below
    @JoinTable(
        name = "student_course",                                  // the bridge table
        joinColumns        = @JoinColumn(name = "student_id"),    // FK → THIS entity
        inverseJoinColumns = @JoinColumn(name = "course_id")      // FK → the OTHER entity
    )
    private Set<Course> courses = new HashSet<>();                // ⚠️ Set, not List — see below
}

@Entity @Table(name = "courses")
public class Course {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToMany(mappedBy = "courses")
    private Set<Student> students = new HashSet<>();
}
```

#### Why `inverseJoinColumns` exists here and nowhere else

In `@ManyToOne` there is **one** FK column to name, so one `@JoinColumn` suffices. A join table has **two** FK columns and they are not interchangeable, so the annotation needs two slots:

- `joinColumns` → the column pointing back at the entity **you are writing the annotation in**.
- `inverseJoinColumns` → the column pointing at the entity **on the other end**.

"Inverse" here means "the far end of this association", not "the inverse side of the bidirectional pair". Getting them backwards compiles fine and produces a table whose rows mean the opposite of what you intended.

#### How `mappedBy` resolves on the inverse side

For `@ManyToMany(mappedBy = "courses") private Set<Student> students;` inside `Course`:

1. Generic type `Set<Student>` → the other entity is `Student`.
2. Find the field named `courses` in `Student`.
3. Read its `@JoinTable` → table `student_course`, and note that **`joinColumns` and `inverseJoinColumns` swap roles** when traversed from this direction.

So the inverse side contributes nothing to the schema; it reuses the owner's `@JoinTable` definition, read backwards.

⚠️ If you put `@JoinTable` on *both* sides instead of `mappedBy` on one, you get **two independent join tables** and two half-correct relationships.

#### Two rules that are not optional

**1. Use `Set`, never `List`.** With a `List`, removing one element makes Hibernate delete every join row for that parent and re-insert the survivors:

```sql
DELETE FROM post_tag WHERE post_id = 1          -- all of them
INSERT INTO post_tag (post_id, tag_id) VALUES (1, 3)   -- put back the ones that stay
```

With a `Set` it is one precise statement:

```sql
DELETE FROM post_tag WHERE post_id = 1 AND tag_id = 3
```

The guidance is explicit: *"when using the `@ManyToMany` annotation, always use a `java.util.Set` and avoid the `java.util.List`."* (This also requires sane `equals`/`hashCode` — [§D3.16](#d316-equals-and-hashcode-for-entities-).)

**2. Never cascade `REMOVE` or `ALL`.** *"The `REMOVE` entity state transition doesn't make any sense for a `@ManyToMany` JPA association since it could trigger a chain deletion that would ultimately wipe both sides of the association."* Deleting one student would delete their courses, and those courses would delete their other students. Use `PERSIST` and `MERGE` only.

#### When the join table needs its own columns

The moment you want `enrolled_at`, `grade`, or `status` on the enrolment, `@ManyToMany` is the wrong tool. Promote the join table to an entity and use two `@ManyToOne`s:

```java
@Entity @Table(name = "enrolments")
public class Enrolment {
    @EmbeddedId private EnrolmentId id;

    @ManyToOne(fetch = FetchType.LAZY) @MapsId("studentId")
    @JoinColumn(name = "student_id")
    private Student student;

    @ManyToOne(fetch = FetchType.LAZY) @MapsId("courseId")
    @JoinColumn(name = "course_id")
    private Course course;

    private Instant enrolledAt;
    private String grade;
}
```

📌 In practice this is what teams end up doing, which is why `@ManyToMany` is genuinely rare. In that same codebase it appears in **0** files, against 70 `@ManyToOne` and 49 `@OneToMany`. Treat `@ManyToMany` as a thing to recognise in an interview more than a thing you will write.

---

### D3.10 `CascadeType` — the complete list [+]

Cascading answers: "when this operation happens to the parent, should it happen to the children too?" Without it, `entityManager.persist(parent)` with an unsaved child throws — Hibernate will not guess.

**The complete Jakarta Persistence `CascadeType` enum is six constants:**

| Constant | Cascades when you… | Resulting SQL on the child |
|---|---|---|
| `PERSIST` | `em.persist(parent)` / save a new parent | `INSERT` |
| `MERGE` | `em.merge(parent)` / save a detached parent | `INSERT` or `UPDATE` |
| `REMOVE` | `em.remove(parent)` | `DELETE` |
| `REFRESH` | `em.refresh(parent)` | re-`SELECT` |
| `DETACH` | `em.detach(parent)` | none — evicts from the persistence context |
| `ALL` | shorthand for the five above | — |

📌 **There is no `SAVE_UPDATE` or `REPLICATE` in `jakarta.persistence.CascadeType`.** Those exist only in Hibernate's own `org.hibernate.annotations.CascadeType`, which is a different (provider-specific) enum. If a tutorial shows them on a `jakarta.persistence` import, it is mixing the two.

#### Choosing

| Situation | Cascade |
|---|---|
| child's whole life belongs to the parent (order → line items) | `ALL` + `orphanRemoval = true` |
| you create parent and children together but delete independently | `{PERSIST, MERGE}` |
| `@ManyToMany` | `{PERSIST, MERGE}` — **never** `REMOVE`/`ALL` |
| `@ManyToOne` (child → parent) | ⚠️ almost always **none** |
| children are shared with other parents | none |

📌 **The cascade setting is per-side and does not mirror.** Putting `cascade = CascadeType.ALL` on `Company.employees` does nothing for operations starting from an `Employee`. If you want it both ways you must declare it on both annotations — and for `REMOVE` that is nearly always a mistake.

---

### D3.11 `orphanRemoval` vs `CascadeType.REMOVE` [+]

Both delete children. They trigger on different events.

**`CascadeType.REMOVE`** = *delete by destruction*. Fires only when the **parent itself** is removed.
**`orphanRemoval = true`** = *delete by disconnection*. Fires when a child is **removed from the collection**, even if the parent lives on.

**Spec wording for `orphanRemoval`:** *"If an entity that is the target of the relationship is removed from the relationship (by setting the relationship to null or removing the entity from the relationship collection), the remove operation will be applied to the entity being orphaned."* It is permitted only on `@OneToOne` and `@OneToMany`.

| What you do | `CascadeType.REMOVE` only | `orphanRemoval = true` |
|---|---|---|
| `repo.delete(parent)` | ✅ children deleted | ✅ children deleted (it implies REMOVE on parent deletion) |
| `parent.getChildren().remove(child)` on a **bidirectional** (`mappedBy`) collection | **nothing at all** — no SQL, the row is untouched | ✅ `DELETE FROM children WHERE id = ?` |
| `parent.getChildren().remove(child)` on a **unidirectional** `@OneToMany` + `@JoinColumn` | `UPDATE children SET parent_id = NULL WHERE id = ?` | `UPDATE … SET parent_id = NULL` then `DELETE` |
| `parent.getChildren().clear()` | as above, for every child | ✅ all children deleted |

⚠️ **Correcting a claim you will see everywhere:** "removing from the collection sets the FK to NULL" is only true for the *unidirectional* `@JoinColumn` variant. On a normal bidirectional `mappedBy` collection, removing from the list produces **no SQL whatsoever** — because, as [§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-) established, that collection has no write path. The child keeps pointing at the parent and reappears on next load. This is the single most confusing symptom in JPA and the reason synchronization helpers exist.

#### Which to choose

**`orphanRemoval = true`** when the child is meaningless alone — `Order` → `OrderLineItem`, `Survey` → `Question`, `Course` → `Review`. Removing the line item from the cart *is* deleting it.

**`CascadeType.REMOVE` without `orphanRemoval`** when the child outlives reassignment — `Department` → `Employee`. Closing the department may archive its employees, but moving one employee to another team must never delete them.

**Neither** when children are shared or independently owned.

📌 **The example from your notes, placed correctly:** "an `Employee` removed from a `Project` must not be deleted" is right, but that relationship is usually **many-to-many** (an employee works on many projects). JPA does not even allow `orphanRemoval` on `@ManyToMany`; removing the employee from `project.getEmployees()` deletes only the join-table row, never the employee.

---
### D3.12 `FetchType`, proxies, and lazy loading [+]

`fetch` controls **when** an association is loaded. It goes on the relationship annotation itself:

```java
@ManyToOne(fetch = FetchType.LAZY)   @JoinColumn(name = "company_id") private Company company;
@OneToMany(mappedBy = "company", fetch = FetchType.LAZY)              private List<Employee> employees;
```

#### `EAGER`

Load the association as part of loading the owner. For a `findById`, Hibernate can usually do this with a `LEFT OUTER JOIN` in one query. For a JPQL query it usually **cannot** — see [§D3.13](#d313-the-n1-problem-and-every-way-to-fix-it-).

#### `LAZY`

Load on first access. Instead of the real object, Hibernate injects a **proxy**: a generated subclass whose fields are empty and whose methods trigger a `SELECT` on first call.

```java
Employee e = repo.findById(1L).get();   // SELECT * FROM employees WHERE id = 1
e.getCompany();                         // returns a proxy — still no query
e.getCompany().getName();               // NOW: SELECT * FROM companies WHERE id = ?
```

Three consequences that surprise people:

1. **`e.getCompany().getId()` does not query.** The id is already in the FK column of the row you loaded, so the proxy knows it.
2. **A null FK gives `null`, not a proxy.** Hibernate creates a proxy only when the FK column has a value. ⚠️ The reverse trap: if the FK holds an id with **no matching row** (no FK constraint in the database), you get a proxy that throws `EntityNotFoundException` on first access. `optional = false` lets Hibernate assume the target exists and use an inner join.
3. ⚠️ **`LazyInitializationException`.** Touching a proxy after the persistence context closed (typically after the `@Transactional` method returned, e.g. in a controller or during JSON serialization) throws. The fix is to fetch what you need *inside* the transaction — [§D3.14](#d314-join-fetch-in-depth-) / [§D3.15](#d315-entitygraph-) — **not** to switch to `EAGER`, and **not** `spring.jpa.open-in-view=true`, which hides the problem by holding a database connection for the whole request.

📌 Spring Boot logs a warning about `open-in-view` on startup for exactly this reason. It defaults to `true`, and turning it **off** (`spring.jpa.open-in-view=false`) is the usual recommendation — it converts hidden N+1 queries into loud exceptions during development.

#### Where the lazy/eager choice is honoured — and where it is not

| Mapping | `LAZY` respected? |
|---|---|
| `@ManyToOne` | ✅ yes — the FK is in the row you already loaded |
| `@OneToMany` | ✅ yes (and it is the default) |
| `@ManyToMany` | ✅ yes (and it is the default) |
| `@OneToOne` **owning** side | ✅ yes |
| `@OneToOne` **`mappedBy`** side | ❌ **no** — always a second query ([§D3.7](#d37-onetoone--and-the-lazy-trap-that-catches-everyone-)) |

#### The rule

**Make every association `LAZY`, then explicitly fetch what a given use case needs.** `EAGER` is a decision made once, globally, by someone who could not know what your next query needs; `JOIN FETCH` and `@EntityGraph` are decisions made per query by someone who does.

---

### D3.13 The N+1 problem, and every way to fix it [+]

#### What the N+1 problem is

*"The N+1 query problem happens when the data access framework executes N additional SQL statements to fetch the same data that could have been retrieved when executing the primary SQL query."*

```java
List<Company> companies = companyRepository.findAll();   // 1 query
for (Company c : companies) {
    System.out.println(c.getEmployees().size());          // N queries — one per company
}
```

100 companies → **101 queries**. Each is fast; the round trips are what kill you.

#### ⚠️ `EAGER` does not fix it — it causes it

This is the most important correction in this section. With `@ManyToOne(fetch = EAGER)` and a JPQL query or `findAll()`, Hibernate runs the main query and then issues **one secondary `SELECT` per row**:

*"Unlike the default fetch plan… a JPQL or Criteria API query defines an explicit plan that Hibernate cannot change by injecting a JOIN FETCH automatically."*

So `EAGER` gives you the N+1 *plus* you can never opt out of it. `LAZY` at least gives you the choice.

#### The five fixes

| # | Fix | Scope | Use when |
|---|---|---|---|
| 1 | **`JOIN FETCH`** ([§D3.14](#d314-join-fetch-in-depth-)) | one query | you are writing the JPQL anyway |
| 2 | **`@EntityGraph`** ([§D3.15](#d315-entitygraph-)) | one repository method | you want Spring Data's derived queries |
| 3 | **`@BatchSize` / `default_batch_fetch_size`** | global or per-association | you cannot restructure the queries |
| 4 | **DTO projection** | one query | you only need a few columns, not managed entities |
| 5 | **`@Fetch(FetchMode.SUBSELECT)`** | per association | one extra query total, regardless of parent count |

**Fix 3 in detail** — the global safety net:

```properties
spring.jpa.properties.hibernate.default_batch_fetch_size=20
```

Hibernate then collects up to 20 pending parent ids and issues one query per batch:

```sql
SELECT * FROM employees WHERE company_id IN (1,2,3,…,20);
```

100 companies → `1 + ceil(100/20) = 6` queries instead of 101. It does not eliminate the extra round trips, but it bounds them, and it needs no code change. `@BatchSize(size = 20)` does the same for one association.

**Fix 4 in detail** — if you only need a projection, do not load entities at all:

```java
public record CompanySummary(Long id, String name, long employeeCount) {}

@Query("""
    SELECT new com.example.CompanySummary(c.id, c.name, COUNT(e))
    FROM Company c LEFT JOIN c.employees e
    GROUP BY c.id, c.name
""")
List<CompanySummary> findSummaries();
```

One query, no persistence context, no lazy loading, nothing to go wrong. ↔ [§D5.8](#d58-projections-vs-dtos-q31) compares this with Spring Data REST projections.

---

### D3.14 `JOIN FETCH` in depth [+]

#### What `JOIN FETCH` is

`JOIN FETCH` is a **JPQL** clause (not SQL). It tells Hibernate: perform the join *and* use the joined rows to populate the association in memory.

```java
@Query("SELECT c FROM Company c LEFT JOIN FETCH c.employees WHERE c.id = :id")
Optional<Company> findWithEmployees(@Param("id") Long id);
```

#### `JOIN` vs `JOIN FETCH` — the distinction that matters

```java
// plain JOIN: joins for FILTERING only. employees stays a lazy proxy → N+1 still happens.
@Query("SELECT c FROM Company c JOIN c.employees e WHERE e.name = :n")
List<Company> findByEmployeeName(String n);

// JOIN FETCH: joins AND hydrates. employees is initialised. No N+1.
@Query("SELECT c FROM Company c LEFT JOIN FETCH c.employees")
List<Company> findAllWithEmployees();
```

📌 A plain `JOIN` changes *which rows* you get. `JOIN FETCH` changes *what is loaded into memory*. They are orthogonal, and you can use both in one query.

#### How it maps to SQL joins

| JPQL | SQL | Effect on parents with no children |
|---|---|---|
| `JOIN FETCH` | `INNER JOIN` | ⚠️ **silently dropped from the results** |
| `LEFT JOIN FETCH` | `LEFT OUTER JOIN` | kept, with an empty collection |

⚠️ **Default to `LEFT JOIN FETCH`.** A plain `JOIN FETCH` on a collection turns "list all companies" into "list all companies that have at least one employee" — a filtering change disguised as a performance optimisation. There is no `RIGHT JOIN FETCH` worth using.

#### Fetching more than one association

You can chain, including across levels:

```java
@Query("SELECT c FROM Company c LEFT JOIN FETCH c.employees e LEFT JOIN FETCH e.addresses")
List<Company> loadEverything();
```

This is real production JPQL (entity names changed). It chains four, two levels deep:

```java
"SELECT o from Shipment as o JOIN FETCH o.createdByUser as cbu "
+ "JOIN FETCH o.updatedByUser as ubu JOIN FETCH o.shippingProvider as sp "
+ "JOIN FETCH sp.carrier as c where 1 = 1 "
```

📌 Note those are all `*ToOne` associations — chaining `*ToOne` fetches is cheap and safe, because each adds columns but no rows. A neighbouring repository in the same codebase chains eight `LEFT JOIN FETCH`es the same way.

⚠️ **`MultipleBagFetchException`** — you cannot `JOIN FETCH` two `List` collections at the same level:

```
org.hibernate.loader.MultipleBagFetchException: cannot simultaneously fetch multiple bags
```

A "bag" is Hibernate's name for an unordered `List`. *"The reason why a `MultipleBagFetchException` is thrown by Hibernate is that duplicates can occur, and the unordered `List`, which is called a bag in Hibernate terminology, is not supposed to remove duplicates."*

Changing both to `Set` removes the *exception* — but ⚠️ **it does not remove the problem.** You still get a Cartesian product: 50 posts × 20 comments × 10 tags = 10,000 rows to produce 50 objects. The actual recommendation is *"load at most one collection at a time"*, i.e. one query per collection, letting the persistence context stitch them together.

#### ⚠️ `JOIN FETCH` + pagination: the silent memory bomb

```java
@Query("SELECT c FROM Company c LEFT JOIN FETCH c.employees")
Page<Company> findAllWithEmployees(Pageable pageable);   // ⚠️
```

Hibernate logs:

```
HHH000104:   firstResult/maxResults specified with collection fetch; applying in memory!   ← Hibernate 5
HHH90003004: firstResult/maxResults specified with collection fetch; applying in memory!   ← Hibernate 6
```

📌 The code changed between major versions — same message, same cause. Hibernate 6 also narrowed *when* it fires: Hibernate 5 warns for `JOIN FETCH` **or** an entity graph, Hibernate 6 only for an explicit `JOIN FETCH` clause. ⚠️ That means under Hibernate 6 an `@EntityGraph` + `Pageable` can paginate in memory **without warning you at all** — the behaviour is unchanged, only the log line is gone.

**Why:** the joined result set has one row per *child*, so `LIMIT 20` would slice through the middle of a parent's children and hand you a `Company` with a truncated employee list. *"Because Hibernate favors consistency, it fetches the entire result set and does the pagination in memory."* Your `Page` of 20 is produced by loading **every matching row in the table** into the JVM first.

This is a warning, not an error. It will pass code review, pass tests on a 50-row dev database, and fall over in production.

**The fix — two queries:**

```java
// 1. paginate over IDs only (no fetch join, so SQL LIMIT works)
@Query("SELECT c.id FROM Company c ORDER BY c.name")
Page<Long> findIdPage(Pageable pageable);

// 2. fetch the full objects for that page
@Query("SELECT DISTINCT c FROM Company c LEFT JOIN FETCH c.employees WHERE c.id IN :ids")
List<Company> findWithEmployeesByIds(@Param("ids") List<Long> ids);
```

📌 Pagination with a `*ToOne` fetch join is fine — those do not multiply rows. The rule is specifically about **collection** fetches.

#### When *not* to use `JOIN FETCH`

- With pagination over a collection (above).
- For more than one collection at a time (Cartesian product).
- When you only need scalar fields — use a DTO projection instead.
- When the association is big and you need one field from it — query it directly.

---

### D3.15 `@EntityGraph` [+]

Spring Data JPA's declarative alternative to writing `JOIN FETCH`. It overrides the mapping's fetch plan **for one repository method**, and it works on derived query methods, so you keep `findAll()`, `findByStatus(...)` and friends.

```java
public interface CompanyRepository extends JpaRepository<Company, Long> {

    @EntityGraph(attributePaths = {"employees"})
    List<Company> findAll();                       // overrides the LAZY mapping, here only

    @EntityGraph(attributePaths = {"employees", "employees.addresses"})   // nested paths allowed
    Optional<Company> findById(Long id);
}
```

#### `FETCH` vs `LOAD` — the attribute everybody skips

`@EntityGraph(type = ...)` takes `EntityGraphType.FETCH` (Spring Data's default) or `EntityGraphType.LOAD`, and they differ **only in how attributes you did *not* list are treated**:

| Type | Listed attributes | **Unlisted** attributes |
|---|---|---|
| `FETCH` (default) | `EAGER` | forced to **`LAZY`**, overriding the mapping |
| `LOAD` | `EAGER` | keep their **declared/default** `FetchType` |

📌 So `FETCH` gives you exactly what you asked for and nothing else — which is usually what you want, and which is why it is also the one that will surprise you if an association you relied on being `EAGER` quietly becomes lazy for that one method.

#### `@EntityGraph` vs `JOIN FETCH`

| | `JOIN FETCH` | `@EntityGraph` |
|---|---|---|
| Written as | a JPQL string | an annotation |
| Works with derived queries | ❌ | ✅ |
| Nested paths | ✅ | ✅ (`"a.b"`) |
| Control over join type | ✅ (`LEFT` or inner) | ❌ — provider decides (Hibernate uses a left outer join) |
| Also filters rows | ✅ | ❌ fetch plan only |
| Reusable across methods | ❌ | ✅ via `@NamedEntityGraph` |

Both produce the same *kind* of SQL for the simple case, and both hit exactly the same pagination and Cartesian-product limits — `@EntityGraph` is not a way around [§D3.14](#d314-join-fetch-in-depth-)'s warnings, only a nicer way to write them.

📌 In a large production codebase I checked, `JOIN FETCH` appeared in **6** files and `@EntityGraph` in **0**. Teams there write the JPQL.

---
### D3.16 `equals` and `hashCode` for entities [+]

Collection operations — `Set` membership, `list.remove(child)`, `orphanRemoval` detection — all depend on equality. Entities make this harder than normal objects because an entity's id is **null before persist and non-null after**, so a naive `hashCode` based on the id changes mid-lifecycle and the object is lost inside its own `HashSet`.

⚠️ The failure mode is not an exception. It is `remove()` silently doing nothing.

**The safe pattern:** compare on id, but return a **constant** hash code.

```java
@Entity
public class Employee {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Employee other)) return false;
        return id != null && id.equals(other.id);   // ⚠️ null id ⇒ never equal to anything but itself
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();               // constant across the whole lifecycle
    }
}
```

The reasoning: *"`hashCode()` must return a constant value to ensure equality is consistent across all entity state transitions."* A constant hash degrades a `HashSet` to a list scan — irrelevant for the handful of children in one entity's collection, and correct, which the alternative is not.

📌 If your entity has a genuine **natural key** (an email, a UUID you assign in the constructor, a business identifier), use that in both methods instead. It is stable from birth and this whole problem disappears.

⚠️ **Do not use Lombok's `@Data` or `@EqualsAndHashCode` on entities.** They generate `equals`/`hashCode` over *all* fields, which means touching a lazy association inside `equals` — triggering queries, or `LazyInitializationException`, from inside a `HashSet` lookup.

---

### D3.17 Schema generation: who creates the tables? [+]

Nothing in this section creates a table unless you tell Hibernate to. That is `spring.jpa.hibernate.ddl-auto`:

| Value | What happens at startup |
|---|---|
| `none` | nothing |
| `validate` | compare entities to the existing schema; **fail fast** on mismatch |
| `update` | add missing tables/columns; ⚠️ never drops or alters existing ones |
| `create` | drop and recreate the schema every startup |
| `create-drop` | `create`, plus drop everything on shutdown |

**The default is conditional:** Spring Boot picks `create-drop` if the database is embedded (H2, HSQLDB, Derby) **and no schema manager such as Flyway or Liquibase is handling it**, and `none` otherwise. So the same code silently manages the schema against H2 in a test and does nothing against MySQL in production.

#### So: does Spring Boot create the `student_course` join table for you?

- `ddl-auto=update` / `create` / `create-drop` → **yes**, Hibernate emits the `CREATE TABLE` from your `@JoinTable` with both FK constraints and a composite primary key.
- `ddl-auto=none` / `validate` → **no**. You create it in a migration (Flyway/Liquibase) or it does not exist, and you get `Table 'db.student_course' doesn't exist` at first use — or, with `validate`, a clean failure at startup, which is the point of `validate`.

⚠️ **`update` is for local development only.** It never drops a column, never changes a type, never notices a renamed field (it just adds a new column and leaves the old one). Run migrations in production and set `validate` so a drifted schema fails loudly at boot instead of quietly at 3am.

📌 Mature codebases follow this: the schema is a migration artefact, not a Hibernate side effect.

---

### D3.18 Advanced mappings [+]

#### Composite keys — `@Embeddable` + `@EmbeddedId`

When the primary key is two or more columns (a link table, a time-series metric keyed by entity + date):

```java
@Embeddable
public class EnrolmentId implements Serializable {       // ⚠️ must be Serializable
    private Long studentId;
    private Long courseId;

    // ⚠️ must implement equals() and hashCode() — Hibernate compares keys in memory
    @Override public boolean equals(Object o) { /* both fields */ }
    @Override public int hashCode() { return Objects.hash(studentId, courseId); }
}

@Entity
public class Enrolment {
    @EmbeddedId private EnrolmentId id;
    private String grade;
}
```

The alternative is `@IdClass`, which keeps the fields on the entity and names a separate key class. `@EmbeddedId` is generally preferred — one place to look.

📌 `@EmbeddedId` is common in real code. A typical query is `WHERE pa.id.projectUuid in (:project_uuids)` — note the navigation *into* the composite key.

#### Inheritance — `@Inheritance`

| Strategy | Tables | ✅ | ❌ |
|---|---|---|---|
| `SINGLE_TABLE` (**default**) | one table, all subclass columns, plus a discriminator column | fastest; no joins; polymorphic queries trivial | every subclass column must be nullable — you lose `NOT NULL` |
| `JOINED` | parent table + one table per subclass | properly normalised; constraints work | every read joins |
| `TABLE_PER_CLASS` | one standalone table per concrete subclass, base columns duplicated | fast for a single known subclass | polymorphic queries become `UNION`s |

```java
@Entity
@Inheritance(strategy = InheritanceType.JOINED)
public abstract class Payment {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY) private Long id;
    private BigDecimal amount;
}

@Entity
public class CreditCardPayment extends Payment { private String last4; }
```

📌 `@Inheritance` appeared in **0** files in the production codebase I checked. Composition beats inheritance in persistence even more than elsewhere.

#### `@ElementCollection` — a collection of values, not entities

For a `Set<String>` of tags or a list of embeddables that has no identity of its own:

```java
@Entity
public class Contact {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY) private Long id;

    @ElementCollection
    @CollectionTable(name = "contact_phones", joinColumns = @JoinColumn(name = "contact_id"))
    @Column(name = "phone_number")
    private Set<String> phoneNumbers = new HashSet<>();
}
```

The values live in their own table but have **no lifecycle of their own** — no `@Id`, no repository, deleted with the parent automatically. Defaults to `LAZY`.

⚠️ Like a `List`-based `@ManyToMany`, a `List`-based `@ElementCollection` deletes and re-inserts the whole collection on any change. Use `Set`, or add `@OrderColumn` if order genuinely matters.

---

### D3.19 Serializing bidirectional entities to JSON [+]

A bidirectional pair is a **cycle**. Hand it to Jackson and you get:

```
com.fasterxml.jackson.databind.JsonMappingException: Infinite recursion (StackOverflowError)
```

Company → employees → each employee → company → employees → …

| Fix | How | Notes |
|---|---|---|
| **DTOs** | never serialize entities; map to a response record | ✅ the right answer — also solves `LazyInitializationException` and over-exposure at once ([§P5.2](06-spring-production.md#p52-dtos-vs-entities--never-expose-your-entities-)) |
| `@JsonManagedReference` / `@JsonBackReference` | forward side serialized, back side omitted | asymmetric: the child's parent link vanishes from the JSON |
| `@JsonIgnore` | drop one side entirely | bluntest |
| `@JsonIdentityInfo` | emit the object once, then references by id | keeps both directions; produces JSON clients may not expect |

📌 The production example in §D3.4 uses the annotation route: its `Playlist` entity carries `@JsonBackReference` directly above its `@OneToMany` getter. That works, and it is also a good illustration of why [§P5.2](06-spring-production.md#p52-dtos-vs-entities--never-expose-your-entities-) argues for DTOs: the annotation couples your persistence model to your wire format.

---

### D3.20 The decision checklist [+]

**Choosing the mapping**

| Question | Answer |
|---|---|
| Does one row point at exactly one other, and nothing else points at it? | `@OneToOne` — but first ask whether it should be one table |
| Do many rows point at one? | `@ManyToOne` on the many side (+ `@OneToMany(mappedBy)` if you need the reverse) |
| Do many point at many? | `@ManyToMany` with `Set` — or a join entity if the link has any attribute of its own |
| Is the "child" just a value with no identity? | `@ElementCollection` |

**Defaults to override, every time**

```java
@ManyToOne(fetch = FetchType.LAZY)            // EAGER is the default and is wrong
@OneToOne(fetch = FetchType.LAZY)             // EAGER is the default and is wrong
@ManyToMany                                   // use Set, never List
@JoinColumn(name = "explicit_name")           // never rely on the derived name
```

**The seven traps, in the order they will hit you**

| # | Trap | [§](#d3-jpa-and-hibernate-entity-relationships-) |
|---|---|---|
| 1 | Adding to a `mappedBy` collection writes no SQL | [§D3.4](#d34-owning-side-vs-inverse-side--and-what-mappedby-actually-does-) |
| 2 | `*ToOne` defaults to `EAGER` | [§D3.3](#d33-the-four-relationship-types-at-a-glance-) |
| 3 | `EAGER` causes N+1, it does not fix it | [§D3.13](#d313-the-n1-problem-and-every-way-to-fix-it-) |
| 4 | The `mappedBy` side of a `@OneToOne` can never be lazy | [§D3.7](#d37-onetoone--and-the-lazy-trap-that-catches-everyone-) |
| 5 | `JOIN FETCH` + `Pageable` paginates in memory | [§D3.14](#d314-join-fetch-in-depth-) |
| 6 | `@ManyToMany` with `List` deletes and re-inserts the whole join table | [§D3.9](#d39-manytomany-and-jointable-) |
| 7 | Lombok `@Data` on an entity breaks `equals`/`hashCode` | [§D3.16](#d316-equals-and-hashcode-for-entities-) |

**Sources for this section:** [Jakarta Persistence 3.1 spec](https://jakarta.ee/specifications/persistence/3.1/jakarta-persistence-spec-3.1.html) and its [annotation javadocs](https://jakarta.ee/specifications/persistence/3.1/apidocs/jakarta.persistence/jakarta/persistence/onetomany) (defaults, `CascadeType`, `orphanRemoval`, `@JoinColumn` naming); [Vlad Mihalcea on `@OneToOne`](https://vladmihalcea.com/the-best-way-to-map-a-onetoone-relationship-with-jpa-and-hibernate/), [`@OneToMany`](https://vladmihalcea.com/the-best-way-to-map-a-onetomany-association-with-jpa-and-hibernate/), [`@ManyToMany`](https://vladmihalcea.com/the-best-way-to-use-the-manytomany-annotation-with-jpa-and-hibernate/), [N+1](https://vladmihalcea.com/n-plus-1-query-problem/), [`MultipleBagFetchException`](https://vladmihalcea.com/hibernate-multiplebagfetchexception/), [HHH000104](https://vladmihalcea.com/fix-hibernate-hhh000104-entity-fetch-pagination-warning-message/); [Spring Boot data-access how-to](https://docs.spring.io/spring-boot/how-to/data-access.html); [Spring Data JPA `EntityGraphType`](https://docs.spring.io/spring-data/jpa/docs/current/api/org/springframework/data/jpa/repository/EntityGraph.EntityGraphType.html).

---


## D4. Transactions and query performance in production

Two operational topics that decide whether the mappings in [§D3](#d3-jpa-and-hibernate-entity-relationships-) survive production traffic: where transaction boundaries go, and how many queries a request really runs.

🔗 `@Transactional` is an AOP proxy, so the proxy rules in [§C5](02-spring-core.md#c5-proxies-jdk-dynamic-proxies-cglib-and-configuration-full-vs-lite-mode) and [§C6](02-spring-core.md#c6-aspect-oriented-programming-aop-) apply. Events that should fire only after commit use `@TransactionalEventListener` ([§C7](02-spring-core.md#c7-spring-application-events)).

### D4.1 Transactions [+]

```java
@Service
@RequiredArgsConstructor
public class OrderService {
    private final OrderRepository orders;
    private final InventoryService inventory;
    private final PaymentClient payments;            // used in the "network calls" trap below

    @Transactional                                   // ✅ on the SERVICE, not the controller or repository
    public Order place(CreateOrderRequest r) {
        Order o = orders.save(Order.from(r));
        inventory.reserve(o);                        // same transaction — rolls back together
        return o;
    }
}
```

⚠️ **Four traps, in the order you'll hit them:**

| Trap | Detail |
|---|---|
| **Self-invocation** | `@Transactional` is an **AOP proxy** ([§C2.13](02-spring-core.md#c213-what-actually-happens-at-startup-the-mechanism)). Calling it from another method of the same class **silently skips the transaction.** |
| **Only `RuntimeException` (and `Error`) rolls back** | By default a **checked** exception **commits**. Use `@Transactional(rollbackFor = Exception.class)` if you throw checked exceptions. |
| **`private`/`final` methods** | Cannot be proxied. The annotation is silently ignored. |
| **Network calls inside a transaction** | ⚠️ `payments.charge()` inside `@Transactional` holds a **database connection** for the whole HTTP round-trip. Under load the connection pool empties and the service stops. **Keep I/O outside the transaction.** |

💡 **`@Transactional(readOnly = true)` on query methods** lets Hibernate skip dirty-checking and flushing, and marks the JDBC connection read-only. It can route to a read replica **only if** you configured a routing `DataSource` for that (for example `AbstractRoutingDataSource` keyed on the read-only flag). Cheap and worth doing by default on reads.

### D4.2 Which repository methods are transactional by default — and the `deleteBy…` trap

The Spring Data JPA reference is precise: *"methods inherited from `CrudRepository` inherit the transactional configuration from `SimpleJpaRepository`. For read operations, the transaction configuration `readOnly` flag is set to `true`. All others are configured with a plain `@Transactional`."* But *"declared query methods (including default methods) do not get any transaction configuration applied by default."*

| Method | Transaction if the caller has none? |
|---|---|
| `save`, `delete`, `deleteById`, `findById`, `findAll` (inherited) | ✅ yes (`SimpleJpaRepository`'s own `@Transactional`) |
| `findByEmail(...)` (derived read) | not needed for reading; runs without one |
| `deleteByUser(user)` (derived delete) | ❌ **none**, yet it must remove entities |
| `@Modifying @Query("delete …")` | ❌ none; you must add `@Transactional` |

⚠️ **Why `deleteBy…` fails.** A derived delete *"runs a query and then deletes the returned instances one by one"* (so `@PreRemove` callbacks fire). Removing entities requires an active transaction. Called from a method without `@Transactional`, it fails with `InvalidDataAccessApiUsageException: No EntityManager with actual transaction available for current thread - cannot reliably process 'remove' call`. Here is how that message is produced, verified in Framework 7.0.9 source:
- Spring's shared `EntityManager` proxy (`SharedEntityManagerCreator`) throws JPA's `TransactionRequiredException` with that text.
- `EntityManagerFactoryUtils.convertJpaAccessExceptionIfPossible` translates it to `InvalidDataAccessApiUsageException`.
- The method name in quotes is whatever was called, here `remove`.

**Fix:** call it from a `@Transactional` service method (the usual answer), or annotate the repository method:

```java
public interface RefreshTokenRepository extends JpaRepository<RefreshToken, Long> {
    @Transactional                       // derived deletes need a transaction
    void deleteByUser(User user);

    @Modifying                           // bulk JPQL: one DELETE, no @PreRemove, no orphan handling
    @Transactional
    @Query("delete from RefreshToken t where t.expiryDate < :now")
    int deleteExpired(@Param("now") Instant now);
}
```

📌 **Derived delete vs bulk delete:** `deleteBy…` loads every matching row into memory first, then deletes each one. That is correct but slow for large sets. `@Modifying @Query` issues a single statement but **bypasses** the persistence context, so entities already loaded in the session are stale afterwards (`@Modifying(clearAutomatically = true)` clears them).

🔗 The JWT refresh-token flow in [§S3](05-spring-security.md#s3-stateless-authentication-jwt-and-refresh-tokens) uses exactly this `deleteByUser` method.

### D4.3 The N+1 query problem [+]

**The most common performance bug in every Java service you will ever touch.** This is the operational summary; [§D3.13](#d313-the-n1-problem-and-every-way-to-fix-it-) has the full treatment — including why `FetchType.EAGER` **causes** N+1 rather than fixing it, and all five remedies compared.

```java
List<Order> orders = repo.findAll();                 // 1 query
for (Order o : orders) {
    o.getItems().size();                             // ⚠️ +1 query EACH → 1 + N queries
}
```
100 orders → **101 queries.** It never shows up in tests with 3 rows, and it destroys the endpoint in production.

```java
// ✅ Fix 1 — JOIN FETCH
@Query("select distinct o from Order o join fetch o.items where o.status = :s")
List<Order> findWithItems(@Param("s") OrderStatus s);

// ✅ Fix 2 — @EntityGraph (full treatment in §D3.13)
@EntityGraph(attributePaths = {"items", "customer"})
List<Order> findByStatus(OrderStatus status);

// ✅ Fix 3 — batch the collection loads: 101 queries → 1 + ceil(N/50)
//    application.yml: spring.jpa.properties.hibernate.default_batch_fetch_size: 50
```
⚠️ **`JOIN FETCH` and pagination don't mix.** Fetching a collection with `Pageable` makes Hibernate load **everything** into memory and paginate there, logging `HHH90003004` (Hibernate 6) or `HHH000104` (Hibernate 5): `firstResult/maxResults specified with collection fetch; applying in memory`. Use `default_batch_fetch_size`, or the two-query id-then-fetch pattern in [§D3.14](#d314-join-fetch-in-depth-).

💡 **Catch it automatically in tests**, rather than in production:
```properties
logging.level.org.hibernate.SQL=DEBUG           # count the queries
spring.jpa.properties.hibernate.generate_statistics=true
```
And add **datasource-proxy** or **[quick-perf](https://github.com/quick-perf/quickperf)** to assert a query budget in an integration test.

## D5. Spring Data REST [Q22–Q26, Q29–Q31]

> **Your question [Q22]:** *"how spring boot data rest is replacing or getting used instead of restController with entity? when should we use this… and is this an industry standard approach? how this works and how routing happens without telling route path and how it will integrate with the database, what if we have complex logic in our crud operation not just simply crud but there are business logic there in each crud api endpoint?"*

### D5.1 The mental shift, and the two architectural flows [Q22, Q24]

You have to shift your perspective away from traditional controller architecture. In a traditional Spring Boot app **you are the middleman**, hand-writing plumbing: a table needs an Entity, which needs a Repository, which needs a Service, which needs a Controller with explicit `@RequestMapping`s.

**Spring Data REST eliminates that middleman for standard CRUD.** It hooks directly into your Spring Data repositories and exposes them as fully functional HTTP endpoints — **without a single `@RestController`.**

```
TRADITIONAL ARCHITECTURE FLOW:
[HTTP Request] ➔ [ @RestController ] ➔ [ @Service ] ➔ [ Repository ] ➔ [ Entity / DB ]

SPRING DATA REST FLOW:
[HTTP Request] ➔ [ Spring Data REST Engine ] ─────────➔ [ Repository ] ➔ [ Entity / DB ]
```

| | Traditional | Spring Data REST |
|---|---|---|
| **Required components** | Entity + Repository + Service + `@RestController` | ✅ **Entity + Repository only** |
| Route declaration | explicit `@GetMapping("/users/{id}")` | derived at startup by reflection |
| Response format | whatever you return | **HAL** (`application/hal+json`) by default |
| Where business logic goes | the `@Service` | lifecycle event listeners, or a custom controller |

In the Spring Data REST flow the framework contributes a built-in internal controller (`RepositoryEntityController`, `RepositoryPropertyReferenceController`, `RepositorySearchController`) that reads the incoming HTTP stream, validates the JSON, and drives the repository directly.

**The dependency:**
```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-rest</artifactId>
</dependency>
```

### D5.2 How routing happens with no `@RequestMapping` [Q22]

*(Your diagram, preserved.)*
```
[ Incoming HTTP Request ] 
          │
          ▼
┌───────────────────────────────┐
│ Spring Data REST Engine       │  ◄── Plugs into Repository definitions
└───────────────────────────────┘
          │
          ▼
┌───────────────────────────────┐
│ Spring Data JPA Repository    │  ◄── Automatically maps to SQL queries
└───────────────────────────────┘
          │
          ▼
┌───────────────────────────────┐
│ Database (PostgreSQL/MySQL)   │
└───────────────────────────────┘
```

At application boot, instead of scanning for path strings in controllers, Spring Data REST uses **reflection** to inspect your repository interfaces:
1. It finds the **entity type** each repository manages (from the generic parameter).
2. It applies a **pluralization algorithm** to the entity name and lowercases it.
3. `interface UserRepository extends CrudRepository<User, Long>` → base route **`/users`**.

Override it without writing a controller:
```java
@RepositoryRestResource(path = "members", collectionResourceRel = "members")
public interface UserRepository extends CrudRepository<User, Long> {}
// instantly changes the auto-generated route from '/users' to '/members'
```

**The endpoints you get for free:**

| Method + path | Repository method | Response |
|---|---|---|
| `GET /users` | `findAll(Pageable)` | 200, HAL collection + `page` |
| `GET /users/{id}` | `findById(id)` | 200 / 404 |
| `POST /users` | `save(entity)` | **201** + `Location` header |
| `PUT /users/{id}` | `save(entity)` | 200/204 — **full replace** |
| `PATCH /users/{id}` | `save(entity)` | 200/204 — partial merge |
| `DELETE /users/{id}` | `deleteById(id)` | 204 |
| `GET /users/search` | — | lists every exported query method |
| `GET /users/{id}/{assoc}` | — | a followed association |
| `GET /profile` | — | ALPS metadata for the whole API |

#### What `path` and `collectionResourceRel` control [Q23]

> **Your question [Q23]:** *"what do these two — `path` and `collectionResourceRel` — tell? and will this work the same if db is NoSQL as well like MongoDB?"*

| Property | Controls | Default | Override effect |
|---|---|---|---|
| **`path`** | the **network URI segment** clients hit | pluralised, lowercased entity name → `/users` | `path="members"` → URL becomes `/members` |
| **`collectionResourceRel`** | the **JSON key inside `_embedded`** | the same pluralised name → `"users"` | `collectionResourceRel="members"` → `_embedded.members` |

```json
{
  "_embedded": {
    "members": [                       // ← changed from "users" by collectionResourceRel
      { "firstName": "Alice", "_links": { } }
    ]
  },
  "_links": { }
}
```
💡 **Why this matters:** front ends parse on these keys. If the business decides "Users" are now "Members" across the UI, one property updates both the URL and the JSON shape — no controller touched.

Two related properties worth knowing: **`itemResourceRel`** (the rel for a *single* item) and **`exported = false`** (hide the repository entirely).

#### Does it work with MongoDB? [Q23]

**Yes, absolutely — Spring Data REST is database-agnostic.** It does not hook into Hibernate or SQL; it hooks into the abstract **Spring Data Commons** layer.

```java
@RepositoryRestResource(path = "members", collectionResourceRel = "members")
public interface UserRepository extends MongoRepository<User, String> {}   // instead of JpaRepository
```
```java
@Document(collection = "users")        // @Document, not @Entity
public class User {
    @Id private String id;             // String/ObjectId, not an auto-increment Long
    private String firstName;
}
```
`GET /members/60c72b2f9b1d` → the engine invokes `findById("60c72b2f9b1d")` → the Spring Data MongoDB driver issues `db.users.find({"_id": ObjectId("...")})` instead of a SQL `SELECT` → the retrieved object is serialised into the **exact same HAL JSON**.

**The core difference to keep in mind:** routing, URLs, interceptors and JSON formats are identical; only the **entity definitions and ID types** change (`@Document` vs `@Entity`, `String`/`ObjectId` vs `Long`). The same holds for Spring Data JDBC, Cassandra, Neo4j and Redis.

### D5.3 Naming conventions and irregular plurals [Q29]

> **Your question [Q29]:** *"it creates api with url after making the first letter of entity small and appending 's'… how to handle the case when the plural form is not that simple like [person → people, goose → geese]? so for that we use RepositoryResourcePath"*

> 📌 **Spring Data REST handles irregular plurals correctly.** It uses **Evo Inflector** (`org.atteo:evo-inflector`), a Java implementation of **Damian Conway's pluralization algorithm**. `Person` → **`/people`**, `Goose` → **`/geese`**, `Category` → **`/categories`**, and `Person`'s rel → `"people"`.
>
> ⚠️ **The caveat that makes this practically important:** Evo Inflector must be **on the classpath**. Spring Data REST declares it as an **optional** dependency, so depending on your build it may be absent — and *then* the fallback really is a naive `+ "s"`, giving you `/persons`. If irregular plurals matter, add it explicitly and verify with `GET /profile`:
> ```xml
> <dependency>
>     <groupId>org.atteo</groupId>
>     <artifactId>evo-inflector</artifactId>
> </dependency>
> ```
>
> Also: the annotation that pins a path is **`@RepositoryRestResource`** — that is the only name for it.

**Either way, be explicit.** Relying on any inflection algorithm for your public URL contract is fragile:
```java
// Overriding irregular plurals explicitly — always safe, always readable
@RepositoryRestResource(path = "people", collectionResourceRel = "people")
public interface PersonRepository extends CrudRepository<Person, Long> {}
```

### D5.4 How Spring knows which field is the primary key [Q24]

> **Your question [Q24]:** *"how did spring know that our primary key is `id`? it could be anything like `user_id` etc."*

**It never guesses by field name.** Two pieces of information combine:

**1. The `@Id` annotation on the entity** — this is the declaration, whatever the field or column is called:
```java
@Entity
public class User {
    @Id                          // ← "THIS is the primary key field"
    @Column(name = "user_id")    // ← the DB column can be called anything
    private Long userId;         // ← so can the Java field
    private String name;
}
```

**2. The repository's generic signature** — the second type parameter is the ID type:
```java
public interface UserRepository extends CrudRepository<User, Long> {}
//                                                     ^^^^  ^^^^
//                                                   entity   ID type, must match the @Id field
```

At runtime Spring Data REST reads the generic parameter (`Long`), inspects `User` to find the field marked `@Id`, and wires it into `findById(ID id)`.

⚠️ Note there are **two different `@Id` annotations**: `jakarta.persistence.Id` for JPA, and `org.springframework.data.annotation.Id` for MongoDB / JDBC / Cassandra. Importing the wrong one gives a confusing "no id property found" error at startup.

### D5.5 Adding business logic beyond CRUD [Q22, Q24]

> **Your question [Q22]:** *"what if we have complex logic in our crud operation, not just simply crud but there is business logic in each crud api endpoint?"*

There is no `@RestController` to put it in, so Spring Data REST gives you **two patterns**.

#### Pattern A — Application events (entity lifecycle hooks)

Spring Data REST publishes `ApplicationContext` events around every entity operation. Extend `AbstractRepositoryEventListener<T>`:

```java
@Component
public class UserBeforeCreateListener extends AbstractRepositoryEventListener<User> {

    @Autowired
    private EmailService emailService;

    @Override
    protected void onBeforeCreate(User user) {
        // 1. Custom validation
        if (user.getEmail() == null) {
            throw new IllegalArgumentException("Email is strictly mandatory!");
        }
        // 2. Modify data before persistence
        user.setStatus("PENDING_ACTIVATION");
    }

    @Override
    protected void onAfterCreate(User user) {
        // 3. Post-persistence side effects
        emailService.sendWelcomeEmail(user.getEmail());
    }
}
```

**[+] The complete hook list** — worth having, because the docs bury it:

| Before | After | Fires on |
|---|---|---|
| `onBeforeCreate` | `onAfterCreate` | `POST` |
| `onBeforeSave` | `onAfterSave` | `PUT` / `PATCH` |
| `onBeforeDelete` | `onAfterDelete` | `DELETE` |
| `onBeforeLinkSave` | `onAfterLinkSave` | association updated |
| `onBeforeLinkDelete` | `onAfterLinkDelete` | association removed |

The annotation-based alternative, if you prefer one class per aggregate:
```java
@RepositoryEventHandler(User.class)
@Component
public class UserEventHandler {
    @HandleBeforeCreate public void beforeCreate(User u) { ... }
    @HandleAfterCreate  public void afterCreate(User u)  { ... }
}
```

⚠️ **Two real hazards with this pattern.** First, the `onAfter*` hooks run **on the request thread, before the HTTP response**, so a slow email send blocks the request. `RepositoryEntityController` publishes `AfterCreateEvent` right after `invokeSave(…)` returns, and the controller itself is not `@Transactional`, so by then the repository's own transaction has normally **already committed**. Offload slow work with `@Async` ([§P3](06-spring-production.md#p3-background-work-scheduled-and-async)). ⚠️ A `@TransactionalEventListener` would not fire here unless an outer transaction is active (or `fallbackExecution = true`). Second, **the logic is invisible from the endpoint**: nothing in the code says `POST /users` sends an email. That is exactly the debuggability cost flagged in [§D5.12](#d512-when-to-use-it-and-when-not-to-q22).

#### Pattern B — Co-existing with custom controllers [Q24]

> **Your question [Q24]:** *"how is this possible? using spring data rest we will not have some components that are required in the controller flow — how do both of these two exist together?"*

**Spring Data REST is not all-or-nothing.** The answer is **composition**: your custom controller injects the **repository** directly, or you introduce a `@Service` for that one endpoint.

**The mechanics of path hijacking.** Spring Data REST registers its auto-generated endpoints at a **lower priority** than user-defined ones. An incoming request is matched against your `@RestController`/`@RepositoryRestController` beans first; if one matches, Spring Data REST backs off for that route entirely.

**A concrete example** — `GET /users`, `GET /users/{id}` and `DELETE /users/{id}` stay automatic, but `PUT /users/{id}/promote` is yours:

```java
// The shared entity & repository — unchanged
@Entity
public class User {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;
    private String status;   // "REGULAR", "PREMIUM"
}

// Automatically exposes: GET /users, POST /users, DELETE /users/{id}
public interface UserRepository extends CrudRepository<User, Long> {}
```
```java
// A service ONLY for the complex logic
@Service
public class UserBusinessService {
    @Autowired private UserRepository userRepository;

    @Transactional
    public User promoteToPremium(Long userId) {
        User user = userRepository.findById(userId)
            .orElseThrow(() -> new ResourceNotFoundException("User not found"));
        user.setStatus("PREMIUM");
        // Trigger external operations here (e.g. send a billing notification email)
        return userRepository.save(user);
    }
}
```
```java
import org.springframework.data.rest.webmvc.RepositoryRestController;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;

@RepositoryRestController          // ⚠️ NOT @RestController — see the table below
public class CustomUserManagementController {

    @Autowired private UserBusinessService userBusinessService;

    @PutMapping("/users/{id}/promote")
    public @ResponseBody ResponseEntity<?> promoteUser(@PathVariable("id") Long id) {
        User premiumUser = userBusinessService.promoteToPremium(id);
        return ResponseEntity.ok(premiumUser);
    }
}
```

**Why it works:**
- `GET /users/5` → no custom mapping → Spring Data REST handles it from the repository.
- `PUT /users/5/promote` → Spring finds your controller first → your service runs → saved.

⚠️ **`@ResponseBody` is mandatory** on `@RepositoryRestController` methods (or on the class). Unlike `@RestController`, it is **not** implied — and omitting it makes Spring try to resolve your return value as a **view name**, producing a baffling `TemplateInputException` or 404.

#### `@RepositoryRestController` vs `@BasePathAwareController` vs `@RestController` [Q26]

| | **`@RepositoryRestController`** | **`@BasePathAwareController`** | **`@RestController`** |
|---|---|---|---|
| Adopts `spring.data.rest.base-path` | ✅ | ✅ | ❌ — you write the full path |
| Tied to a repository resource | ✅ intended to extend/hijack one | ❌ independent of repositories | ❌ |
| HAL-JSON message converters | ✅ | ✅ | ❌ plain Jackson |
| `@ResponseBody` implied | ❌ **must add it** | ❌ **must add it** | ✅ |
| **Use for** | a custom sub-route on an existing collection, e.g. `PUT /api/v1/members/{id}/promote` | a utility endpoint under the same prefix that maps to no collection, e.g. `POST /api/v1/system/purge-cache` | anything outside the Spring Data REST world |

### D5.6 Controlling path variables and query parameters [Q25, Q26]

> **Your question [Q25]:** *"how to control the path param variable — is this `id`, `{user_id}`, or can we only have the primary key as the id path variable when using spring data rest? same question for query parameters."*

**The summary rule of thumb:**

| | Customizable? |
|---|---|
| **Path variables** (`/members/105`) | ❌ **Locked to the `@Id` value.** Requires a custom controller to change. |
| **Query parameters** (`?email=…`) | ✅ **100% customizable out of the box**, via repository query methods. |

#### Path variables are rigid

The single-resource URL is strictly `GET /members/{id}`, and `{id}` maps to the value of whatever field is annotated `@Id`. Even if your Java field is `userId` and the column is `user_id`, the URL still carries the **primary key value**: `GET /members/101`.

**To look up by a different unique field** (`GET /members/alice99`), hijack the route:
```java
@RepositoryRestController
public class CustomMemberLookupController {

    @Autowired private UserRepository userRepository;

    @GetMapping("/members/{username}")
    public @ResponseBody ResponseEntity<?> getMemberByUsername(@PathVariable("username") String username) {
        User user = userRepository.findByUsername(username)
            .orElseThrow(() -> new ResourceNotFoundException("Member not found"));
        return ResponseEntity.ok(user);
    }
}
```
⚠️ **This shadows the numeric lookup.** `/members/{username}` and `/members/{id}` are equally specific, so you may get the ambiguity error from [§W4.13](03-spring-web.md#w413-routing-does-declaration-order-matter), or your controller may swallow `/members/105` too. In practice use a distinct sub-path — `/members/by-username/{username}` — or a search endpoint.

> **Your follow-up [Q26]:** *"can't we use `RepositoryRestConfigurer` for this use case?"*
>
> **No.** `RepositoryRestConfigurer` controls base paths, CORS, metadata exposure, ID exposure, Jackson modules and validators — but **not** the URI template for default endpoints. Spring Data REST's core design is that *a URL identifies a resource by its persistent identifier*, and the parsing of that segment is built into the framework's mapping classes. To route on an alternate unique property you must fall back to a custom controller.
>
> 💡 **[+] There is one genuinely useful middle ground:** `RepositoryRestConfiguration.withEntityLookup()` lets you change **how the `{id}` segment is resolved into an entity** — so the URL can carry a username while the framework still treats it as the identifier, keeping HAL links consistent:
> ```java
> @Component
> public class LookupConfig implements RepositoryRestConfigurer {
>     @Override
>     public void configureRepositoryRestConfiguration(RepositoryRestConfiguration config, CorsRegistry cors) {
>         config.withEntityLookup()
>               .forRepository(UserRepository.class,
>                              User::getUsername,                 // entity → URI segment
>                              UserRepository::findByUsername);   // URI segment → entity
>     }
> }
> ```
> `GET /members/alice99` now works **and** every generated `self` link uses `alice99`. Note what this is actually doing: not `RepositoryRestConfigurer` changing the URI *template*, but changing the *identifier mapping* — which reaches the same goal.

#### Query parameters are fully flexible

You control them by writing **query methods** in the repository. Spring Data REST scans them and exposes them under a generated `/search` sub-resource:

```java
import org.springframework.data.repository.query.Param;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import org.springframework.data.rest.core.annotation.RestResource;
import org.springframework.data.repository.CrudRepository;

@RepositoryRestResource(path = "members", collectionResourceRel = "members")
public interface UserRepository extends CrudRepository<User, Long> {

    // 1. Custom search path and query parameter name
    @RestResource(path = "by-email", rel = "by-email")
    Optional<User> findByEmail(@Param("email") String email);
    // @Param("email") maps the HTTP query parameter '?email=...' to this Java argument

    // 2. Filtering a collection by a status query param
    @RestResource(path = "active", rel = "active")
    List<User> findByStatus(@Param("status") String status);
}
```
- `GET /members/search/by-email?email=alice@example.com`
- `GET /members/search/active?status=ACTIVE`

Hitting the directory endpoint `GET /members/search` lists everything available, as a **URI Template** (note the `{?email}` syntax — RFC 6570):
```json
{
  "_links": {
    "by-email": { "href": "http://localhost:8080/members/search/by-email{?email}" },
    "active":   { "href": "http://localhost:8080/members/search/active{?status}" }
  }
}
```
⚠️ **`@Param` is required.** Without it, the parameter name must survive compilation (`-parameters`), and Spring Data REST will otherwise report the parameter as unnamed and the search will 400.

### D5.7 Projections [Q30] — and what they actually optimise

By default Spring Data REST serialises the **entire entity**. **Projections** create tailored views — to hide sensitive fields, drop heavy columns, or compute combined ones.

**Step A — the entity:**
```java
@Entity
public class User {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String firstName;
    private String lastName;
    private String email;
    private String password;             // hide completely!
    private String internalSystemNotes;  // hide too!
}
```

**Step B — the projection interface** (no DTO class, no mapper):
```java
import org.springframework.data.rest.core.config.Projection;
import org.springframework.beans.factory.annotation.Value;

@Projection(name = "userSummary", types = { User.class })
public interface UserSummaryProjection {

    // 1. Closed: a direct getter matching the entity
    String getEmail();

    // 2. Open: a SpEL target expression combining fields on the fly
    @Value("#{target.firstName} #{target.lastName}")
    String getFullName();
}
```

**Step C — the repository is unchanged:**
```java
@RepositoryRestResource(path = "members", collectionResourceRel = "members")
public interface UserRepository extends JpaRepository<User, Long> {}
```

**Consuming it:** `GET /api/v1/members?page=0&size=5&projection=userSummary`
```json
{
  "_embedded": {
    "members": [
      {
        "fullName": "Alice Smith",
        "email": "alice@example.com",
        "_links": {
          "self": { "href": "http://localhost:8080/api/v1/members/1" },
          "user": { "href": "http://localhost:8080/api/v1/members/1{?projection}" }
        }
      }
    ]
  },
  "page": { "size": 5, "totalElements": 1, "totalPages": 1, "number": 0 }
}
```
`password` and `internalSystemNotes` are stripped, and `fullName` is injected.

> 📌 **`?projection=` does not change the SQL.** Spring Data REST applies that parameter at **serialization time**: the engine loads the **full entity** through the normal repository method, then wraps it in a projection proxy while writing JSON. **No columns are saved. No SQL changes.** You get a smaller *payload*, not a cheaper *query*.
>
> The "closed projections optimize SQL" rule is true — but only for **repository-return-type projections**, a different feature:
> ```java
> public interface UserRepository extends JpaRepository<User, Long> {
>     // ✅ THIS optimizes the SQL: Hibernate selects only first_name, last_name
>     List<UserNameOnly> findByStatus(String status);
> }
> interface UserNameOnly { String getFirstName(); String getLastName(); }
> ```
> And the best-performing variant is a **class-based (DTO) projection**, where Hibernate emits a constructor expression:
> ```java
> public record UserNameDto(String firstName, String lastName) {}
> List<UserNameDto> findByStatus(String status);   // → SELECT u.first_name, u.last_name FROM users u
> ```
>
> 💡 **So the practical takeaway inverts:** use `?projection=` for **shaping and hiding**, never for performance. Use a **repository return type** when you actually need to reduce the query. And ⚠️ note that `?projection=` still loads `password` into memory — it merely omits it from the JSON, so it is a **presentation** control, not a **security** control.

**Open vs closed projections** — the distinction is still real, just about a different cost:

| | Closed projection | Open projection |
|---|---|---|
| Definition | only getters matching entity properties | uses `@Value` + SpEL |
| Evaluation | direct property access on the loaded entity | SpEL evaluated per property per row |
| Repository-return-type SQL optimization | ✅ possible | ❌ never — needs the whole entity |
| `?projection=` SQL optimization | ❌ — serialization-time only | ❌ |
| Cost | low | SpEL parsing overhead on large result sets |

**Making a projection the default:**
```java
@RepositoryRestResource(
    path = "members",
    collectionResourceRel = "members",
    excerptProjection = UserSummaryProjection.class)   // applied to COLLECTION listings
public interface UserRepository extends JpaRepository<User, Long> {}
```
⚠️ **`excerptProjection` applies to collections and to embedded associations only.** A direct `GET /members/1` still returns the **full entity** unless the client passes `?projection=userSummary`. This asymmetry is a long-standing complaint and a genuine data-leak footgun: your list endpoint hides `password`, your detail endpoint does not.

### D5.8 Projections vs DTOs [Q31]

> **Your question [Q31]:** *"I think DTO is a more reliable use case in the real world as we don't need to send the projection in the query parameter? if DTO is for this purpose only then why do projections exist, and what's the difference, and when to use what?"*

**Your intuition is correct, and it matches what most enterprise teams do.** But projections solve a different problem.

| Dimension | **Projections** | **DTOs (via Service/Controller)** |
|---|---|---|
| Component type | Java **interface**, framework-managed | Java **class**, developer-managed |
| Boilerplate | near zero — one interface | high — controller + service + DTO + mapping |
| Client control | **dynamic** — client picks via `?projection=` | **static** — the endpoint contract decides |
| Performance (SQL) | only repository-return-type projections optimize ([§D5.7](#d57-projections-q30--and-what-they-actually-optimise)) | explicit — JPQL constructor expressions, fetch graphs |
| Architectural style | **contract-last**, bound to Spring Data REST | **contract-first / DDD**, isolates DB from client |
| Compile-time safety | ⚠️ the projection name is a **string** in a URL | ✅ a type |

**Why projections exist at all:** they support the rapid-CRUD/HATEOAS philosophy. If one front end needs 5 different shapes of `User` (dropdown, table summary, full profile, admin overview, export), the DTO approach means 5 DTO classes, 5 service methods and 5 endpoints. With projections the backend writes **1 repository and 5 thin interfaces**, and the front end picks per call — no new Java plumbing. It maximises front-end independence.

**Choose DTOs when** *(the industry-standard default)*:
- **Strict security.** A DTO is a concrete firewall. With projections, one forgotten `exported = false` or one missing projection name and the **full entity** leaks ([§D5.7](#d57-projections-q30--and-what-they-actually-optimise) shows exactly how).
- **Complex transformation.** Combining three databases, calling a downstream gRPC service, heavy formatting — a framework projection cannot do it.
- **Microservice mesh architecture.** Distributed systems want rigid, type-safe schemas that don't depend on a URL parameter to decide the payload shape.

**Choose projections when:**
- You have already committed to Spring Data REST / HATEOAS for a dashboard or internal ops tool.
- Read-heavy internal admin consoles — listing rows with quick column filtering.
- Rapid MVPs where velocity dominates.

> **Summary for your own codebase:** public-facing or microservice-driven applications where stability, compile-time type safety and explicit security boundaries matter → **DTO + service layer**. Pure CRUD back-office panels mapping rows to views with few side effects → **projections**, ideally via `excerptProjection`.

### D5.9 Associations and `AggregateReference` [Q26]

**Association** — a relationship between two managed entities (`@ManyToOne`, `@OneToMany`). Spring Data REST does **not** embed the child data in the parent JSON; it exposes the relationship as a **hypermedia link**:
```json
{
  "firstName": "Alice",
  "_links": {
    "self":      { "href": "http://localhost:8080/members/1" },
    "addresses": { "href": "http://localhost:8080/members/1/addresses" }
  }
}
```
Follow it with `GET /members/1/addresses`. You **manipulate** associations with the `text/uri-list` content type, which surprises everyone the first time:
```http
PUT /members/1/addresses
Content-Type: text/uri-list

http://localhost:8080/addresses/7
http://localhost:8080/addresses/9
```
`PUT` replaces the whole set, `POST` appends, `DELETE /members/1/addresses/7` removes one.

**`AggregateReference`** — used to implement clean **Domain-Driven Design**. Instead of coupling entities with `@ManyToOne Order order`, you hold only the foreign ID:
```java
AggregateReference<Order, Long> orderRef;
```
This keeps aggregates independent and avoids loading deep relational graphs.

> 📌 **`AggregateReference` is a Spring Data JDBC type** — `org.springframework.data.jdbc.core.mapping.AggregateReference`. Spring Data MongoDB has no such class; its equivalents are `@DBRef` (a real reference, discouraged) or, idiomatically, just storing the raw id field. The DDD *principle* — reference other aggregates by identity, never by object graph — is universal, but the **class** is JDBC-only.

💡 **[+] Why this matters to you specifically.** In a microservice gateway, entities routinely live in *other services*. `AggregateReference` (or a plain `orderId` field) is the correct modelling choice there, because a JPA `@ManyToOne` across a service boundary is impossible. This is the same instinct as a foreign key that your ORM refuses to join.

### D5.10 Hiding endpoints, rels, Jackson and CORS [Q26]

#### `@RestResource` and hiding CRUD methods

`@RestResource` controls the visibility and naming of exposed endpoints. Override the inherited method signature and set `exported = false`:
```java
@RepositoryRestResource(path = "members")
public interface UserRepository extends CrudRepository<User, Long> {

    // Hide DELETE /members/{id} completely
    @Override @RestResource(exported = false)
    void deleteById(Long id);

    // Hide POST /members (disabling member creation)
    @Override @RestResource(exported = false)
    <S extends User> S save(S entity);
}
```
⚠️ **Hiding `save` disables `POST`, `PUT` *and* `PATCH` at once** — they all funnel through `save`. To disable only some verbs use `RepositoryRestConfiguration`:
```java
config.getExposureConfiguration()
      .forDomainType(User.class)
      .withItemExposure((metadata, httpMethods) -> httpMethods.disable(HttpMethod.DELETE))
      .withCollectionExposure((metadata, httpMethods) -> httpMethods.disable(HttpMethod.POST));
```
⚠️ And **hiding an endpoint is not security.** Anyone who can reach the app can still reach an endpoint you forgot to hide. Real protection is [§S1](05-spring-security.md#s1-the-architecture-from-the-servlet-filter-chain-to-the-securitycontext).

#### Handling `rel` attributes

`rel` (relation) is the **semantic name of a link** — the key inside `_links`, telling the client what that link means:
```java
// The JSON key inside '_links' shows as "find-by-code" instead of the method name
@RestResource(path = "by-code", rel = "find-by-code")
Optional<User> findByVerificationCode(@Param("code") String code);
```
| Property | Controls |
|---|---|
| `path` | the **URL** segment — `/members/search/by-code` |
| `rel` | the **JSON key** in `_links` — `"find-by-code"` |
| `exported` | whether it appears at all |
| `description` | the ALPS metadata description |

#### Custom Jackson serializers

⚠️ Spring Data REST configures its **own isolated `ObjectMapper`** for HAL-JSON, so a global `@Component` serializer or a `spring.jackson.*` property **will not affect it**. Register through `RepositoryRestConfigurer`:
```java
@Configuration
public class RestDataCustomConfiguration implements RepositoryRestConfigurer {
    @Override
    public void configureJacksonObjectMapper(ObjectMapper objectMapper) {
        SimpleModule customModule = new SimpleModule("CustomRestDataModule");
        customModule.addSerializer(MyCustomClass.class, new MyCustomSerializer());
        objectMapper.registerModule(customModule);
    }
}
```
💡 This "Spring Data REST has its own mapper" surprise is the #1 source of *"why is my `@JsonSerialize` being ignored?"*

#### Configuring CORS

**For a normal `@RestController`** — per method, or globally:
```java
@Configuration
public class WebMvcConfig implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/api/mvc/**").allowedOrigins("http://localhost:3000");
    }
}
```
**For Spring Data REST** — it bypasses standard MVC CORS config, so use the second `CorsRegistry` argument of `RepositoryRestConfigurer`:
```java
@Configuration
public class RestDataCorsConfiguration implements RepositoryRestConfigurer {
    @Override
    public void configureRepositoryRestConfiguration(RepositoryRestConfiguration config, CorsRegistry cors) {
        cors.addMapping("/**")
            .allowedOrigins("http://localhost:3000")
            .allowedMethods("GET", "POST", "PUT", "DELETE");
    }
}
```
You can also set it per repository: `@RepositoryRestResource` + `@CrossOrigin` on the interface.

⚠️ **When Spring Security is present it handles CORS first**, in the filter chain — before any of the above runs. You then need `http.cors(Customizer.withDefaults())` plus a `CorsConfigurationSource` bean, or your carefully configured CORS is rejected by a 401 before it ever matters.

#### `RepresentationModelProcessor` — injecting links

A `RepresentationModel` (formerly `Resource`) wraps your payload plus its hyperlinks. `RepresentationModelProcessor<T>` intercepts and alters the links **just before serialization**:
```java
@Component
public class UserResourceProcessor implements RepresentationModelProcessor<EntityModel<User>> {
    @Override
    public EntityModel<User> process(EntityModel<User> model) {
        model.add(Link.of("http://localhost:8080/docs/members.html", "documentation"));
        return model;
    }
}
```
💡 **The high-value use** is conditional links, which is the whole point of HATEOAS ([§D6.5](#d65-the-real-world-debate-should-you-actually-follow-_links-q28)):
```java
if (model.getContent().getStatus() == AWAITING_PAYMENT) {
    model.add(linkTo(methodOn(PaymentController.class).pay(id)).withRel("pay"));
}
```
Use `PagedModel<EntityModel<User>>` as the type parameter to process collections instead.

### D5.11 Configuration properties [Q29]

```properties
# 1. Base API URL routing
# Shifts the automated base route (e.g. from '/' to '/api/v1/people')
spring.data.rest.base-path=/api/v1

# 2. Pagination capacity constraints
spring.data.rest.default-page-size=50
# Hard-caps the client 'size' parameter — prevents ?size=99999 attacks
spring.data.rest.max-page-size=100

# 3. Custom navigational variable renaming
spring.data.rest.page-param-name=p
spring.data.rest.size-param-name=limit
spring.data.rest.sort-param-name=orderBy
# Client call changes from ?page=0&size=10 to ?p=0&limit=10&orderBy=name,asc

# 4. Metadata / ALPS
# Blocks the framework from exposing full entity validation criteria on public routes
spring.data.rest.metadata-configuration.alps-enabled=false

# 5. ⚠️ THE MOST IMPORTANT ONE — which repositories get exposed
# DEFAULT    = all public repository interfaces  (⚠️ dangerous default)
# ALL        = all repositories, public or not
# ANNOTATED  = ✅ only those explicitly marked @RepositoryRestResource / @RestResource
# VISIBILITY = only public ones
spring.data.rest.detection-strategy=ANNOTATED

# 6. Misc
spring.data.rest.return-body-on-create=true
spring.data.rest.return-body-on-update=true
spring.data.rest.default-media-type=application/hal+json
```

⚠️ **Set `detection-strategy=ANNOTATED` on day one.** The default (`DEFAULT`) exposes **every public repository in your application over HTTP**, including internal ones you never intended to publish. Adding `spring-boot-starter-data-rest` to an existing service has published entire internal data models by accident more than once.

**Exposing raw IDs.** By default Spring Data REST **omits the `@Id` from the JSON body** — the identity is supposed to live in the `self` URL. Front ends usually want the raw value anyway:
```java
@Component
public class ExposeIdsConfig implements RepositoryRestConfigurer {
    @Override
    public void configureRepositoryRestConfiguration(RepositoryRestConfiguration config, CorsRegistry cors) {
        config.exposeIdsFor(User.class, Order.class);
        // or, blanket:  config.exposeIdsFor(entityManager.getMetamodel().getEntities()
        //                        .stream().map(Type::getJavaType).toArray(Class[]::new));
    }
}
```

**Pagination and sorting over the wire [Q29]:**

| Parameter | Meaning | Example |
|---|---|---|
| `page` | page index, **0-based** | `GET /people?page=2&size=5` → the third page |
| `size` | rows per page (default **20**) | |
| `sort` | `field,direction` | `GET /people?sort=lastName,desc` |
| multi-field sort | repeat the parameter | `GET /people?sort=lastName,desc&sort=firstName,asc` |

⚠️ **`page` is 0-indexed.** `page=1` is the *second* page. This trips up every front end at least once.

### D5.12 When to use it, and when not to [Q22]

> **Your question:** *"is this an industry standard approach?"*

**It is a highly specialized standard within the Spring ecosystem, but not universally adopted for standard microservice development.** It is an exceptional fit for some use cases and a poor choice for others.

**✅ The sweet spots:**
- **Internal admin panels / CRUD-heavy apps.** If your service mostly reads, updates, edits and filters relational rows with few transactional side effects, it saves thousands of lines of boilerplate.
- **Rapid prototyping & MVPs.** A fully functional relational backend for a front-end team to consume immediately — weeks of work in an afternoon.
- **HATEOAS compliance.** When the design strictly mandates hypermedia-driven architecture with dynamic API graph linking.

**❌ The warning signs:**
- **Heavy DDD & business logic.** If nearly every endpoint orchestrates multiple microservices, calls third-party payment gateways, or runs heavy transactional workflows, forcing that into lifecycle listeners makes the codebase **brittle and very hard to debug**.
- **Public-facing open APIs.** The hypermedia format adds payload overhead and confuses external consumers used to flat JSON.
- **High performance control.** Because mappings are automated, tuning fetch plans, caching strategies and specialised response structures is significantly harder than explicit services and controllers.

**[+] Three more from experience, since you'll be asked to justify the choice:**
- ⚠️ **It couples your HTTP API to your database schema.** Rename a column and your public JSON changes. There is no anti-corruption layer. For a long-lived public API this is disqualifying.
- ⚠️ **Security is coarse.** Field-level authorization ("managers may change `salary`, nobody else may") has no natural home. `@PreAuthorize` on repository methods works but is awkward.
- ⚠️ **It is a niche choice.** It is still actively maintained and released with every Spring Data release train, but it is rarely the centre of new Spring services (this is a judgement about industry usage, not an official status). New greenfield Spring services in 2026 overwhelmingly use `@RestController` + DTOs.

> **Verdict for you:** know it well enough to recognise it and to be productive if you inherit it — internal tools especially. For the microservice work you're doing, **`@RestController` + DTOs is the right default**, and [§D5.8](#d58-projections-vs-dtos-q31) is the argument to make if anyone proposes otherwise.

---

## D6. HATEOAS, HAL and Querydsl [Q27, Q28]

### D6.1 What HATEOAS is [Q27]

**HATEOAS = Hypermedia As The Engine Of Application State.** It is **not a framework or library** — it is a foundational design principle of REST architecture. (In Roy Fielding's original dissertation it is the **highest** level of REST maturity; by his definition an API without it is not really REST at all.)

In a HATEOAS-compliant API the server doesn't return raw data alone. It returns the data **plus dynamic hyperlinks** that tell the client which actions are available next and exactly which URLs perform them.

#### The real-world analogy

**Without HATEOAS (blindly typing URLs):** imagine online banking with **zero buttons, menus or links** — just text: `$500`. To transfer money or close the account, you have to consult a secret instruction manual and type the URL into the address bar yourself. That is how traditional REST APIs work: **the client hardcodes every endpoint path.**

**With HATEOAS (clicking buttons):** you log in and see `$500`, and right next to it the server has rendered **[Transfer Money] [View Statements] [Apply for Loan]**. You don't need to know the backend's routing — you click the anchors it provided. HATEOAS brings that browser experience to **machine-to-machine** calls.

#### The code comparison

```json
// Traditional REST — flat JSON. What can I do next? Read the docs and hardcode /api/orders/5082/pay.
{
  "orderId": 5082,
  "status": "AWAITING_PAYMENT",
  "totalAmount": 120.00
}
```
```json
// HATEOAS / HAL — the data plus the available transitions
{
  "orderId": 5082,
  "status": "AWAITING_PAYMENT",
  "totalAmount": 120.00,
  "_links": {
    "self":   { "href": "http://localhost:8080/api/orders/5082" },
    "pay":    { "href": "http://localhost:8080/api/orders/5082/payment" },
    "cancel": { "href": "http://localhost:8080/api/orders/5082/cancel" }
  }
}
```

### D6.2 Why it's required [Q27]

**A. Absolute decoupling of client and server — zero hardcoded URLs.**
In traditional REST, if the backend renames `/api/v1/orders` to `/api/v2/checkout`, every web and mobile client **breaks instantly** until they're updated and redeployed. With HATEOAS the client hardcodes only the **root entry URL** (`/api`) and discovers everything else by following `href`s. The backend can rename routes daily and clients never notice.

**B. Dynamic business-logic control.**
The server uses `_links` to express **what is legal right now**. If an order moves `AWAITING_PAYMENT → SHIPPED`, paying or cancelling becomes illegal. The backend simply **stops emitting** the `pay` and `cancel` links; the UI sees they're absent and hides the buttons. **You don't duplicate state-machine rules on both sides.**

**C. Discoverability and self-documentation.**
A developer can open Postman, hit the root endpoint, and navigate the entire API graph by reading and clicking links.

> **Summary:** HATEOAS is required when you want **resilient, evolvable, decoupled** APIs where the server keeps absolute control over routing changes and state transitions without breaking clients.

### D6.3 What HAL is, and why it helps [Q28]

**HAL = Hypertext Application Language** — a formally standardized media type, `application/hal+json`.

HATEOAS says *"include links."* It doesn't say **how**. Without a convention, every team invents its own: a `links` array here, a `_linksMap` there, bare `hrefs` elsewhere. **HAL provides one universal layout rule:**
- All raw data lives at the root, or inside **`_embedded`** for collections.
- All navigation, relational and action links live in a flat **`_links`** object.
- Each link is keyed by its **`rel`** and holds at minimum an `href`; optionally `templated`, `title`, `type`.

**Why it's beneficial — tooling compatibility.** Because your API follows a standard structure, generic tools work with it out of the box. The **HAL Explorer** is one dependency away and gives you a clickable, interactive web dashboard over your whole API, with **no front-end code at all**:
```xml
<dependency>
    <groupId>org.springframework.data</groupId>
    <artifactId>spring-data-rest-hal-explorer</artifactId>
</dependency>
```
→ browse to `http://localhost:8080/` and navigate the entire graph.

💡 **[+] HAL is not the only hypermedia format**, and Spring HATEOAS supports several — useful to know so you can recognise them:

| Format | Media type | Note |
|---|---|---|
| **HAL** | `application/hal+json` | ✅ Spring's default, simplest, most widely used |
| **HAL-FORMS** | `application/prs.hal-forms+json` | HAL **+ the shape of each request** — lets a client render a form |
| Collection+JSON | `application/vnd.collection+json` | |
| UBER | `application/vnd.amundsen-uber+json` | |
| ALPS | `application/alps+json` | semantic **profile** metadata — Spring Data REST's `/profile` |

```java
@Configuration
@EnableHypermediaSupport(type = { HypermediaType.HAL, HypermediaType.HAL_FORMS })
class HypermediaConfig {}
```

### D6.4 Pagination and metadata for collections [Q28]

> **Your question:** *"i g hateoas has pagination metadata as well for a collection, data related to other actions as well? how do we know what kind of metadata or links will get generated for an endpoint?"*

**Yes.** Fetching a collection — `GET /members?page=1&size=2` — returns **three** distinct elements:

- **`_embedded`** — the actual list of data objects.
- **`page`** — pagination analytics: `size`, `totalElements`, `totalPages`, `number`.
- **`_links`** — navigational handles: `first`, `prev`, `self`, `next`, `last`.

```json
{
  "_embedded": {
    "members": [
      { "name": "Alice", "_links": { "self": { "href": "/members/1" } } }
    ]
  },
  "_links": {
    "first": { "href": "http://localhost:8080/members?page=0&size=2" },
    "prev":  { "href": "http://localhost:8080/members?page=0&size=2" },
    "self":  { "href": "http://localhost:8080/members?page=1&size=2" },
    "next":  { "href": "http://localhost:8080/members?page=2&size=2" }
  },
  "page": {
    "size": 2,
    "totalElements": 25,
    "totalPages": 13,
    "number": 1
  }
}
```
💡 Note `prev` and `next` are **absent** on the first and last pages respectively — that absence *is* the signal to disable the button. Same principle as `pay`/`cancel` above.

**How to know which links an endpoint will generate — you don't have to guess.** Spring Data REST generates metadata templates:
- `GET /members/search` → a runtime directory of every query method and its parameters.
- `GET /profile` → **ALPS** descriptors for the whole API.
- `GET /profile/members` → the semantic descriptor for that one resource.
- Or just add the HAL Explorer and look.

### D6.5 The real-world debate: should you actually follow `_links`? [Q28]

> **Your question:** *"i g in real world full stack application one should not rely on `_links` or any metadata link for navigation, instead we should have dedicated endpoints for each separate action?"*

**Your intuition is shared by many engineering teams, and in practice they mostly agree with you.**

**Why teams hesitate to follow links:**
- **Front-end complexity.** Parsing a nested `_links` map, matching a string key, extracting a URL and feeding it into an HTTP layer takes a lot of client-side abstraction boilerplate.
- **Type-safe breakage.** Modern front ends are TypeScript-heavy. Dynamic, string-driven URLs from the server make strict compile-time endpoint types hard to maintain.
- ⚠️ **[+] Nobody actually rewires clients live.** The decoupling benefit is theoretical if your deployment process ships the front end and backend together anyway.
- ⚠️ **[+] Extra round trips.** Strict HATEOAS means walking the graph from the root to find a resource. Clients bookmark URLs instead, which quietly reintroduces the coupling.

**Where the real-world hybrid value lies — this is the pattern worth internalising:**

> Use HATEOAS for **state-driven visibility** (server-controlled feature flags), **not** for route navigation.

The front-end developer **hardcodes** the action route (`POST /orders/{id}/cancel`). But they do **not** write client-side logic deciding *when* cancelling is allowed. Instead they check whether the server included a `"cancel"` key in `_links`. If it's missing, the button is disabled or hidden.

```typescript
// The pattern that actually pays for itself
const canCancel = 'cancel' in order._links;     // the SERVER owns the state machine
<button disabled={!canCancel} onClick={() => api.post(`/orders/${order.id}/cancel`)}>
```
✅ This centralises business rules on the backend while keeping client architecture explicit and typed. You get the real benefit of HATEOAS without paying its ergonomic cost.

### D6.6 [+] Spring HATEOAS without Spring Data REST

You don't need Spring Data REST to emit HAL — and this is the more common production setup, because it keeps you on `@RestController` + DTOs:

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-hateoas</artifactId>
</dependency>
```
```java
import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.*;

@RestController
@RequestMapping("/api/orders")
public class OrderController {

    @GetMapping("/{id}")
    public EntityModel<OrderDto> one(@PathVariable Long id) {
        OrderDto order = service.find(id);

        EntityModel<OrderDto> model = EntityModel.of(order,
            linkTo(methodOn(OrderController.class).one(id)).withSelfRel(),
            linkTo(methodOn(OrderController.class).all()).withRel("orders"));

        // ✅ Conditional links — the state machine expressed as hypermedia
        if (order.status() == AWAITING_PAYMENT) {
            model.add(linkTo(methodOn(PaymentController.class).pay(id)).withRel("pay"));
            model.add(linkTo(methodOn(OrderController.class).cancel(id)).withRel("cancel"));
        }
        return model;
    }
}
```
💡 **`linkTo(methodOn(...))` is the key trick:** the URL is derived from the controller method's own `@RequestMapping`, by reflection. Change the `@GetMapping` path and every generated link updates — **no string ever gets hardcoded**, and a renamed route can't silently produce a dead link.

| Type | Wraps |
|---|---|
| `RepresentationModel` | links only |
| `EntityModel<T>` | one object + links |
| `CollectionModel<T>` | a collection + links |
| `PagedModel<T>` | a page + links + `page` metadata |
| `RepresentationModelAssembler<T, D>` | reusable entity → model mapping |

⚠️ **[+] A Spring Data 3.3 / Boot 3.3 change you will hit.** Returning a bare `Page<T>` from a controller now logs: *"Serializing PageImpl instances as-is is not supported… no guarantee about the stability of the resulting JSON structure."* The fix is to opt into the stable representation:
```java
@Configuration
@EnableSpringDataWebSupport(pageSerializationMode = VIA_DTO)   // Page → PagedModel automatically
class WebConfig {}
```
…or return `PagedModel` explicitly (via `PagedResourcesAssembler` with Spring HATEOAS, or `org.springframework.data.web.PagedModel` without it). Worth doing early — the JSON shape changes, so migrating later breaks clients.

### D6.7 Querydsl [Q28]

> **Your question:** *"what is QueryDSL and how is this different from other languages (like SQL, JPQL etc)?"*

**Querydsl is a Java framework for building completely type-safe, fluent, dynamic database queries using a Java API instead of text strings.**

**The critical difference between the three:**

| | Checked at | Refactor-safe | Bound to |
|---|---|---|---|
| **SQL** — `SELECT * FROM users WHERE age > 18` | **never** (a runtime string) | ❌ | a specific DB dialect and **table/column** names |
| **JPQL/HQL** — `SELECT u FROM User u WHERE u.age > 18` | **runtime only** | ❌ | Java **entity/field** names, but still a plain string |
| **Querydsl** — `user.age.gt(18)` | ✅ **compile time** | ✅ | Java, type-checked |

The JPQL failure mode is the painful one: misspell a field — `"WHERE u.aage > 18"` — and the application **compiles perfectly**, deploys perfectly, and crashes at runtime the moment a user hits that endpoint.

**How Querydsl achieves it:** an **annotation processor** reads your `@Entity` classes at build time and generates a companion **`Q`-type** for each — `User` → `QUser`.
```java
// Misspell 'age' and javac fails immediately, before the app can even build
QUser user = QUser.user;
BooleanExpression isAdult = user.age.gt(18);
```

**Where it really earns its place — dynamic queries.** This is what JPQL cannot do cleanly:
```java
// Building a filter from whatever the client actually sent
BooleanBuilder where = new BooleanBuilder();
if (status  != null) where.and(user.status.eq(status));
if (minAge  != null) where.and(user.age.goe(minAge));
if (nameLike != null) where.and(user.name.containsIgnoreCase(nameLike));

List<User> results = queryFactory.selectFrom(user).where(where)
                                 .orderBy(user.createdAt.desc())
                                 .limit(50).fetch();
```
The JPQL equivalent is string concatenation with `StringBuilder` and a parameter map — the classic source of both bugs and SQL-injection risk. Querydsl's main rival for this job is the **JPA Criteria API**, which is type-safe too but famously unreadable; Querydsl exists largely because Criteria is so unpleasant.

**Integrating with Spring Data REST** — extend `QuerydslPredicateExecutor` and the binding is automatic:
```java
public interface UserRepository extends JpaRepository<User, Long>,
                                        QuerydslPredicateExecutor<User> {}
```
Any client can now filter straight from the URL, and Spring builds the predicate safely:
```
GET /members?firstName=Dave&lastName=Mathews&age=30
```
Customise the binding with `QuerydslBinderCustomizer`:
```java
public interface UserRepository extends JpaRepository<User, Long>,
        QuerydslPredicateExecutor<User>, QuerydslBinderCustomizer<QUser> {
    @Override
    default void customize(QuerydslBindings bindings, QUser user) {
        bindings.bind(user.firstName).first(StringExpression::containsIgnoreCase);
        bindings.excluding(user.password);       // ⚠️ ALWAYS exclude sensitive fields
    }
}
```
⚠️ **Without `excluding`, every entity field becomes a queryable URL parameter** — including `?password=...`, which turns into an oracle for brute-forcing values. Whitelist with `bindings.including(...)` rather than blacklisting.

⚠️ **[+] The Boot 3 build gotcha that costs everyone an afternoon.** Spring Boot 3 moved to Hibernate 6 and `jakarta.persistence`, so **every Querydsl artifact needs the `jakarta` classifier** — otherwise the `Q` classes are never generated and you get `cannot find symbol: QUser` with no useful explanation:
```xml
<dependency>
    <groupId>com.querydsl</groupId>
    <artifactId>querydsl-jpa</artifactId>
    <version>5.1.0</version>
    <classifier>jakarta</classifier>          <!-- ⚠️ required for Boot 3 -->
</dependency>
<plugin>
    <groupId>org.apache.maven.plugins</groupId>
    <artifactId>maven-compiler-plugin</artifactId>
    <configuration>
        <annotationProcessorPaths>
            <path>
                <groupId>com.querydsl</groupId>
                <artifactId>querydsl-apt</artifactId>
                <version>5.1.0</version>
                <classifier>jakarta</classifier>   <!-- ⚠️ here too -->
            </path>
            <path>
                <groupId>jakarta.persistence</groupId>
                <artifactId>jakarta.persistence-api</artifactId>
                <version>3.1.0</version>
            </path>
        </annotationProcessorPaths>
    </configuration>
</plugin>
```
*(The older `apt-maven-plugin` approach you'll find in most blog posts is no longer needed — use `annotationProcessorPaths` on the compiler plugin.)*

🐍🟨 **Your equivalents:** Querydsl ↔ **SQLAlchemy Core / the ORM query API** (`select(User).where(User.age > 18)`) ↔ **Prisma** or **Drizzle** or **Knex** in TypeScript. The shared idea is the same everywhere: replace a query *string* with composable, checkable expressions. Coming from SQLAlchemy you will find Querydsl immediately familiar — the difference is that Java's type safety is enforced by the **compiler** rather than by your editor.

---



---

[⬅ 03-spring-web.md](03-spring-web.md) · [🏠 Start here](00-start-here.md) · [05-spring-security.md ➡](05-spring-security.md)
