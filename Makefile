%.zip: %/
	cd $< && zip -r ../$@ . 