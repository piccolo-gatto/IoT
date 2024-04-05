from pydantic import BaseModel
from datetime import datetime


class NewUser(BaseModel):
    name: str


class UserSaved(NewUser):
    id: int
    name: str

    class Config:
        orm_mode = True
