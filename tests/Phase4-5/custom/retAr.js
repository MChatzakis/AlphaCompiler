function createMovie(title, actors){
    return [
        {"title" : title},
        {"actors" : actors},
        {"year" : 0},
        {"awards" : []},
        {"age restricted" : true},
        {"box office" : 0}
    ];
}

starWars = createMovie("StarWars", ["Mark", "Hans", "Harisson"]);
starWars["title"] = 1978; //?
print(starWars);