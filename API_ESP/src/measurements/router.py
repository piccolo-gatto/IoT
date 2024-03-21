from fastapi import APIRouter, Depends
from src.measurements.schemas import TemperatureValue, TemperatureSaved
from src.measurements.models import Temperature
from sqlalchemy.orm import Session
from datetime import datetime
from src.dependencies import get_db

router = APIRouter()


@router.get("/temperature")
async def get_temperature(location: str, db: Session = Depends(get_db)):
    # TODO select data for location
    try:
        temperatures = db.query(Temperature).filter(Temperature.location == location).all()
        values = []
        for temperature in temperatures:
            values.append(temperature.value)
        return {
            "values": values,  # TODO these values are updated
            "location": location
        }
    except Exception as e:
        return e


@router.post("/submit_temperature", response_model=TemperatureSaved)
async def submit_temperature(request: TemperatureValue, db: Session = Depends(get_db)):
    # TODO save data so we can make get_temperature work properly
    data = Temperature(value=request.value, location=request.location, device_id=request.device_id,
                       timestamp=datetime.now())
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e
