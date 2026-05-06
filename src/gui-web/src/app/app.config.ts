/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { ApplicationConfig, provideBrowserGlobalErrorListeners } from '@angular/core';
import { provideRouter } from '@angular/router';

import { routes } from './app.routes';

import { load as loadCore } from '@wrapper-wasm';
import { CORE_LOADER } from '@services/core-service/core-service';

export const appConfig: ApplicationConfig = {
    providers: [
        provideBrowserGlobalErrorListeners(),
        provideRouter(routes),

        { provide: CORE_LOADER, useValue: loadCore }
    ]
};
