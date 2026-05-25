/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import 'dotenv/config';

import { Helpers } from './Helpers';
import { Application } from './Application';

try {
    Application.instance.initDatabaseTables();
    Application.instance.start();
} catch(error) {
    console.error(Helpers.errorToString(error));
    process.exit(1);
}
