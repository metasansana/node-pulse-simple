import * as Buffer from 'buffer';

declare module 'index' {

    class Connection {

        constructor(name: string);

        write(data: Buffer): void;

        close(): void;

    }

}
