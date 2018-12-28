
$(PWD): build lib
	touch $@

build: $(shell find src -type f -name \*.cc -o -name \*.h)
	MAKEFLAGS= node-gyp rebuild

lib: $(shell find src -type f -name \*.ts -o -name \*.js -o -name \*.json )
	mkdir -p lib
	echo $? | xargs cp --parents -R -u -t lib
	mv $@/src/* $@
	rm -R $@/src
	./node_modules/.bin/tsc --project lib

# Generate typedoc documentation.
.PHONY: docs
docs: lib
	./node_modules/.bin/typedoc \
	--mode modules \
	--out $@ \
	--tsconfig lib/tsconfig.json \
	--theme minimal lib  \
	--excludeNotExported \
	--excludePrivate && \
	echo "" > docs/.nojekyll
