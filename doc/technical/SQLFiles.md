# SQL Files (data-web)

## Locations

- @threadlists: `resources/threadlists`
- @sql: `src/data-web/src/sql`

## Syntax

### Comments

```sql
-- Single-line comment

/*
 Multi-line
 comment
*/
```

### Positional Parameters

```sql
$1, $2, $3...
```

### Conditional Directives (`@with`)

The SQL query can be built conditionally using the custom `@with()` directive:

```sql
SELECT * FROM items @with(user) { WHERE user_id = $1 } ;
```

In this case, the `WHERE` clause will only be included if the file is imported with the specified condition (see below).

> [!IMPORTANT]
> `@with()` directives cannot be nested and the conditional block body cannot contain the closing curly brace character (`}`).

## Import

The SQL files can be imported as strings directly in TypeScript. The import is handled by the `tsup` plugin `src/data-web/sqlPlugin.ts`.

```typescript
import getItems from '@sql/getItems.sql';
import getItemsForUser from '@sql/getItems.sql' with { user: true };
```

A condition must be set to true to be enabled. Any other value will disable the condition.
