LIBS = Benchmark CPL DBH FSExtensions Graph OF RGB Session TimeStamp XMLElement

all: docs

docs: doc-html doc-text #doc-pdf

doc-html:
	for LIB in LIBS; do \
		for FILE in *.inc; do \
			VERSION=$(echo $FILE | sed 's/\.inc$//'); \
			mkdir -p $(LIB)/doc; \
			xsltproc -o $(LIB)/doc/$(VERSION).html .stuff/xsl/doc-html.xsl $(VERSION).phpdl; \
		done; \
	done;

doc-text:
	for LIB in LIBS; do \
		for FILE in *.inc; do \
			VERSION=$(echo $FILE | sed 's/\.inc$//'); \
			mkdir -p $(LIB)/doc; \
			xsltproc -o $(LIB)/doc/$(VERSION).txt .stuff/xsl/doc-text.xsl $(VERSION).phpdl; \
		done; \
	done;

doc-pdf:
	for LIB in LIBS; do \
		for FILE in *.inc; do \
			VERSION=$(echo $FILE | sed 's/\.inc$//'); \
			mkdir -p $(LIB)/doc; \
			xsltproc -o $(LIB)/doc/$(VERSION).txt .stuff/xsl/doc-pdf.xsl $(VERSION).phpdl; \
		done; \
	done;
