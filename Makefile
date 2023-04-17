%.zip: %/
	$(RM) $@
	zip -r $@ $< tools 