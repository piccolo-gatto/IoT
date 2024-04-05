from pydantic import BaseModel
from datetime import datetime


class NewColors(BaseModel):
    colors: str


class ColorsSaved(NewColors):
    id: int
    colors: str

    class Config:
        orm_mode = True


class NewLeds(BaseModel):
    user_id: int
    device_id: str
    colors_id: int


class LedsSaved(NewLeds):
    id: int
    user_id: int
    device_id: str
    colors_id: int

    class Config:
        orm_mode = True
