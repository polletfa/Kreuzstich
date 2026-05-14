/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { z } from 'zod';

import { GenericResponseSchema } from '@datatypes/api/Generic';
import * as db from '@datatypes/db';

// ------------------------------------------------------------------------- GET /threadlists

export const GetThreadListsResponseSchema = GenericResponseSchema.extend({
    data: z.array(db.ThreadListSchema).optional()
});
export type GetThreadListsResponse = z.infer<typeof GetThreadListsResponseSchema>;
