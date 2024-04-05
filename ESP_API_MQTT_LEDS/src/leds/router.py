from fastapi import APIRouter, Depends
from leds.schemas import NewColors, ColorsSaved, NewLeds, LedsSaved
from leds.models import Colors, Leds
from sqlalchemy.orm import Session
from datetime import datetime
from dependencies import get_db

router = APIRouter()


@router.get("/all_colors")
async def get_colors(db: Session = Depends(get_db)):
    try:
        users = db.query(Colors).all()
        return users
    except Exception as e:
        return e


@router.post("/create_colors", response_model=ColorsSaved)
async def create_colors(request: NewColors, db: Session = Depends(get_db)):
    data = Colors(colors=request.colors)
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e
    

@router.get("/all_leds")
async def get_leds(user_id: int, device_id: int, db: Session = Depends(get_db)):
    try:
        users = db.query(Leds).filter(Leds.user_id == user_id and Leds.device_id == device_id).all()
        return users
    except Exception as e:
        return e


@router.post("/create_leds", response_model=LedsSaved)
async def create_leds(request: NewLeds, db: Session = Depends(get_db)):
    data = Leds(user_id = request.user_id, device_id = request.device_id, colors_id = request.colors_id)
    try:
        db.add(data)
        db.commit()
        db.refresh(data)
        return data
    except Exception as e:
        return e