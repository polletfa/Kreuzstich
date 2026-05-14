/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { z } from 'zod';

import { GenericResponseSchema } from '@api/Generic';

// ------------------------------------------------------------------------- GET /threadlists

export const GetThreadListsResponseSchema = GenericResponseSchema.extend({
    data: z.array(z.object({
        id: z.number(),
        isCustom: z.boolean(),
        name: z.string()
    })).optional()
});
export type GetThreadListsResponse = z.infer<typeof GetThreadListsResponseSchema>;
