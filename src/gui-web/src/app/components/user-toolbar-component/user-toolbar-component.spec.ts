/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UserToolbarComponent } from './user-toolbar-component';

describe('UserToolbarComponent', () => {
    let component: UserToolbarComponent;
    let fixture: ComponentFixture<UserToolbarComponent>;

    beforeEach(async () => {
        await TestBed.configureTestingModule({
            imports: [UserToolbarComponent],
        }).compileComponents();

        fixture = TestBed.createComponent(UserToolbarComponent);
        component = fixture.componentInstance;
        await fixture.whenStable();
    });

    it('should create', () => {
        expect(component).toBeTruthy();
    });
});
