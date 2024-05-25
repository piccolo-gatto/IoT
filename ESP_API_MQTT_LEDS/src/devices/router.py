from fastapi import APIRouter, Depends
from devices.schemas import NewDevice, DeviceSaved
from devices.models import Device
from sqlalchemy.orm import Session
from datetime import datetime
from dependencies import get_db

router = APIRouter()


@router.get("/devices")
async def get_devices(user_id: int, db: Session = Depends(get_db)):
    try:
        devices = db.query(Device).filter(Device.user_id == user_id).all()
        return devices
    except Exception as e:
        return e


@router.post("/create_device", response_model=DeviceSaved)
async def create_device(request: NewDevice, db: Session = Depends(get_db)):
    data = Device(id=request.id, user_id=request.user_id)
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e