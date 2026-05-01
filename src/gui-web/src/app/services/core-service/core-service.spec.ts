/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

// todo
import { TestBed } from '@angular/core/testing';

import { CoreService } from './core-service';

describe('CoreService', () => {
    let service: CoreService;

    beforeEach(() => {
        TestBed.configureTestingModule({});
        service = TestBed.inject(CoreService);
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });
});
