/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

export interface User {
    id: number,
    email: string,
    name: string,
    password: string
}

export interface Thread {
    id: number,
    list_id: number,
    name: string,
    color: string
}

export interface ThreadList {
    id: number,
    user_id: number|null,
    name: string
}
