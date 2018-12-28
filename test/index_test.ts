import { Connection } from '../src';
import { toPromise } from '@quenk/noni/lib/control/monad/future';
import { readFile } from '@quenk/noni/lib/io/file';

const SAMPLE_FILE = `${__dirname}/./fixtures/sample.wav`;

describe('pulse-simple', () => {

    describe('Connection', () => {

        it('should play audio', () =>
            toPromise(readFile(SAMPLE_FILE, {})
                .map((data: Buffer) => {

                    let c = new Connection('test');
                    c.write(data);
                    c.write(data);
                    c.write(data);
                    c.close();

                })));

    });

});
