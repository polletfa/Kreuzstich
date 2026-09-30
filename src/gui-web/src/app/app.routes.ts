/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Routes } from '@angular/router';
import { DesignerComponent } from '@components/designer-component/designer-component';
import { PageNotFoundComponent } from '@components/page-not-found-component/page-not-found-component';

export const routes: Routes = [
    {path: '', component: DesignerComponent},
    {path: '**', component: PageNotFoundComponent}
];
