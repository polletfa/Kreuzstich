/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import * as z from 'zod/v4';

// ------------------------------------------------------------------------- GET /version

export const GetVersionResponseSchema = z.object({
    NAME: z.string(),
    WEBSITE: z.string(),
    MAJOR: z.number(),
    MINOR: z.number(),
    BUILD_TIME: z.string(),
    GIT_COMMIT: z.string(),
    BUILD_TYPE: z.string(),
    LICENSE: z.string(),
    VERSION_STRING: z.string()
});
export type GetVersionResponse = z.infer<typeof GetVersionResponseSchema>;
