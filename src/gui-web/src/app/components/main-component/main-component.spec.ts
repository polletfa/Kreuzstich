/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { TestBed } from '@angular/core/testing';

import { MatToolbarModule } from '@angular/material/toolbar';
import { MatButtonModule } from '@angular/material/button';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatListModule } from '@angular/material/list';
import { MatIconModule } from '@angular/material/icon';

import { MainComponent } from './main-component';

import { CORE_LOADER } from '@services/core-service/core-service';
import { Version } from '@version';

const mockThread = class {
    delete = vi.fn();
    [Symbol.dispose]() { this.delete(); }
    name = vi.fn().mockReturnValue("mock");
}
const mockCore = {
    Version: {
        getVersionString: vi.fn().mockReturnValue(Version.getVersionString())
    },
    ColorSpace: {
        compositeRGBAOntoBackground: vi.fn(),
        distance: vi.fn()
    },
    Thread: mockThread,
    ThreadList: class {
        delete = vi.fn();
        [Symbol.dispose]() { this.delete(); }

        get = vi.fn().mockReturnValue([
            new mockThread(),
            new mockThread()
        ]);
        findClosest = vi.fn().mockReturnValue(new mockThread());
    }
};

describe('MainComponent', () => {
    beforeEach(async () => {
        await TestBed.configureTestingModule({
            imports: [
                MainComponent,
                MatButtonModule,
                MatIconModule,
                MatListModule,
                MatSidenavModule,
                MatToolbarModule
            ],
            providers: [
                { provide: CORE_LOADER, useValue: () => Promise.resolve(mockCore) }
            ]
        }).compileComponents();
    });

    it('should create the app', () => {
        const fixture = TestBed.createComponent(MainComponent);
        const app = fixture.componentInstance;
        expect(app).toBeTruthy();
    });
});
