/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

interface Core {
  Version: Version;
};

declare function CoreModule(opts?: object): Promise<any>;
