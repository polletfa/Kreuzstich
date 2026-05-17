# Data Processing Guidelines

## Objective

The objective of this document is to provide guidelines for development and deployment to ensure compliance with the European Union's General Data Protection Regulation.

Our primary compliance target is the GDPR, as the project is based in the EU. We have not conducted a full assessment of other jurisdictions' data protection laws.
Given the privacy-first approach of this project, we believe the risk of non-compliance with other regulations is low, but this has not been formally verified.
Should the project grow significantly, compliance with other applicable regulations (e.g. CCPA, LGPD) will need to be reviewed.

## Data

The following data may be processed and/or stored by the program:
- HTTP request data including IP, user agent, referer, and so on,
- User information required for login (email, password, display name),
- User profile information (demographic data, social media accounts...),
- User generated content (including uploaded pictures).

How each type of data is handled is described in the "Implementation" section.

## Philosophy

The general philosophy of our data processing policy is to avoid storing personal data unless explicitly provided and allowed by the user (art. 25 GDPR):
- No personal data in technical logs,
- No tracking or analytics tools,
- Mandatory user information only as required for login and user identification,
- Additional personal information only on a voluntary basis.

Data will not be transferred or sold to any third party beyond what is necessary to ensure service. See the "External providers" section.

## Implementation

### URLs and cookies

- URLs, especially for API calls, shall not contain any token, user ID or resource ID that can be linked to a user (no REST API, user/resource IDs in POST requests only).
- User identification shall be done through a HTTP-only session cookie.
- The session cookie shall expire when the user closes the browser, unless the user selected "Keep me logged in" during the logging process.
- If the user selected "Keep me logged in", the session cookie shall expire after 30 days at most.
- No other cookie shall be set and no tracking or analytics tool used.

### Logging

- nginx logs:
   - Request time
   - Server hostname
   - Request URL
   - Response status
   - Response size
   - Error messages
- Backend/fastify logs:
   - Request time
   - Server hostname
   - Request URL
   - Request method
   - Response status
- Backend/Database logs:
   - Database queries shall not be logged.
   - On error, only log `error.message`, never the full error object, which contains the full query.
   - Never log user id, authentication tokens, or user input.
- Backend/additional logs:
   - Error messages, information messages for debugging purposes
   - Never log user id, authentication tokens, or user input.
- Logs are managed by docker.
- On deployment, old containers are removed, including the associated logs (so logs are only retained since the last deployment)
- Docker logs are limited to 10 MB per container.

### Picture storage

- Pictures shall be stored as a raw pixel buffer without metadata/EXIF data (art. 5 GDPR).
- For patterns, only the resized image with original colors and the resized image with selected colors (i.e. the actual pattern) shall be stored,
  not the original image provided by the user (art. 5 GDPR).
- Later on, a feature may be implemented to allow users to upload pictures of their works in progress or finished work.
  In this case, the pictures may be stored in any format (not necessarily as a raw pixel buffer), but must not contain metadata (art. 5 GDPR).
  The recommended workflow in this case would be to either use a library to strip EXIF data, or to proceed as follow:
   - Load the picture into a raw pixel buffer,
   - Generate new picture from the raw pixel buffer.
- Visibility of patterns can be private, adult users only, or public.
- Visibility of patterns shall be private by default, unless set otherwise by the user (art. 25 GDPR).
- Patterns with adult content cannot be shared publicly, but can be shared with adult users who consent to see this type of content (see next section).
  Selecting the appropriate visibility is the responsibility of the user (no automatic detection of adult content, no moderation before publishing).

### User accounts and guest access

- Many features shall be accessible without an account. In this case, no data shall be stored on the server. All data shall be stored locally using IndexedDB.
- For registered users, caching might be done with IndexedDB, but otherwise data shall be sent to the server for storage.
- Data associated with an account shall be kept for as long as the account exists.
- Only email, username and password are mandatory. Any other data is voluntary and optional.
- Users may at anytime delete or disable their account, as well as any of their data, subject to technical limitations such as backups (art. 17 GDPR).
- On account deletion: The account and all associated data (except backups, see below) shall be deleted right away.
- On account disabling:
  - The account shall not be visible anymore, but the data shall be retained for a maximum of 1 year.
  - One month before deletion, the user shall be sent a warning.
  - If the user logs in during the retention period, the account may then be reactivated upon confirmation by the user.
- Users can consent to viewing adult content. By doing so, they declare that they are legally allowed to do so. This option is disabled by default and must
  be set explicitly.

### Emails

- Emails may be sent for account management and legal purposes:
   - Confirmation of account creation
   - Password recovery
   - Account deletion
   - Account suspension
   - Data breach notification (Art. 34 GDPR)
   - Changes in privacy policy (Art. 13/14 GDPR)
   - Changes in terms of service
- Account management emails cannot be opted out, since they are either technical or legal requirements.
- Any other email (for example notifications or newsletters) may only be sent with the explicit permission of the user, configurable in the user profile (art. 7 GDPR).
- Any optional email shall be disabled by default and must be explicitly subscribed by the user (opt-in).
- Emails must contain as little user-related information as strictly necessary.

### Backups

- Daily incremental backup of all server data shall be performed.
- Data retention for backup shall not exceed 90 days, but can be less.
- Backups are encrypted (art. 32 GDPR).
- Data deleted by the user (including account deletion) are not removed from the backups, since removing parts of a backup
  point is not feasible. So deleted data will still exist during the backup data retention period.

### Data security and data breaches

- The following mechanisms are in place to ensure security (art. 32 GDPR):
   - GitHub security advisories, dependabot alerts and CodeQL scanning,
   - Automated security updates on the server (Debian unattended-upgrades).
- In case of a suspected breach, potentially affected users will be notified without undue delay (art. 34 GDPR).
- In case of a suspected breach, the responsible authority will be notified within 72 hours (art. 33 GDPR).
- The responsible authority is the [Landesbeauftragte für Datenschutz Brandenburg](https://www.lda.brandenburg.de/).

### Illegal Content and ToS Violations Response Procedure

#### Serious illegal content (CSAM, terrorism, hate speech)

In the event that content suspected to be child sexual abuse material (CSAM),
terrorism-related content, or content inciting violence or hatred (§ 130 StGB)
is discovered:

- **Immediately suspend the content** – make it inaccessible to all users, including the owner. Do not delete it.
- **Immediately suspend the user account** – prevent the user from uploading further content or deleting their account. Do not delete it.
- **Preserve all associated account data** – do not delete the account or any associated metadata.
- **Report immediately to the appropriate authority:**
   - CSAM → [Bundeskriminalamt](https://www.bka.de)
   - Terrorism-related content → [Bundeskriminalamt](https://www.bka.de)
   - Hate speech / incitement to violence → [Staatsanwaltschaft Potsdam](https://staatsanwaltschaften.brandenburg.de/sta/de/sta-potsdam/)
- **Follow law enforcement instructions** regarding evidence preservation and deletion. Do not delete the content or backups until explicitly
   authorized to do so.
- **Document everything** – record what was found, when, what actions were taken, and when.

Note: Do not copy or download the content. Suspending it in place preserves it as evidence without active possession.

#### Other ToS violations

In the event that content violating the Terms of Service is discovered:

- **Public explicit content** – set visibility to _adult users only_ and notify the user.
   This is considered a mistake rather than a violation.

- **Copyright infringement, non-consensual images of real people or discriminatory content** – immediately suspend the content and notify the user by email, explaining
   the violation and the action taken. The user may appeal within 30 days by contacting mail@kreuzstich.art.
   If the appeal is successful, the content will be restored. Otherwise it will be deleted after 30 days.

- **Document all actions taken**, including what was found, when, and what was done.

Repeated violations may result in account suspension.

#### Suspended accounts

- Accounts suspended due to serious illegal content cannot be deleted by the user. Accounts will only be deleted after instructed to do so by the authorities.
- Accounts suspended due to repeated violations without police involvement may not be reactivated by the user, but they may be deleted.
  If the user does not request deletion, the account will be automatically deleted after 1 year.
  One month before deletion, the user shall be sent a warning.
  The account may be reenabled by the operator after an appeal by the user.

### External providers

- GitHub, Inc.
   - Source code (publicly available),
   - Docker images (publicly available),
   - SSH credentials (secrets)
   - No personal data, not GDPR relevant
- STRATO GmbH
   - Virtual server, backups
   - Datacenters located in Germany
   - [Data processing agreement](DPA.strato.pdf) signed on the 12th May 2026 (art. 28 GDPR).
- Heinlein Hosting GmbH
   - Email service mailbox.org
   - Datacenters in Germany
   - [Data processing agreement](DPA.mailbox.pdf) signed on the 15th May 2026 (art. 28 GDPR).

## Related documents

- [Data Retention Schedule](DataRetentionSchedule.md)
- [Privacy Policy](PrivacyPolicy.md) (art. 13/14 GDPR)
- [Record of Processing Activities](RecordOfProcessingActivities.md) (art. 30 GDPR)

## GDPR Reference

The following GDPR articles are relevant to this document:

- **Art. 5** – Data minimization
- **Art. 7** – Conditions for consent
- **Art. 13/14** – Information obligations
- **Art. 17** – Right to erasure
- **Art. 17.3** – Exceptions to the right to erasure
- **Art. 25** – Privacy by design and by default
- **Art. 28** – Data Processing Agreements
- **Art. 30** – Record of Processing Activities
- **Art. 32** – Security of processing
- **Art. 33** – Breach notification to supervisory authority
- **Art. 34** – Breach notification to affected users
