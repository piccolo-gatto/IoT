from sqlalchemy import Column, Integer, String, Float, DateTime
from src.database import Base
from datetime import datetime


class Temperature(Base):
    __tablename__ = "temperature"

    id = Column(Integer, primary_key=True, index=True)
    value = Column(Float)
    location = Column(String)
    device_id = Column(String)
    timestamp = Column(DateTime, default=datetime.now())
