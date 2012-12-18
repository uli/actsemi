SUBDIRS = Baselibc libactsemi installer launcher demo

all: subdirs

subdirs:
	for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir; \
	done

clean: subdirs_clean

subdirs_clean:
	for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir clean; \
	done

.PHONY: subdirs subdirs_clean $(SUBDIRS)
