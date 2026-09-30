/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Component, OnInit, OnDestroy } from '@angular/core';
import { Meta } from '@angular/platform-browser';

@Component({
    selector: 'app-page-not-found-component',
    imports: [],
    templateUrl: './page-not-found-component.html',
    styleUrl: './page-not-found-component.scss',
})
export class PageNotFoundComponent implements OnInit, OnDestroy{
    constructor(private meta: Meta) {}

    ngOnInit() {
        this.meta.addTag({name: 'robots', content: 'noindex, nofollow'});
    }

    ngOnDestroy() {
        this.meta.removeTag("name='robots'");
    }
}
