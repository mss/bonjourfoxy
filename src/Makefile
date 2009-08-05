SUBDIRS = browse enumerate register resolve notifier 

.PHONY: $(SUBDIRS) clean

all: $(SUBDIRS)

browse:
	make -C $@ all

enumerate:
	make -C $@ all

manager:
	make -C $@ all

notifier:
	make -C $@ all

register:
	make -C $@ all

resolve:
	make -C $@ all

clean:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done
