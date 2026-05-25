/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Component } from '@angular/core';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatSidenavModule } from '@angular/material/sidenav';
import { MatListModule } from '@angular/material/list';
import { MatIconModule } from '@angular/material/icon';
import { RouterOutlet } from '@angular/router';

import { UserToolbarComponent } from '@components/user-toolbar-component/user-toolbar-component';

@Component({
    selector: 'app-main-component',
    templateUrl: './main-component.html',
    styleUrl: './main-component.scss',
    imports: [
        MatToolbarModule,
        MatSidenavModule,
        MatListModule,
        MatIconModule,
        RouterOutlet,
        UserToolbarComponent
    ],
})
export class MainComponent {}
