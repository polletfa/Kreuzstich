/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DesignerComponent } from './designer-component';

import { CORE_LOADER } from '@services/core-service/core-service';
import { mockCore } from '@tests/core.mockup';

describe('DesignerComponent', () => {
    let component: DesignerComponent;
    let fixture: ComponentFixture<DesignerComponent>;

    beforeEach(async () => {
        await TestBed.configureTestingModule({
            imports: [DesignerComponent],
            providers: [
                { provide: CORE_LOADER, useValue: () => Promise.resolve(mockCore) }
            ]
        }).compileComponents();

        fixture = TestBed.createComponent(DesignerComponent);
        component = fixture.componentInstance;
        await fixture.whenStable();
    });

    it('should create', () => {
        expect(component).toBeTruthy();
    });
});
