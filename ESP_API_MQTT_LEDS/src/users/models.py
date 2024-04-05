from sqlalchemy import Column, Integer, String, Float, DateTime
from database import Base
from datetime import datetime


class User(Base):
    __tablename__ = "user"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String)
