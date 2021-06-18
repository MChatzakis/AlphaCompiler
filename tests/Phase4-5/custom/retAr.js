function createMovie(title, actors){
    return [
        {title : "title"},
        {"actors" : ["Mark", "Hans", "Harisson"]},
        {"year" : 0},
        {"awards" : []},
        {"age restricted" : true},
        {"box office" : 0}
    ];
}

starWars = createMovie("StarWars", ["Mark", "Hans", "Harisson"]);
starWars["year"] = 1978; //?
print(starWars);