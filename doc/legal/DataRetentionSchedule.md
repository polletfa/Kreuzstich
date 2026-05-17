# Data Retention Schedule

This document summarizes the retention periods for all data processed by Kreuzstich.
It is a quick reference companion to the [Data Processing Guidelines](DataProcessingGuidelines.md).

| Data type | Retention | Notes |
|---|---|---|
| HTTP request data (transient) | Not stored | Received and discarded during request processing |
| HTTP logs | Until next deployment or 10 MB limit | Whichever comes first |
| Session cookies | Until browser close or 30 days | 30 days only if "Keep me logged in" selected |
| Account data | Until account deletion | |
| Account (disabled) | Max 1 year | Warning email 1 month before deletion |
| Account (suspended, violations) | Max 1 year or on request | Warning email 1 month before deletion. Can be reactivated by operator after appeal |
| Account (suspended, illegal content) | Until authorized by law enforcement | Cannot be deleted by user |
| User content | Until account deletion | |
| User content (suspended, ToS) | 30 days | Restored if appeal successful, otherwise deleted |
| User content (suspended, illegal) | Until authorized by law enforcement | Cannot be deleted by user |
| Backups | Max 90 days | Includes residual copies of deleted data. Backups containing illegal content must be purged after authorization by law enforcement. |

## Related documents

- [Data Processing Guidelines](DataProcessingGuidelines.md)
- [Record of Processing Activities](RecordOfProcessingActivities.md)
