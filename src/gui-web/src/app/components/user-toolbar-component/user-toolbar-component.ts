/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Component, effect } from '@angular/core';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { MatCheckboxModule } from '@angular/material/checkbox';
import { FormsModule } from '@angular/forms';
import { MatButtonModule } from '@angular/material/button';

import { UserService } from '@services/user-service/user-service';

@Component({
    selector: 'app-user-toolbar-component',
    imports: [
        MatProgressSpinnerModule,
        MatCheckboxModule,
        FormsModule,
        MatButtonModule
    ],
    templateUrl: './user-toolbar-component.html',
    styleUrl: './user-toolbar-component.scss',
})
export class UserToolbarComponent {
    public persistentLogin = true;

    constructor(public userService: UserService) {
        effect(() => {
            console.log('User changed: ', this.userService.user());
        });
    }

    public onClickLogin() {
        //todo this is just a test for now
        if(this.userService.user()) {
            this.userService.logout();
        } else {
            this.userService.login({email: 'mail@kreuzstich.art', password: 'test', persist: this.persistentLogin});
        }
    }
}
