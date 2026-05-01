/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

class Thread {
    constructor(name: string, rgb: string);
    isValid(): bool;
    equals(color: Thread|ColorSpace.ColorRGBA): bool;
    name(): string;
    color(): ColorSpace.ColorRGBA;
    hsl(): ColorSpace.ColorHSL;
    distance(color: Thread|ColorSpace.ColorLAB): number;
}
