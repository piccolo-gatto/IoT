from sqlalchemy import Column, Integer, String
from database import Base
from datetime import datetime


class Colors(Base):
    __tablename__ = "colors"

    id = Column(Integer, primary_key=True, index=True)
    colors = Column(String, nullable=False)


class Leds(Base):
    __tablename__ = "leds"

    id = Column(Integer, primary_key=True, index=True)
    user_id = Column(Integer, nullable=False)
    device_id = Column(String, nullable=False)
    colors_id = Column(Integer, nullable=False)
