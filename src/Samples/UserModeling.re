type teamId = TeamId(string);
type team = {
  id: teamId,
  name: string
};

type userId = UserId(string);
type sex = Man | Woman | Unknown(string);

type userAttribute = {
  id: userId,
  name: string,
  age: int,
  /* sex: sex,
  height: float,
  weight: float,
  email: string,
  password: string,
  teamId: teamId, */
};

type leaderUserAttribute = {
  subordinates: list(userId)
};

type adminUserAttribute = {
  teamIds: list(teamId)
};

type user = LeaderUser(userAttribute, leaderUserAttribute)
  | NormalUser(userAttribute)
  | AdminUser(userAttribute, leaderUserAttribute, adminUserAttribute);


let applyUser = (apply, user) => switch (user) {
| LeaderUser(attr, _) => attr |> apply
| NormalUser(attr) => attr |> apply
| AdminUser(attr, _, _) => attr |> apply
};

module Sample = {
  let _ = () => {
    let normalUser = NormalUser ({ name: "User", id: UserId("id"), age: 10});

    let name = applyUser((attr) => attr.name, normalUser);
    Js.Console.log(name);
  };
}