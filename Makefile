PROJECT_PARTS := fsbl

.PHONY: all clean $(PROJECT_PARTS)

all: $(PROJECT_PARTS)
	./genimage.sh -c genimage.cfg

$(PROJECT_PARTS):
	$(MAKE) -C $@

clean:
	$(MAKE) -C fsbl clean
	rm -rf sdcard.img
	rm -rf genimage.tmp
	rm -rf tmp