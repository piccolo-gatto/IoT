from sqlalchemy import Column, Integer, String, Float, DateTime
from database import Base
from datetime import datetime


class Device(Base):
    __tablename__ = "device"

    id = Column(String, primary_key=True, index=True)
    user_id = Column(Integer)
