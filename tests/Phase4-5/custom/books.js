function Book(title) {

	print(title);

    return [
		{ "title" : title },
		{ "sections" : [] },
        { "AppendSection" :
			(function(book, section) {
				book.sections[objecttotalmembers(book.sections)] = section;
			})
		}
    ];
}

book = Book("Algorithms");
print(book);