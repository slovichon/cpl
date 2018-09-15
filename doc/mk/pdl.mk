# $Id$

OBJDIR = obj

.SUFFIXES: .pdl .html

HTML = ${LIBS:S/$/.html/}

.include "local.mk"

ADJSYSROOT = ${.CURDIR}/${SYSROOT}

all: all-recursive docs

docs: doc-html

doc-html: ${HTML}

.pdl.html:
	${XSLTPROC} -o ${.TARGET} ${ADJSYSROOT}/doc/xsl/doc-html.xsl ${.IMPSRC}

obj: obj-recursive
	@mkdir ${OBJDIR}

clean: clean-recursive
	rm -f ${HTML}

all-recursive clean-recursive obj-recursive:
	@for i in ${SUBDIRS}; do						\
		echo "==> $$i";							\
		(cd ${.CURDIR}/$$i && ${.MAKE} ${.TARGET:S/-recursive//});	\
	done
	@if [ -n "${SUBDIRS}" ]; then						\
		echo "<==";							\
	fi
