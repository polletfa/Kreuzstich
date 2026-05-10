/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import 'dotenv/config';

import { Application } from './Application';

try {
    new Application().start();
} catch(error) {
    console.error(error instanceof Error ? error.message : error);
    process.exit(1);
}
