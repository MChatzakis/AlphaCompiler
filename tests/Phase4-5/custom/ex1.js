function Book(title) {
    return [
		{ "title" : title },
		{ "sections" : [] },

		{ "AppendSection" :
			(function(book, section) {
				book.sections[objecttotalmembers(book.sections)] = section;
			})
		},

        { "Accept" :
        	(function(book, visitor) {
        		visitor.VisitBook(book);

        		for (i=0; i < objecttotalmembers(book.sections); ++i)
        			book.sections[i].Accept(book.sections[i], visitor);
        	})
        }
    ];
}

function Section(title) {
    return [
        { "title" : title },
        { "paragraphs" : [] },

		{ "AppendParagraph" :
			(function(section, paragraph) {
				section.paragraphs[objecttotalmembers(section.paragraphs)]
					= paragraph;
			})
		},

        { "Accept" :
        	(function(section, visitor) {
        		visitor.VisitSection(section);

        		for (i=0; i < objecttotalmembers(section.paragraphs); ++i)
        			section.paragraphs[i].Accept(section.paragraphs[i], visitor);
        	})
        }
    ];
}

function Paragraph(text) {
    return [
        { "content" : text },

        { "Accept" :
        	(function(paragraph, visitor) {
        		visitor.VisitParagraph(paragraph);
        	})
        }
    ];
}

book = Book("Hitchhicker's Guide to the Galaxy");
print(book);