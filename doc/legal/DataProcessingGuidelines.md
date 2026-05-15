# Data Processing Guidelines

## Objective

The objective of this document is to provide guidelines for development and deployment to ensure compliance with the European Union's General Data Protection Regulation.
We don't have the resources to check or ensure compliance with data protection legislations from other jurisdictions but we believe that complying with GDPR
will be sufficient to automatically ensure compliance with other legislations, so we don't plan to restrict access to the European Union.

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

- URLs, especially for API calls, shall not contain any token or user ID.
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
- Visibility of patterns shall be private by default, unless set to public by the user (art. 25 GDPR).

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

### Emails

- Emails may be sent for account management purposes:
   - Confirmation of account creation
   - Password recovery
   - Account deletion
   - Data breach notification
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

### External providers

- GitHub, Inc.
   - Source code (publicly available),
   - Docker images (publicly available),
   - SSH credentials (secrets)
   - No personal data, not GDPR relevant
- STRATO GmbH
   - Virtual server
   - Datacenter located in Germany
   - [Data processing agreement](DPA.strato.pdf) signed on the 12th May 2026 (art. 28 GDPR).
- Acronis International GmbH
   - Backups
   - Acronis has datacenters outside the European Union but backups are stored encrypted.
   - Sub-contractor of STRATO GmbH, covered by the same DPA (art. 28 GDPR).
- Heinlein Hosting GmbH
   - Email service mailbox.org
   - Datacenters in Germany
   - [Data processing agreement](DPA.mailbox.pdf) signed on the 15th May 2026 (art. 28 GDPR).

## Related documents

- [Privacy Policy](PrivacyPolicy.md) (art. 13/14 GDPR)
- [Record of Processing Activities](RecordOfProcessingActivities.md) (art. 30 GDPR)

## GDPR Reference

The following GDPR articles are relevant to this document:

- **Art. 5** – Data minimization
- **Art. 7** – Conditions for consent
- **Art. 13/14** – Information obligations
- **Art. 17** – Right to erasure
- **Art. 25** – Privacy by design and by default
- **Art. 28** – Data Processing Agreements
- **Art. 30** – Record of Processing Activities
- **Art. 32** – Security of processing
- **Art. 33** – Breach notification to supervisory authority
- **Art. 34** – Breach notification to affected users
