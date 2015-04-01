include config.mk

JAVA  = $(shell find src/ -name '*.java')
CLASS = $(patsubst src/%.java, _build/%.class, $(JAVA))
MANIFEST = $(OUT_DIR)/META-INF/MANIFEST.MF

default: build

_build/%.class: src/%.java
	$(JC) $(JCFLAGS) -cp $(SRC_DIR) -d $(OUT_DIR) $<

pre_build:
	mkdir -p $(OUT_DIR)

build: pre_build $(CLASS)

clean:
	rm -rf $(OUT_DIR)

run: build
	$(J) $(JFLAGS) -cp $(OUT_DIR) $(MAIN)

$(MANIFEST):
	mkdir -p $(OUT_DIR)/META-INF
	echo "Main-Class: $(MAIN)" > $(OUT_DIR)/META-INF/MANIFEST.MF

jar: build $(MANIFEST)
	cd $(OUT_DIR); zip -r client.jar .
