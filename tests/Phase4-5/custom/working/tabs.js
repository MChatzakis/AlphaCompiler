t = [1, 2, 3, 4, 5];
t1 = [{ "string": true }, { 12.34: "CSD" }];

t[5] = 6;
t[5] = nil;

t[0] = nil;
t[0] = t1;

print("Table: ", t, " with ", objecttotalmembers(t), " members.");
print(t[6]); //nil

t2 = objectmemberkeys(t1);
print("Table: ", t2, " with ", objecttotalmembers(t2), " members.");

t3 = objectcopy(t);
print("Table: ", t3, " with ", objecttotalmembers(t3), " members.");

