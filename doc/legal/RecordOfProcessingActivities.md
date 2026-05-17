# Record of Processing Activities

*As required by Art. 30 GDPR*

## Controller

Fabien Pollet\
Heinrich-Heine-Straße 19\
14641 Nauen, Germany\
mail@kreuzstich.art

https://kreuzstich.art

---

## Processing Activities

### 1. HTTP Request Data (transient)

- **Purpose**: Technical operation of the service. Data is received as part of every HTTP request but immediately discarded without persistent storage.
- **Data categories**: IP address, user agent, referer
- **Data subjects**: All visitors, including anonymous users
- **Retention**: Not stored. Data exists only in memory during request processing.
- **Legal basis**: Legitimate interest – Art. 6.1.f GDPR (necessary for network communication)
- **Recipients**: STRATO GmbH (hosting infrastructure)

---

### 2. HTTP Logs

- **Purpose**: Technical monitoring and error diagnosis. No personal data is intentionally logged. This entry documents the deliberate decision to exclude personal data from logs.
- **Data categories**: Request time, server hostname, request URL, response status, response size, error messages. IP addresses and user agents are explicitly excluded from logs.
- **Data subjects**: All visitors, including anonymous users
- **Retention**: Until next deployment (ephemeral, managed by Docker). Size limited to 10 MB per container.
- **Legal basis**: Legitimate interest – Art. 6.1.f GDPR (technical operation and error monitoring)
- **Recipients**: STRATO GmbH (hosting infrastructure)

---

### 3. User Accounts

- **Purpose**: Authentication and identification of registered users, enabling access to user-specific features and persistent storage of user-generated content.
- **Data categories**: Email address, username, hashed password, adult content setting, account status and metadata (e.g. account creation date, disabled/suspended status)
- **Data subjects**: Registered users
- **Retention**: For the duration of the account. On deletion, data is removed immediately (except residual copies in backups, retained for up to 90 days). On disabling, data is retained for up to 1 year, then deleted.
- **Legal basis**: Contract performance – Art. 6.1.b GDPR (account creation constitutes a service agreement)
- **Recipients**: STRATO GmbH (hosting infrastructure and backups), Heinlein Hosting GmbH (email notifications via mailbox.org)

---

### 4. Session Cookies

- **Purpose**: Maintaining authenticated sessions between requests.
- **Data categories**: Session token (opaque identifier linking a browser session to a user account)
- **Data subjects**: Authenticated users
- **Retention**: Until browser is closed, or up to 30 days if the user selected "Keep me logged in". Invalidated on logout.
- **Legal basis**: Contract performance – Art. 6.1.b GDPR (necessary to provide the authenticated service)
- **Recipients**: STRATO GmbH (hosting infrastructure)

---

## Related Documents

- [Data Processing Guidelines](DataProcessingGuidelines.md)
- [Privacy Policy](PrivacyPolicy.md) (Art. 13/14 GDPR)

## GDPR Reference

- **Art. 6.1.b** – Lawfulness of processing: contract performance
- **Art. 6.1.f** – Lawfulness of processing: legitimate interest
- **Art. 30** – Records of processing activities
