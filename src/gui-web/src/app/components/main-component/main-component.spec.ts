/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { TestBed } from '@angular/core/testing';

import { MatToolbarModule } from '@angular/material/toolbar';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatListModule } from '@angular/material/list';
import { MatIconModule } from '@angular/material/icon';

import { MainComponent } from './main-component';

describe('MainComponent', () => {
    beforeEach(async () => {
        await TestBed.configureTestingModule({
            imports: [
                MainComponent,
                MatIconModule,
                MatListModule,
                MatSidenavModule,
                MatToolbarModule
            ],
        }).compileComponents();
    });

    it('should create the app', () => {
        const fixture = TestBed.createComponent(MainComponent);
        const app = fixture.componentInstance;
        expect(app).toBeTruthy();
    });
});
