/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { TestBed } from '@angular/core/testing';
import { MainComponent } from './main-component';
import { CORE_LOADER } from '@services/core-service/core-service';

const mockCore = {
    Version: {
        getVersionString: vi.fn().mockReturnValue('mocked')
    },
    ColorSpace: {
        compositeRGBAOntoBackground: vi.fn(),
        distance: vi.fn()
    }
};

describe('MainComponent', () => {
    beforeEach(async () => {
        await TestBed.configureTestingModule({
            imports: [MainComponent],
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

    it('should render title', async () => {
        const fixture = TestBed.createComponent(MainComponent);
        await fixture.whenStable();
        const compiled = fixture.nativeElement as HTMLElement;
        expect(compiled.querySelector('h1')?.textContent).toContain('Hello, gui-web');
    });
});
